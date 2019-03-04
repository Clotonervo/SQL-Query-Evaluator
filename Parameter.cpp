/*
 Parameter.cpp
 */

#include "Parameter.h"
#include "Expressions.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
Parameter::Parameter(vector<Token>& tokenList)
{
    if (tokenList.begin()->GetTokenType() == ID){
        parameterToken = ID;
        parameterId = new Id(tokenList);
        parameterString = NULL;
        expresh = NULL;
    }
    else if (tokenList.begin()->GetTokenType() == STRING){
        parameterToken = STRING;
        parameterString = new DLPString(tokenList);
        parameterId = NULL;
        expresh = NULL;
    }
    else {
        parameterToken = PERIOD;
        parameterString = NULL;
        parameterId = NULL;
        expresh = new Expressions(tokenList);
    }
}
Parameter::~Parameter()
{
    delete parameterId;
    delete parameterString;
    delete expresh;
}

TokenType Parameter::GetParameterTokenType()
{
    return parameterToken;
}

DLPString* Parameter::GetParameterString()
{
    return parameterString;
}

Id* Parameter::GetParameterID()
{
    return parameterId;
}

//------------------------------------------------ ToString ----------------------------------------------------
string Parameter::ToString()
{
    stringstream OSS;
    switch (parameterToken) {
        case ID:
            OSS << parameterId->GetId();
            break;
        case STRING:
            OSS << parameterString->GetString();
            break;
        case PERIOD:
            OSS << expresh->ToString();
            break;
        default:
            throw (parameterToken);
            break;
    }
    return OSS.str();
}
