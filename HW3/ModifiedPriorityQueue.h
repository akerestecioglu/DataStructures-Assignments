//
//  ModifiedPriorityQueue.h
//  HW3
//
//  Created by Alihan Kerestecioglu on 11/26/19.
//  Copyright © 2019 Alihan Kerestecioglu. All rights reserved.
//

#ifndef ModifiedPriorityQueue_h
#define ModifiedPriorityQueue_h
#include <iostream>
#include <vector>
using namespace std;

template <class Comparable>
class ModifiedPriorityQueue {
    
public:
    
    ModifiedPriorityQueue(){}  //default constructor
    
    ModifiedPriorityQueue(int size){   //constructor
        currentSize = 0;
        Heap.resize(size);
        Location.resize(size);
    }
    
    ~ModifiedPriorityQueue(){}   //destructor
    
    bool isEmpty() const{
        return currentSize == 0;
    }
    
    void insert(Comparable value, int label){  //This method inserts an item with the given value and label into the MPQ.
        
        // Percolate up
        // Note that instead of swapping we move the hole up
        HeapNode newNode(value, label);  //node to be inserted
        int hole = ++currentSize;  //index to be inseted
        for( ; hole > 1 && value > Heap[hole / 2].height; hole /= 2){
            Heap[hole] = Heap[hole / 2];   //update the heap vector
            Location[Heap[hole/2].label] = hole;   //update the location vector
        }
        Heap[hole] = newNode;   //update the heap vector
        Location[label] = hole;   //update the location vector
    }
    
    Comparable Remove(int label){  //This method removes the value with this label and returns it.
        //LOCATION'I GUNCELLE
        Comparable val = Heap[Location[label]].height;   //return value
        Heap[Location[label]] = Heap[currentSize--];   //update the heap
        Location[Heap[Location[label]].label] = Location[label];  //update the location vector
        percolateDown(Location[label]);   //establish the heap order
        return val;
    }
    
    Comparable GetMax(){   //This method returns the maximum value that is currently stored.
        return Heap[1].height;
    }
    
private:
    
    struct HeapNode {
        Comparable height;
        int label;
        HeapNode(){}
        HeapNode(Comparable a, int b){
            height = a;
            label = b;
        }
        bool operator>(const HeapNode & rhs){
            return height > rhs.height;
        }
    };
    
    int currentSize; // Number of elements in heap
    vector<HeapNode> Heap;  // The heap array
    vector<int> Location;
    void buildHeap( );
    void percolateDown(int hole){   //from the slides, slightly different
        int child;
        HeapNode temp = Heap[hole];
        
        for( ; hole * 2 <= currentSize; hole = child ){
            child = hole * 2;
            if (child != currentSize && Heap[child + 1] > Heap[child]){
            child++;
            }
            if (Heap[child] > temp){
                Heap[hole] = Heap[child];   //update the heap vector
                Location[Heap[child].label] = hole;   //update the location vector
            }
            else
                break;
        }
        Heap[hole] = temp;   //update the heap vector
        Location[temp.label] = hole;   //update the location vector
    }

};

#endif /* ModifiedPriorityQueue_h */
