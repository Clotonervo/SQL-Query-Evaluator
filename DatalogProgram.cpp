/*
 DatalogProgram.cpp
 */

#include "DatalogProgram.h"
#include "TokenChecker.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
DataLog::DataLog(vector<Token>& tokenInput)
{
    tokenList = tokenInput;    
    schemesStuff = new Schemes(tokenList);
    factsStuff = new Facts(tokenList);
    rulesStuff = new Rules(tokenList);
    queriesStuff = new Queries(tokenList);
    TokenChecker::CheckToken(END_OF_FILE, tokenList);
    makeDomains(tokenInput);
}

DataLog::~DataLog()
{
    delete schemesStuff;
    delete factsStuff;
    delete rulesStuff;
    delete queriesStuff;
}

//------------------------------------------------ ToString ----------------------------------------------------
string DataLog::ToString()
{
    stringstream OSS;
    OSS << "Success!" << endl;
    OSS << schemesStuff->ToString();
    OSS << factsStuff->ToString();
    OSS << rulesStuff->ToString();
    OSS << queriesStuff->ToString();
    OSS << DomainToString();
    return OSS.str();
}

void DataLog::makeDomains(vector<Token> tokenInput)
{
    for (unsigned int i = 0; i < tokenInput.size(); i++) {
        if (tokenInput.at(i).GetTokenType() == FACTS){
            frontIndex = i;
        }
        if (tokenInput.at(i).GetTokenType() == RULES){
            index = i;
        }
    }
    for (int i = frontIndex; i < index; i++) {
        if (tokenInput.at(i).GetTokenType() == STRING){
            domainStuff.insert(tokenInput.at(i).GetValue());
        }
    }
    return;
}

string DataLog::DomainToString()
{
    stringstream OSS;
    OSS << "Domain(" << domainStuff.size() << "):" << endl;
    for(set<string>::iterator iter=domainStuff.begin(); iter!=domainStuff.end(); ++iter){
        OSS << "  " << *iter << endl;
    }
    return OSS.str();
}

//------------------------------------------------ Getters ----------------------------------------------------
Schemes* DataLog::GetSchemes()
{
    return schemesStuff;
}

Facts* DataLog::GetFacts()
{
    return factsStuff;
}

Rules* DataLog::GetRules()
{
    return rulesStuff;
}

Queries* DataLog::GetQueries()
{
    return queriesStuff;
}
