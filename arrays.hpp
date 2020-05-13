//
//  arrays.hpp
//  PracticeC++
//
//  Created by Gaurav Sharma on 28/4/20.
//  Copyright © 2020 Gaurav Sharma. All rights reserved.
//

#ifndef arrays_hpp
#define arrays_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <cmath>


std::vector<std::string> checkDivisibility(std::vector<std::string> arr);
long minArea(std::vector<int> x, std::vector<int> y, int k);
int distinctMoves(std::string s, int n, int x, int y);
void rotateMatrix(int (&m)[3][3]);
void rotateMatrixInPlace(int (&m)[5][5]);
void zeroMatrix(int (&m)[5][5]);
void zeroMatrixOptimized(int (&m)[5][5]);

#endif /* arrays_hpp */
