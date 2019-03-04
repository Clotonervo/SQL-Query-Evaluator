/*
 Fact.cpp
 */

#include "Fact.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
Fact::Fact(vector<Token>& tokenList)
{
    factID = new Id(tokenList);
    TokenChecker::CheckToken(LEFT_PAREN, tokenList);
    listOfStrings.push_back(new DLPString(tokenList));

    while(tokenList.begin()->GetTokenType() == COMMA) {
        TokenChecker::CheckToken(COMMA, tokenList);
        listOfStrings.push_back(new DLPString(tokenList));
        if (tokenList.begin()->GetTokenType() != COMMA){
            break;
        }
    };
    
    TokenChecker::CheckToken(RIGHT_PAREN, tokenList);
    TokenChecker::CheckToken(PERIOD, tokenList);
}

Fact::~Fact()
{
    delete factID;
    for (unsigned int i = 0; i < listOfStrings.size(); i++) {
        delete listOfStrings.at(i);
    }
}

Id* Fact::GetFactID()
{
    return factID;
}

vector<DLPString*> Fact::GetListOfStrings()
{
    return listOfStrings;
}

//------------------------------------------------ ToString ----------------------------------------------------
string Fact::ToString()
{
    stringstream OSS;
    OSS << "  " << factID->GetId() << "(";
    for (unsigned int i=0; i < listOfStrings.size(); i++) {
        if (i == listOfStrings.size() - 1){
            OSS << listOfStrings.at(i)->GetString() << ").";
        }
        else {
            OSS << listOfStrings.at(i)->GetString() << ",";
        }
    }
    return OSS.str();
    
}
