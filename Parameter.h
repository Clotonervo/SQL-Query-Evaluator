/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 Creates a Parameter object (is recursive with Expressions
 Inputs: a list of tokens
 Outputs: via a ToString outputs all the elements of a Parameter
 */

#ifndef Parameter_h
#define Parameter_h

#include <stdio.h>
#include "Token.h"
#include "Id.h"
#include "DLPString.h"
#include <vector>
#include <sstream>

class Expressions;

class Parameter {
public:
    Parameter(vector<Token>& tokenList);
    ~Parameter();
    
    TokenType GetParameterTokenType();
    DLPString* GetParameterString();
    Id* GetParameterID();
    
    string ToString();
    
private:
    TokenType parameterToken;
    Id* parameterId;
    DLPString* parameterString;
    Expressions* expresh;
};

#endif /* Parameter_h */
