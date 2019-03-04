/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 Creates a Predicate
 Inputs: a list of tokens
 Outputs: outputs the elements in a Predicate via a ToString
 */

#ifndef Predicate_h
#define Predicate_h

#include <stdio.h>
#include "Token.h"
#include "Id.h"
#include "Parameter.h"
#include <vector>
#include <sstream>

class Predicate {
public:
    Predicate(vector<Token>& tokenList);
    ~Predicate();
    
    Id* GetPredicateID();
    vector<Parameter*> GetListOfParameters();
    
    string ToString();
private:
    Id* predicateId;
    vector<Parameter*> listOfParameters;
};

#endif /* Predicate_h */
