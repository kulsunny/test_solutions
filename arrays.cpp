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

std::vector<std::pair<double, int>> calcDistanceFromOtherPoints(const std::vector<int>& x,const std::vector<int>& y,int currPoint)
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
    
    //for (auto x:uniqueStringSet)
        //std::cout << x << std::endl;
    return (int)uniqueStringSet.size();
}
