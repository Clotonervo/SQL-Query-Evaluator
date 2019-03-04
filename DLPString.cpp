/*
 DLPString.cpp
 */

#include "DLPString.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
DLPString::DLPString(vector<Token>& tokenList)
{
    currString = tokenList.begin()->GetValue();
    TokenChecker::CheckToken(STRING, tokenList);
}

string DLPString::GetString()
{
    string tempString;
    tempString = currString.substr(1, (currString.length() - 2));
    
    return currString;
}
