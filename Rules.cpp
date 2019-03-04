/*
 Rules.cpp
 */

#include "Rules.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
Rules::Rules(vector<Token>& tokenList)
{
    TokenChecker::CheckToken(RULES, tokenList);
    TokenChecker::CheckToken(COLON, tokenList);
    
    if (tokenList.begin()->GetTokenType() == RULES){
        return;
    }
    
    while (tokenList.begin()->GetTokenType() == ID){
        listOfRules.push_back(new Rule(tokenList));
    }
}

Rules::~Rules()
{
    for (unsigned int i=0; i < listOfRules.size(); i++){
        delete listOfRules.at(i);
    }
}

vector<Rule*> Rules::GetRulesList()
{
    return listOfRules;
}




//------------------------------------------------ ToString ----------------------------------------------------
string Rules::ToString()
{
    stringstream OSS;
    OSS << "Rules(" << listOfRules.size() << "):" << endl;
    for (unsigned int i=0; i < listOfRules.size(); i++) {
        OSS << listOfRules.at(i)->ToString() << "." << endl;
    }
    return OSS.str();
}

