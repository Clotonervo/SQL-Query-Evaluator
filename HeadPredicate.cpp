/*
 HeadPredicate.cpp
 */

#include "HeadPredicate.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
HeadPredicate::HeadPredicate(vector<Token>& tokenList)
{
    headPredicateID = new Id(tokenList);
    TokenChecker::CheckToken(LEFT_PAREN, tokenList);
    
    while (true){
        idList.push_back(new Id(tokenList));
        if (tokenList.begin()->GetTokenType() != COMMA){
            break;
        }
        TokenChecker::CheckToken(COMMA, tokenList);
    }
    TokenChecker::CheckToken(RIGHT_PAREN, tokenList);
}

HeadPredicate::~HeadPredicate()
{
    delete headPredicateID;
    for (unsigned int i=0; i < idList.size(); i++) {
        delete idList.at(i);
    }
}

Id* HeadPredicate::GetHeadPredID()
{
    return headPredicateID;
}

vector<Id*> HeadPredicate::GetIDList()
{
    return idList;
}


//------------------------------------------------ ToString ----------------------------------------------------
string HeadPredicate::ToString()
{
    stringstream OSS;
    OSS << "  " << headPredicateID->GetId() << "(";
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
