//
// Rectangle.h
//  25497_AlihanKerestecioglu
//
//  Created by Alihan Kerestecioglu on 10/16/19.
//  Copyright © 2019 Alihan Kerestecioglu. All rights reserved.
//

#ifndef Rectangle_h
#define Rectangle_h

#include <iostream>
using namespace std;

class Rectangle {
    friend class TwoDimTree;
    friend class TwoDimTreeNode;
public:
    Rectangle(){}
    Rectangle(int a, int b, int c, int d){
        top = a;
        left = b;
        bottom = c;
        right = d;
    }
    int Right(){
        return right;
    }
    int Left(){
        return left;
    }
    int Bottom(){
        return bottom;
    }
    int Top(){
        return top;
    }
    bool CanDivide(){
        if ((bottom - top) > 1 && (right - left) > 1)
            return true;
        else
            return false;
    }
    
private:
    int top;
    int left;
    int bottom;
    int right;
};

#endif /* Rectangle_h */
