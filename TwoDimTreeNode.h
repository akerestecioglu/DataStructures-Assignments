//
//  TwoDimTreeNode.h
//  25497_AlihanKerestecioglu
//
//  Created by Alihan Kerestecioglu on 10/16/19.
//  Copyright © 2019 Alihan Kerestecioglu. All rights reserved.
//

#ifndef TwoDimTreeNode_h
#define TwoDimTreeNode_h

#include "Rectangle.h"
#include <vector>

using namespace std;

class TwoDimTreeNode {
    
    friend class TwoDimTree;
public:
    TwoDimTreeNode(){
        TopLeft = TopRight = BottomRight = BottomLeft = NULL;
    }
    TwoDimTreeNode(Rectangle rec){
        extent = rec;
        TopLeft = TopRight = BottomRight = BottomLeft = NULL;
    }
    Rectangle Extent(){
        return extent;
    }
    
private:
    Rectangle extent;
    vector<Rectangle> vertical, horizontal;
    TwoDimTreeNode *TopLeft, *TopRight, *BottomLeft, *BottomRight;
};


#endif /* TwoDimTreeNode_h */
