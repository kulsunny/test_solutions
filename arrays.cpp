//
//  arrays.cpp
//  PracticeC++
//
//  Created by Gaurav Sharma on 28/4/20.
//  Copyright © 2020 Gaurav Sharma. All rights reserved.
//

#include "arrays.hpp"

std::vector<std::string> checkDivisibility(std::vector<std::string> arr)
{
    std::vector<std::string> ret;
    for(auto x : arr)
    {
        bool found = false;
        
        // For nums less than 3 digits
        if (x.length() < 3)
        {
            int num = std::stoi(x);
            
            if (num%8 == 0)
                found = true;
        }
        
        // For nums more than 3 digits
        int hash[10] {0};
        for (auto c : x)
        {
            hash[c-'0']++;
        }
        
        for (int i=100; i<1001; i++)
        {
            if (i%8 != 0)
                continue;
            
            int unitsPlace = i%10;
            int unitCopy = hash[unitsPlace];
            hash[unitsPlace]--;
            
            int decimalsPlace = (i/10)%10;
            int decimalCopy = hash[decimalsPlace];
            hash[decimalsPlace]--;
            
            int hundredsPlace = (i/100)%10;
            int hundredCopy = hash[hundredsPlace];
            hash[hundredsPlace]--;
            
            if (hash[unitsPlace] >= 0
                && hash[decimalsPlace] >= 0
                && hash[hundredsPlace] >= 0)
            {
                //std::cout << "found for " << i << std::endl;
                found = true;
                break;
            }
            
            hash[hundredsPlace] = hundredCopy;
            hash[decimalsPlace] = decimalCopy;
            hash[unitsPlace] = unitCopy;
        }
        
        if (found)
            ret.push_back("YES");
        else
            ret.push_back("NO");
    }
    
    return ret;
}


long calcCurrMinArea(const std::vector<int>& x, const std::vector<int>& y,
                     std::vector<std::pair<double, int>>& dist, int k)
{
    long currMinArea{0};
    
    std::sort(dist.begin(), dist.end());
    
    int maxX{0},minX{0},maxY{0},minY{0};
    for (int j=0; j<k; j++)
    {
        int index = dist[j].second;
        
        maxX = std::max(x[index], maxX);
        minX = std::min(x[index], minX);
        
        maxY = std::max(y[index], maxY);
        minY = std::min(y[index], minY);
    }
    
    maxX++;
    minX--;
    
    maxY++;
    minY--;
    
    int currMinSide = std::max(std::abs(maxX) + std::abs(minX),
                               std::abs(maxY) + std::abs(minY));
    
    currMinArea = currMinSide*currMinSide;
    
    return currMinArea;
}

std::vector<std::pair<double, int>> calcDistanceFromOtherPoints(const std::vector<int>& x,                    const std::vector<int>& y,int currPoint)
{
    std::vector<std::pair<double, int>> dist;
    for (int i=0;i<x.size();i++)
    {
        double d{0.0f};
        
        if (i != currPoint)
            d = sqrt((x[i]*x[i]) + (y[i]*y[i]));
        
        dist.push_back(std::make_pair(d, i));
    }
    
    return dist;
}

long minArea(std::vector<int> x, std::vector<int> y, int k)
{
    if (x.size() != y.size() || k < 1 || k > x.size())
        return -1;
    
    if (k == 1)
        return 4;
    
    long minArea {LONG_MAX};
    for (int i=0;i<x.size();i++)
    {
        // Assume current point is part of the min area
        auto dist = calcDistanceFromOtherPoints(x, y, i);
        
        long currMinArea = calcCurrMinArea(x, y, dist, k);
        
        minArea = std::min(currMinArea, minArea);
    }
    
    return minArea;
}

void distinctMovesSubsequence(std::string s, int n, int x, int y, int index,
                              std::string path,
                              std::unordered_set<std::string>& uniqueStringSet)
{
    if (x == y)
        uniqueStringSet.insert(path);
    
    if (index >= s.size())
        return;
    
    if (s[index] == 'r')
        distinctMovesSubsequence(s, n, x+1, y, index+1, path+"r", uniqueStringSet);
    else
        distinctMovesSubsequence(s, n, x-1, y, index+1, path+"l", uniqueStringSet);
    
    distinctMovesSubsequence(s, n, x, y, index+1, path, uniqueStringSet);
}

int distinctMoves(std::string s, int n, int x, int y)
{
    std::unordered_set<std::string> uniqueStringSet;
    std::string path{""};
    int index = 0;
    distinctMovesSubsequence(s, n, x, y, index, path, uniqueStringSet);
    
    for (auto x:uniqueStringSet)
        std::cout << x << std::endl;
    return (int)uniqueStringSet.size();
}

// 1.7 Rotate Matrix: Given an image represented by an NxN matrix, where each pixel in the image is 4 bytes, write a method to rotate the image by 90 degrees. (Can you do this in place?
// Time:O(n^2) plus Space : O(n^2) because of extra copy matrix
void rotateMatrixOutOfPlace(int (&m)[3][3])
{
    int n = 3;
    int ret[n][n];
    
    // Clockwise
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            ret[j][n-i-1] = m[i][j];
    
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            m[i][j] = ret[i][j];
    
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            std::cout << m[i][j] << std::endl;
}

