/*
 Predicate.cpp
 */

#include "Predicate.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
Predicate::Predicate(vector<Token>& tokenList)
{
    predicateId = new Id(tokenList);
    TokenChecker::CheckToken(LEFT_PAREN, tokenList);
    
    while(true){
        listOfParameters.push_back(new Parameter(tokenList));
        if (tokenList.begin()->GetTokenType() != COMMA){
            break;
        }
        TokenChecker::CheckToken(COMMA, tokenList);
    }
    TokenChecker::CheckToken(RIGHT_PAREN, tokenList);
}

Predicate::~Predicate()
{
    delete predicateId;
    for (unsigned int i = 0; i < listOfParameters.size(); i++) {
        delete listOfParameters.at(i);
    }
}

Id* Predicate::GetPredicateID()
{
    return predicateId;
}

vector<Parameter*> Predicate::GetListOfParameters()
{
    return listOfParameters;
}


//------------------------------------------------ ToString ----------------------------------------------------
string Predicate::ToString()
{
    stringstream OSS;
    OSS << predicateId->GetId() << "(";
    for (unsigned int i = 0; i < listOfParameters.size(); i++){
        if (i == listOfParameters.size() - 1){
            OSS << listOfParameters.at(i)->ToString() << ")";
        }
        else {
            OSS << listOfParameters.at(i)->ToString() << ",";
        }
    }
    return OSS.str();
}
