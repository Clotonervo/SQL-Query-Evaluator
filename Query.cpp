/*
 Query.cpp
 */

#include "Query.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
Query::Query(vector<Token>& tokenList)
{
    queryPred = new Predicate(tokenList);
    TokenChecker::CheckToken(Q_MARK, tokenList);    
}

Query::~Query()
{
    delete queryPred;
}

Predicate* Query::GetPredicate()
{
    return queryPred;
}


//------------------------------------------------ ToString ----------------------------------------------------
string Query::ToString()
{
    stringstream OSS;
    OSS << queryPred->ToString() << "?";
    return OSS.str();
}
