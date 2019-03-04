/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 Creates a list of Query objects to be outputted
 Inputs: a list of tokens
 Outputs: outputs list of Query objects via a ToString
 */

#ifndef Queries_h
#define Queries_h

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "Query.h"
#include "Token.h"
#include "TokenChecker.h"

class Queries {
public:
    Queries(vector<Token>& tokenList);
    ~Queries();
    
    vector<Query*> GetQueries();
    
    string ToString();
    
private:
    vector<Query*> listOfQueries;
    
};

#endif /* Queries_hpp */
