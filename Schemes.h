/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 This code simply makes a list of schemes from a given list of Tokens
 Input: a list of Tokens (a vector)
 Output: a list of schemes via a Scheme ToString
 */

#ifndef Schemes_h
#define Schemes_h

#include <stdio.h>
#include <iostream>
#include "Scheme.h"
#include "Token.h"
#include "TokenChecker.h"

class Schemes {
public:
    Schemes(vector<Token>& tokenList);
    ~Schemes();
    
    vector<Scheme*> GetSchemesList();
    
    string ToString();
    
private:
    vector<Scheme*> listOfSchemes;
};
    
#endif /* Schemes_h */