// 1.7 Rotate Matrix: Given an image represented by an NxN matrix, where each pixel in the image is 4 bytes, write a method to rotate the image by 90 degrees. (Can you do this in place?
// Time: O(n^2) without extra space (Optimized)
void rotateMatrixInPlace(int (&m)[5][5])
{
    int n=5;
    // Copy by doing in-place swaps
    for (int layer=0;layer<n/2;layer++)
    {
        int first = layer;
        int last = n-layer-1;
        for (int i=first; i<last;i++)
        {
            int offset = i-first;
            
            int temp = m[first][i]; // Copy top to temp
            m[first][i] = m[last-offset][first]; // Copy left to top
            m[last-offset][first] = m[last][last-offset]; // Copy bottom to left
            m[last][last-offset] = m[i][last]; // Copy right to bottom
            m[i][last] = temp; // Copy temp to right
        }
    }
    
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            std::cout << m[i][j] << std::endl;
}

// 1.8 Zero Matrix: Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column are set to O.
// Time:O(n^2), Space:O(x) where x is the number of 0s
void zeroMatrix(int (&m)[5][5])
{
    std::unordered_set<int> zeroRows;
    std::unordered_set<int> zeroColumns;
    int n= 5;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            if (m[i][j] == 0)
            {
                zeroRows.insert(i);
                zeroColumns.insert(j);
            }
        }
    }
    
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            if (zeroRows.count(i) || zeroColumns.count(j))
                m[i][j] = 0;
        }
    }
    
    for (int i=0;i<n;i++)
    {
        std::cout << std::endl;
        for (int j=0;j<n;j++)
            std::cout << m[i][j] << " ";
    }
    
}


void zerofyColumn(int (&m)[5][5], int col)
{
    int n=5;
    for (int i=0;i<n;i++)
        m[i][col] = 0;
}

void zerofyRow(int (&m)[5][5], int row)
{
    int n=5;
    for (int i=0;i<n;i++)
        m[row][i] = 0;
}

// 1.8 Zero Matrix: Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column are set to O.
// Time:O(n^2), Space:O(1)
void zeroMatrixOptimized(int (&m)[5][5])
{
    bool zeroFirstRow = false, zeroFirstColumn = false;
    int n= 5;
    
    // Check if first column has 0
    for (int i=0;i<n;i++)
        if (!m[i][0])
            zeroFirstColumn = true;
    
    // Check if first row has 0
    for (int i=0;i<n;i++)
        if (!m[0][i])
            zeroFirstRow = true;
    
    // In rest of the matrix, if there is 0, make the correspoing row/column in the first
    // row/column as 0
    for (int i=1;i<n;i++)
    {
        for (int j=1;j<n;j++)
        {
            if (!m[i][j])
            {
                m[i][0] = 0;
                m[0][j] = 0;
            }
        }
    }
    
    // Iterate to see if there is 0 in first row/column
    // and if there is, make the entire row/column as 0
    for (int i=0;i<n;i++)
        if (!m[i][0])
            zerofyRow(m, i);
    
    for (int i=0;i<n;i++)
        if (!m[0][i])
            zerofyColumn(m, i);
    
    // Finally,  see if the first row/column had any 0
    // and if there is, make the entire first row/column as 0
    if (zeroFirstColumn)
        zerofyColumn(m, 0);
    
    if (zeroFirstRow)
        zerofyRow(m, 0);
    
    for (int i=0;i<n;i++)
    {
        std::cout << std::endl;
        for (int j=0;j<n;j++)
            std::cout << m[i][j] << " ";
    }
        
}

// Given a vector<vector<bool>> as layers of tiles, set outer most layer to true and all others to false.
void setOuterLater(std::vector<std::vector<bool>>& m)
{
    size_t numRows = m.size();
    size_t numCols = m[0].size();
    
    for(size_t i=0;i<numRows;i++)
    {
        for (size_t j=0; j<numCols; j++)
        {
            if (i == 0 || i == numRows-1 || j == 0 || j || numCols-1)
                m[i][j] = true;
            else
                m[i][j] = false;
        }
    }
}

// Given a vector<int>, return the max sum of any 2 elements of the list.
int maxSum(const std::vector<int>& v)
{
    if (v.empty())
        return INT_MIN;
    else if (v.size() == 1)
        return v[0];
    else if (v.size() == 2)
        return v[0]+v[1];
    
    int largest = INT_MIN;
    int secondLargest = INT_MIN;
    
    for (int i=0;i<v.size();i++)
    {
        if (v[i] > largest)
            largest = v[i];
        else if (v[i] > secondLargest)
            secondLargest = v[i];
    }
    
    return largest + secondLargest;
}

// An Aptt can be 1 story or 2 stories, given the height of whole building, return how many combinations you can have. for example if the height is 3, you can do 1 - 1 - 1, 1 - 2, 2 - 1 so the answer is 3.
int getNumCombinations(int height, const std::vector<int>& v)
{
    return -1;
}
