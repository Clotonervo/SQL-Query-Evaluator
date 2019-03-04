/*
 Facts.cpp
 */

#include "Facts.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
Facts::Facts(vector<Token>& tokenList)
{
    TokenChecker::CheckToken(FACTS, tokenList);
    TokenChecker::CheckToken(COLON, tokenList);
    
    if(tokenList.begin()->GetTokenType() == RULES){
        return;
    }

    while(tokenList.begin()->GetTokenType() == ID){
        listOfFacts.push_back(new Fact(tokenList));
    }
}

Facts::~Facts()
{
    for (unsigned int i=0; i < listOfFacts.size(); i++){
        delete listOfFacts.at(i);
    }
}

vector<Fact*> Facts::GetFactList()
{
    return listOfFacts;
}




//------------------------------------------------ ToString ----------------------------------------------------
string Facts::ToString()
{
    stringstream OSS;
    OSS << "Facts(" << listOfFacts.size() << "):" << endl;

    for (unsigned int i=0; i < listOfFacts.size();i++){
        OSS << listOfFacts.at(i)->ToString() << endl;
    }
    return OSS.str();
}

