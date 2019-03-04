/*
 TokenChecker.cpp
 */

#include "TokenChecker.h"

void TokenChecker::CheckToken(TokenType tt, vector<Token>& tokenList)
{
    if (tt == tokenList.begin()->GetTokenType()){
        tokenList.erase(tokenList.begin());
        return;
    }
    else {
        throw string (tokenList.begin()->ToString());
    }
}
