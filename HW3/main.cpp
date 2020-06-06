//
//  main.cpp
//  HW3
//
//  Created by Alihan's Macbook on 11/26/19.
//  Copyright © 2019 Alihan's Macbook. All rights reserved.
//

#include <iostream>
#include "ModifiedPriorityQueue.h"
#include <fstream>
#include <sstream>

using namespace std;

//#define DENEME

struct xNode{   //node for storing the file
    int point;
    int label;
    char side;
    int height;
    xNode(){}
    xNode(int a, int b, char c, int d){
        point = a;
        label = b;
        side = c;
        height = d;
    }
    
    bool operator>(const xNode & rhs){  //overloads the > operator
        return (point > rhs.point) || ((point == rhs.point) && side == 'R' && rhs.side == 'L') || ((point == rhs.point) && (side == rhs.side) && (height < rhs.height));
    }
};

void OpenFile(ifstream & reader){   //opens "input.txt"
    reader.open("input.txt");
#ifdef DENEME
    if (!reader.fail()) {
        cout << "Successfully opened file" << endl;
    }
#endif
}

void Merge(vector<xNode> & main,int start, int center, int end) {

    int leftSize, rightSize;
    leftSize = center - start + 1; //size of the left partition
    rightSize = end - center;   //size of the right partition
    vector<xNode> Left(leftSize), Right(rightSize);   //BURAYA BAK
    
    for(int i=0; i < leftSize; i++) {  //copy the left partition from main array
        Left[i] = main[start+i];
    }
    
    for(int j = 0; j < rightSize; j++) {   //copy the left partition from main array
        Right[j] = main[center+j+1];
    }
    
    int i=0, j=0, k;
    for(k = start; i < leftSize && j < rightSize; k++) {
        if(Right[j] > Left[i]) {
            main[k] = Left[i++];  //copy the less value and increment the pointer
        }
        else {
            main[k] = Right[j++];   //copy the less value and increment the pointer
        }
    }

    while(i < leftSize) {   //copy the remainder of the left partition to the main array
        main[k++] = Left[i++];
    }

    while(j < rightSize) {   //copy the remainder of the left partition to the main array
        main[k++] = Right[j++];
    }
}

void MergeSort(vector<xNode> & A,int start,int end) {
    int center;
    if(start<end)  //until the size of the partition is 1
    {
        center=(start+end)/2;
        MergeSort(A,start,center);   //call the function again with the left partition
        MergeSort(A,center+1,end);   //call the function again with the left partition
        Merge(A,start,center,end);   //merge the partitions
    }
}

vector<xNode> StoreBuildings(ifstream & reader){
    int numBuildings;
    string line;
    getline(reader, line);   //read the first line
    istringstream ss(line);
    ss >> numBuildings;   //get the number of buildings
    #ifdef DENEME
    cout << "Number of buildings: " << numBuildings << endl;
    #endif
    vector<xNode> xArray;
    for (int i = 0; i < numBuildings; i++) {
        getline(reader, line);
        istringstream ss2(line);
        int xLeft, height, xRight;
        ss2 >> xLeft >> height >> xRight;
        //create 2 nodes for each line
        xNode left(xLeft, i, 'L', height);
        xNode right(xRight, i, 'R', height);
        xArray.push_back(left);
        xArray.push_back(right);
    }
    return xArray;
}

void SortBuildings(vector<xNode> & buildings){   //MERGE SORT
    MergeSort(buildings, 0, buildings.size() - 1);
}

void PrintSkyline(ModifiedPriorityQueue<int> & skyline, vector<xNode> & buildings){
    for (int i = 0; i < buildings.size(); i++) {
        if (buildings[i].side == 'L') {   //NEW BUILDING
            if (i == 0 && buildings[i].point != 0) {  //if there is no building at coordinate 0
                cout << "0 0" << endl;
                 cout << buildings[i].point << " " << buildings[i].height << endl;
            }
            else if (i == 0) {   //if there is a building at coordinate 0
                cout << buildings[i].point << " " << buildings[i].height << endl;
            }
            else if (skyline.isEmpty() || skyline.GetMax() < buildings[i].height) {  //if the queue is empty or the new building is the heighest
                cout << buildings[i].point << " " << buildings[i].height << endl;
            }
            skyline.insert(buildings[i].height, buildings[i].label);   //insert the new building into the queue after print operations
        }
        
        else {   //END OF AN EXISTING BUILDING
            int oldMax = skyline.GetMax();   //the maximum height before removal
            skyline.Remove(buildings[i].label);
            while (i != buildings.size()-1 && buildings[i+1].side == 'R' && buildings[i+1].point == buildings[i].point) {  //remove every consecutive nodes at the same point and which are the end of a building
                skyline.Remove(buildings[i+1].label);
                i++;
            }
            if (skyline.isEmpty()) {   //if there is no building left
                cout << buildings[i].point << " 0" << endl;
            }
            else if (skyline.GetMax() < oldMax) {  //if the maximum height has changed
                //COUT THE NEW MAX
                cout << buildings[i].point << " " << skyline.GetMax() << endl;
            }
        }
    }
}

int main() {
    ifstream reader;
    
    OpenFile(reader);
    
    vector<xNode> buildings = StoreBuildings(reader);
    
#ifdef DENEME
    cout << "UNSORTED VECTOR:" << endl;
    for (int i = 0; i < buildings.size(); i++) {
        cout << buildings[i].point << " ";
    }
    cout << endl;
#endif
    
    SortBuildings(buildings);
    
#ifdef DENEME
    cout << "SORTED VECTOR:" << endl;
    for (int i = 0; i < buildings.size(); i++) {
        cout << buildings[i].point << " ";
    }
    cout << endl;
#endif
    
    ModifiedPriorityQueue<int> skyline(buildings.size() / 2);
    
    PrintSkyline(skyline, buildings);
    
    
    return 0;
}
