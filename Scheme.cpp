/*
 Scheme.cpp
 */

#include "Scheme.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
Scheme::Scheme(vector<Token>& tokenList)
{
    schemeId = new Id(tokenList);
    TokenChecker::CheckToken(LEFT_PAREN, tokenList);
    
    while(true){
        idList.push_back(new Id(tokenList));
        if (tokenList.begin()->GetTokenType() != COMMA){
            break;
        }
        TokenChecker::CheckToken(COMMA, tokenList);
    }
    TokenChecker::CheckToken(RIGHT_PAREN, tokenList);
}

Scheme::~Scheme()
{
    for (unsigned int i=0; i < idList.size(); i++) {
        delete idList.at(i);
    }
    delete schemeId;
}


Id* Scheme::GetSchemeID()
{
    return schemeId;
}

vector<Id*> Scheme::GetIdList()
{
    return idList;
}



//------------------------------------------------ ToString ----------------------------------------------------
string Scheme::ToString()
{
    stringstream OSS;
    OSS << "  " << schemeId->GetId() << "(";
    for (unsigned int i=0; i < idList.size(); i++) {
        if (i == idList.size() - 1){
            OSS << idList.at(i)->GetId() << ")";
        }
        else {
            OSS << idList.at(i)->GetId() << ",";
        }
    }
    return OSS.str();
}

