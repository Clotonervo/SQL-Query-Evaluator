/*
 Schemes.cpp
 */

#include "Schemes.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
Schemes::Schemes(vector<Token>& tokenList)
{
    TokenChecker::CheckToken(SCHEMES, tokenList);
    TokenChecker::CheckToken(COLON, tokenList);
    
    do {
        listOfSchemes.push_back(new Scheme(tokenList));
    }while(tokenList.begin()->GetTokenType() == ID);
}

Schemes::~Schemes()
{
    for (unsigned int i=0; i<listOfSchemes.size(); i++){
        delete listOfSchemes.at(i);
    }
}

vector<Scheme*> Schemes::GetSchemesList()
{
    return listOfSchemes;
}






//------------------------------------------------ ToString ----------------------------------------------------
string Schemes::ToString()
{
    stringstream OSS;
    OSS << "Schemes(" << listOfSchemes.size() << "):" << endl;
    for (unsigned int i=0; i < listOfSchemes.size(); i++) {
        OSS << listOfSchemes.at(i)->ToString() << endl;
    }
    return OSS.str();
}
