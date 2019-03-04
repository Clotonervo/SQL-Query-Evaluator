/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 Creates a Query
 Inputs: a list of tokens 
 Outputs: outputs elements of a Query via a ToString
 */

#ifndef Query_h
#define Query_h

#include <stdio.h>
#include <vector>
#include <sstream>
#include <string>
#include "Token.h"
#include "Predicate.h"

class Query {
public:
    Query(vector<Token>& tokenList);
    ~Query();
    
    Predicate* GetPredicate();
    
    string ToString();
    
private:
    Predicate* queryPred;
};

#endif /* Query_h */
