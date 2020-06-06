//Alihan Kerestecioglu
//16.10.2019

#include <iostream>
#include <fstream>
#include <sstream>
#include "Rectangle.h"
#include "TwoDimTreeNode.h"
#include "TwoDimTree.h"
using namespace std;

//TOP, LEFT, BOTTOM, RIGHT

string GetFileName() //returns a file name that is input from the user
{
    cout << "Please enter a file name: ";
    string fileName;
    cin >> fileName;
    return fileName;
}

bool IsOpened(ifstream & reader) //returns true if file is opened
{
    if (reader.fail())
    {
        return false;
    }
    return true;
}

void AskAnotherFileName(ifstream & reader, string & fileName)  //called if reader fails and asks for another file name
{
        reader.clear();
        reader.seekg(0);
        cout << "Failed.." << endl;
        cout << "Please enter another filename: ";
        cin >> fileName;
        reader.open(fileName.c_str());
}

Rectangle GetExtent(ifstream & reader){ //reads the first line and defines a rectangle object with the edge values
    string firstLine;
    getline(reader, firstLine);
    istringstream ss(firstLine);
    int top, left, bottom, right;
    ss >> top >> left >> bottom >> right;
    return Rectangle(top, left, bottom, right);
}


void OpenFile(ifstream & reader, string fileName){   //tries to open the file until it is successful
    reader.open(fileName.c_str());
    while (!IsOpened(reader)) {
        AskAnotherFileName(reader, fileName);
    }
}

void PlaceRectangles(TwoDimTree * tree, TwoDimTreeNode * root, ifstream & reader){
    int top, left, bottom, right;
    string line;
    while(!reader.eof()) {
        getline(reader, line);
        istringstream ss(line);
        ss >> top;
        if (top != -1) {
            ss >> left >> bottom >> right;
            Rectangle r(top, left, bottom, right);
            tree->AddRectangle(r, root);
        }
        else{
            reader.close();
            return;
        }
    }
}

void DealWithPoints(TwoDimTree * tree, TwoDimTreeNode * root){
    int x, y;
    do {
        vector<Rectangle> resultVector;
        cout << "Please enter a point: ";
        cin >> x >> y;
        if (x != -1) {
            tree->SearchPoint(x, y, root, resultVector);
            cout << x << " " << y << endl;
            cout << resultVector.size() << endl;
            if (resultVector.size() > 0) {
                for (int i = 0; i < resultVector.size(); i++) {
                    cout << resultVector[i].Top() << " " << resultVector[i].Left() << " " << resultVector[i].Bottom() << " " << resultVector[i].Right() << endl;
                }
            }
        }
    } while (x != -1);
}

int main() {
    ifstream reader; //create a reader
    OpenFile(reader, GetFileName()); //open the rectangle database file
    Rectangle extent = GetExtent(reader); //create a rectangle object with the coordinates that are read from the first line
    TwoDimTreeNode * myRoot = new TwoDimTreeNode(extent); //set the root of the tree
    TwoDimTree * tree = new TwoDimTree(myRoot); //create a tree object with the root myRoot
    PlaceRectangles(tree, myRoot, reader); //put the rectangles that are read from the file into the vectors im the tree object
    myRoot = tree->GetRoot();
    DealWithPoints(tree, myRoot); //find the rectangles that intersects with the points that are input by the user and display the results
    tree->Delete(myRoot); //delete the tree after the job is done
    
    return 0;
}
