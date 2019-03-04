/*
 Queries.cpp
 */

#include "Queries.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
Queries::Queries(vector<Token>& tokenList)
{
    TokenChecker::CheckToken(QUERIES, tokenList);
    TokenChecker::CheckToken(COLON, tokenList);
    
    while (tokenList.begin()->GetTokenType() == ID){
        listOfQueries.push_back(new Query(tokenList));
    }
}

Queries::~Queries()
{
    for (unsigned int i = 0; i < listOfQueries.size(); i++) {
        delete listOfQueries.at(i);
    }
}

vector<Query*> Queries::GetQueries()
{
    return listOfQueries;
}

//------------------------------------------------ ToString ----------------------------------------------------
string Queries::ToString()
{
    stringstream OSS;
    OSS << "Queries(" << listOfQueries.size() << "):" << endl;
    for (unsigned int i=0; i < listOfQueries.size(); i++) {
        OSS << "  " << listOfQueries.at(i)->ToString() << endl;
    }
    return OSS.str();
}
