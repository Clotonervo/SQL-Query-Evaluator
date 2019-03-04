/*
 Rule.cpp
 */
#include "Rule.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
Rule::Rule(vector<Token>& tokenList)
{
    headPred = new HeadPredicate(tokenList);
    TokenChecker::CheckToken(COLON_DASH, tokenList);
    
    while (tokenList.begin()->GetTokenType() == ID){
        listOfPreds.push_back(new Predicate(tokenList));
        if (tokenList.begin()->GetTokenType() != COMMA){
            break;
        }
        TokenChecker::CheckToken(COMMA, tokenList);
    }
    
    TokenChecker::CheckToken(PERIOD, tokenList);
}

Rule::~Rule()
{
    delete headPred;
    for (unsigned int i = 0; i < listOfPreds.size(); i++) {
        delete listOfPreds.at(i);
    }
}

HeadPredicate* Rule::GetHeadPredicate()
{
    return headPred;
}

vector<Predicate*> Rule::GetListOfPreds()
{
    return listOfPreds;
}

//------------------------------------------------ ToString ----------------------------------------------------
string Rule::ToString()
{
    stringstream OSS;
    OSS << headPred->ToString() << " :- ";
    for (unsigned int i = 0; i < listOfPreds.size(); i++) {
        if (i == listOfPreds.size() - 1){
            OSS << listOfPreds.at(i)->ToString();
        }
        else{
            OSS << listOfPreds.at(i)->ToString() << ",";
        }
    }
    return OSS.str();
}
