//
//  main.cpp
//  PracticeC++
//
//  Created by Gaurav Sharma on 28/4/20.
//  Copyright © 2020 Gaurav Sharma. All rights reserved.
//

#include <iostream>
#include <vector>
#include "strings.hpp"
#include "arrays.hpp"
#include "linklist.hpp"
#include "stacks.hpp"
#include "queues.hpp"
#include "trees.hpp"

#include<queue>
#include<unordered_set>
using namespace std;
class Entry
{
    std::queue<std::string> passports;
public:
    void enter(std::string passportNumber)
    {
        passports.push(passportNumber);
    }
    
    std::string leave()
    {
        if (passports.empty())
            throw std::logic_error("Waiting to be implemented");
        
        std::string front = passports.front();
        passports.pop();
        return front;
    }
};

int countInternalNodes (const std::vector<int>& tree)
{
    std::unordered_set<int> s;
    for (auto i : tree)
        s.insert(i);
    
    int ret = 0;
    for (int i=0;i<tree.size();i++)
    {
        if (s.count(i))
            ret++;
    }
    
    return ret;
}

int calcFactorial(int n)
{
    if (n==0 || n==1)
        return 1;
    
    return n*calcFactorial(n-1);
}

// Print all members of ar[] that have given
void findNumbers(vector<int>& ar, int sum,
                 vector<vector<int> >& res,
                 vector<int>& r, int i)
{
    // If  current sum becomes negative
    if (sum < 0)
        return;
    
    // if we get exact answer
    if (sum == 0)
    {
        res.push_back(r);
        return;
    }
    
    // Recur for all remaining elements that
    // have value smaller than sum.
    while (i < ar.size() && sum - ar[i] >= 0)
    {
        
        // Till every element in the array starting
        // from i which can contribute to the sum
        r.push_back(ar[i]); // add them to list
        
        // recur for next numbers
        findNumbers(ar, sum - ar[i], res, r, i);
        i++;
        
        // remove number from list (backtracking)
        r.pop_back();
    }
}

// Returns all combinations of ar[] that have given
// sum.
vector<vector<int> > combinationSum(vector<int>& ar,
                                    int sum)
{
    vector<int> r;
    vector<vector<int> > res;
    findNumbers(ar, sum, res, r, 0);
    
    return res;
}

void setOuterLater1(std::vector<std::vector<bool>>& m)
{
    size_t numRows = m.size();
    size_t numCols = m[0].size();
    
    for(size_t i=0;i<numRows;i++)
    {
        for (size_t j=0; j<numCols; j++)
        {
            if (i == 0 || i == numRows-1 || j == 0 || j == numCols-1)
                m[i][j] = true;
            else
                m[i][j] = false;
        }
    }
}

int main(int argc, const char * argv[])
{
    std::vector<std::vector<bool>> m;
    
    for (int i=0;i<4;i++)
    {
        std::vector<bool> v;
        for (int j=0;j<6;j++)
            v.push_back(false);
        
        m.push_back(v);
    }
    
    setOuterLater1(m);
    
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<6;j++)
            std:cout << (m[i][j] ? 1 : 0);
        std::cout<<std::endl;
    }
    return 0;
}
