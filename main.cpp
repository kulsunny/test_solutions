//
//  main.cpp
//  PracticeC++
//
//  Created by Gaurav Sharma on 28/4/20.
//  Copyright © 2020 Gaurav Sharma. All rights reserved.
//

#include <iostream>
#include "arrays.hpp"

int main(int argc, const char * argv[])
{
    std::vector<std::string> v;
    v.push_back("23123123123123153453453464565464534241234242342348");
    v.push_back("128");
    auto ret = checkDivisibility(v);
    for (auto s : ret)
    {
        cout << s << endl;
    }
    
    std::vector<int> x{1,3,5,5,2,-1,-4,-1,1,3};
    std::vector<int> y{1,2,2,4,4,2,4,-2,-2,-2};
    
    std::cout << minArea(x, y, 2) << std::endl;
    
    std::cout << distinctMoves("rrlrlr", 6, 1, 3) << std::endl;
    
    return 0;
}
