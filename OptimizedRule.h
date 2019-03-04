//
//  OptimizedRule.hpp
//  Rule Optimization
//
//  Created by Sam Hopkins on 12/5/18.
//  Copyright © 2018 Sam Hopkins. All rights reserved.
//

#ifndef OptimizedRule_h
#define OptimizedRule_h

#include <stdio.h>

class OptimizedRule {
public:
    OptimizedRule();
    
    int value;
    bool recursive;
    
    bool operator< (const OptimizedRule t) const {
        return value < t.value;
    }
};

#endif /* OptimizedRule_hpp */
