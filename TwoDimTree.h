//
//  TwoDimTree.h
//  25497_AlihanKerestecioglu
//
//  Created by Alihan Kerestecioglu on 10/16/19.
//  Copyright © 2019 Alihan Kerestecioglu. All rights reserved.
//

#ifndef TwoDimTree_h
#define TwoDimTree_h

#include "TwoDimTreeNode.h"
#include "Rectangle.h"

using namespace std;

class TwoDimTree {
    
public:
    TwoDimTree(){
        root = NULL;
    }
    TwoDimTree(TwoDimTreeNode * node){
        root = node;
    }
    void Delete(TwoDimTreeNode * temp){
        if (temp->BottomLeft != NULL) {
            Delete(temp->BottomLeft);
        }
        if (temp->BottomRight != NULL) {
            Delete(temp->BottomRight);
        }
        if (temp->TopLeft != NULL) {
            Delete(temp->TopLeft);
        }
        if (temp->TopRight != NULL) {
            Delete(temp->TopRight);
        }
        delete temp;
    }
    void AddRectangle(Rectangle r, TwoDimTreeNode * temp){
        int verticalLine = (temp->Extent().Left() + temp->Extent().Right()) / 2;
        int horizontalLine = (temp->Extent().Top() + temp->Extent().Bottom()) / 2;
        if (r.Left() <= verticalLine && r.Right() > verticalLine) {  //if it intersects with the vertical line
            temp->vertical.push_back(r);
        }
        else if (r.Top() <= horizontalLine && r.Bottom() > horizontalLine) { //if it intersects with the horizontal line
            temp->horizontal.push_back(r);
        }
        else{  //if the lines does not intersect with the rectangle
            if (r.Right() <= verticalLine) { //if it is on the left side
                if (r.Bottom() <= horizontalLine) {  //if it is on the TopLeft
                    if (temp->TopLeft == NULL) {
                        temp->TopLeft = new TwoDimTreeNode;
                        temp->TopLeft->extent.top = temp->extent.top;
                        temp->TopLeft->extent.left = temp->extent.left;
                        temp->TopLeft->extent.bottom = (temp->extent.top + temp->extent.bottom)/2;
                        temp->TopLeft->extent.right = (temp->extent.left + temp->extent.right)/2;
                    }
                    AddRectangle(r, temp->TopLeft); //search the top left quadrant
                }
                else if (r.Top() > horizontalLine) {  //if it is on the BottomLeft
                    if (temp->BottomLeft == NULL) {
                        temp->BottomLeft = new TwoDimTreeNode;
                        temp->BottomLeft->extent.top = (temp->extent.top + temp->extent.bottom)/2+1;
                        temp->BottomLeft->extent.left = temp->extent.left;
                        temp->BottomLeft->extent.bottom = temp->extent.bottom;
                        temp->BottomLeft->extent.right = (temp->extent.left + temp->extent.right)/2;

                    }
                    AddRectangle(r, temp->BottomLeft); //search the bottom left quadrant
                }
            }
            else if (r.Left() > verticalLine){  //if it is on the right side
                if (r.Bottom() <= horizontalLine) { //if it is on the TopRight
                    if (temp->TopRight == NULL) {
                        temp->TopRight = new TwoDimTreeNode;
                        temp->TopRight->extent.top = temp->extent.top;
                        temp->TopRight->extent.left = (temp->extent.left + temp->extent.right)/2+1;
                        temp->TopRight->extent.bottom = (temp->extent.top + temp->extent.bottom)/2;
                        temp->TopRight->extent.right = temp->extent.right;
                    }
                    AddRectangle(r, temp->TopRight); //search the top right quadrant
                }
                else if (r.Top() > horizontalLine){  //if it is on the BottomRight
                    if (temp->BottomRight == NULL) {
                        temp->BottomRight = new TwoDimTreeNode;
                        temp->BottomRight->extent.top = (temp->extent.top + temp->extent.bottom)/2+1;
                        temp->BottomRight->extent.left = (temp->extent.left +temp->extent.right)/2+1;
                        temp->BottomRight->extent.bottom = temp->extent.bottom;
                        temp->BottomRight->extent.right = temp->extent.right;
                    }
                    AddRectangle(r, temp->BottomRight); //search the bottom right quadrant
                }
            }
        }
    }
    
    bool IsIn(int x, int y, Rectangle r){
        if ((r.Left() <= x && r.Right() > x) && (r.Top() <= y && r.Bottom() > y))
            return true;
        else
            return false;
    }
    
    void SearchPoint(int x, int y, TwoDimTreeNode * temp, vector<Rectangle> & intersectingRecs){
        int verticalLine, horizontalLine;
        if (temp != NULL) {
            verticalLine = (temp->Extent().Left() + temp->Extent().Right()) / 2;
            horizontalLine = (temp->Extent().Top() + temp->Extent().Bottom()) / 2;
        }
        if (temp != NULL) {
            for (int i=0; i<temp->horizontal.size(); i++) {
                if (IsIn(x, y, temp->horizontal[i])) {
                    intersectingRecs.push_back(temp->horizontal[i]);
                }
            }
            for (int i=0; i<temp->vertical.size(); i++) {
                if (IsIn(x, y, temp->vertical[i])) {
                    intersectingRecs.push_back(temp->vertical[i]);
                }
            }
            if (x < verticalLine) { //Go To Left
                if (y < horizontalLine) { //Go To Top Left
                    temp = temp->TopLeft;
                    SearchPoint(x, y, temp, intersectingRecs);
                }
                else if (y > horizontalLine) { //Go To Bottom Left
                    temp = temp->BottomLeft;
                    SearchPoint(x, y, temp, intersectingRecs);
                }
                    
            }
            else if (x > verticalLine){ //Go To Right
                if (y < horizontalLine) { //Go To Top Right
                    temp = temp->TopRight;
                    SearchPoint(x, y, temp, intersectingRecs);
                }
                else if (y > horizontalLine) { //Go To Bottom Right
                    temp = temp->BottomRight;
                    SearchPoint(x, y, temp, intersectingRecs);
                }
            }
        }
    }
    
    TwoDimTreeNode * GetRoot(){
        return root;
    }
    
private:
    TwoDimTreeNode * root;
};

#endif /* TwoDimTree_h */
