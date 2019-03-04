/*
 Expressions.cpp
 */

#include "Expressions.h"
#include "Parameter.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
Expressions::Expressions(vector<Token>& tokenList)
{
    TokenChecker::CheckToken(LEFT_PAREN, tokenList);
    paramOne = new Parameter(tokenList);
    
    if (tokenList.begin()->GetTokenType() == ADD){
        op = ADD;
        TokenChecker::CheckToken(ADD, tokenList);
    }
    else if (tokenList.begin()->GetTokenType() == MULTIPLY){
        op = MULTIPLY;
        TokenChecker::CheckToken(MULTIPLY, tokenList);
    }
    else {
        throw tokenList.begin()->ToString();
    }
    
    paramTwo = new Parameter(tokenList);
    TokenChecker::CheckToken(RIGHT_PAREN, tokenList);
}

Expressions::~Expressions()
{
    delete paramOne;
    delete paramTwo;
}

//------------------------------------------------ ToString ----------------------------------------------------
string Expressions::ToString()
{
    stringstream OSS;
    OSS << "(" << paramOne->ToString();
    if (op == ADD){
        OSS << "+";
    }
    else if (op == MULTIPLY){
        OSS << "*";
    }
    OSS << paramTwo->ToString() << ")";
    
    return OSS.str();
}
