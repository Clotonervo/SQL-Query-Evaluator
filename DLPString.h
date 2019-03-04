/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 Stores the value of a STRING TokenType
 Inputs: a list of Tokens
 Outputs: string value
 */

#ifndef DLPString_h
#define DLPString_h

#include <stdio.h>
#include "Token.h"
#include "TokenChecker.h"

class DLPString {
public:
    DLPString(vector<Token>& tokenList);
    string GetString();
    
private:
    string currString;
};


#endif /* DLString_h */
