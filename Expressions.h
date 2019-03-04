/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 Creates an Expressions object
 Inputs: a list of tokens
 Outputs: the elements found in an Expression object
 */

#ifndef Expressions_h
#define Expressions_h

#include <stdio.h>
#include "Token.h"
#include <vector>
#include <sstream>

class Parameter;

class Expressions {
public:
    Expressions(vector<Token>& tokenList);
    ~Expressions();
    
    string ToString();
    
private:
    Parameter* paramOne;
    Parameter* paramTwo;
    TokenType op;
    
};

#endif /* Expressions_h */
