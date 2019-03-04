/*
 ValidityChecker.cpp
 */

#include "ValidityChecker.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
ValidityChecker::ValidityChecker(vector<Token> tokenInput)
{
    tokenList = tokenInput;
    index = 0;
}

void ValidityChecker::TokenChecker(Token x, TokenType tt)
{
    if (tt == tokenList.at(index).GetTokenType()){
        index++;
        return;
    }
    else {
        throw string (tokenList.at(index).ToString());
    }
}

//----------------------------------------- Parsers ---------------------------------------

void ValidityChecker::BigParser()
{
    TokenChecker(tokenList.at(index), SCHEMES);
    TokenChecker(tokenList.at(index), COLON);
    SchemesParser();
    TokenChecker(tokenList.at(index), FACTS);
    TokenChecker(tokenList.at(index), COLON);
    FactsParser();
    TokenChecker(tokenList.at(index), RULES);
    TokenChecker(tokenList.at(index), COLON);
    RulesParser();
    TokenChecker(tokenList.at(index), QUERIES);
    TokenChecker(tokenList.at(index), COLON);
    QueriesParser();
    TokenChecker(tokenList.at(index), END_OF_FILE);
    return;
}


//----------------------------------------- SCHEMES ---------------------------------------

void ValidityChecker::SchemesParser()
{
    TokenChecker(tokenList.at(index), ID);
    TokenChecker(tokenList.at(index), LEFT_PAREN);
    TokenChecker(tokenList.at(index), ID);
    
    if(tokenList.at(index).GetTokenType() == COMMA){
        SchemeListParser();
    }
    
    TokenChecker(tokenList.at(index), RIGHT_PAREN);
    
    if(tokenList.at(index).GetTokenType() == ID){
        SchemesParser();
    }
    return;
}


void ValidityChecker::SchemeListParser()
{
    TokenChecker(tokenList.at(index), COMMA);
    TokenChecker(tokenList.at(index), ID);
    
    if (tokenList.at(index).GetTokenType() == COMMA){
        SchemeListParser();
    }
    return;
}

//----------------------------------------- FACTS ---------------------------------------

void ValidityChecker::FactsParser()
{
    if (tokenList.at(index).GetTokenType() == RULES){
        return;
    }
    
    TokenChecker(tokenList.at(index), ID);
    TokenChecker(tokenList.at(index), LEFT_PAREN);
    TokenChecker(tokenList.at(index), STRING);
    
    if (tokenList.at(index).GetTokenType() == COMMA){
        FactsList();
    }
    
    TokenChecker(tokenList.at(index), RIGHT_PAREN);
    TokenChecker(tokenList.at(index), PERIOD);

    if (tokenList.at(index).GetTokenType() == ID){
        FactsParser();
    }
    return;
}


void ValidityChecker::FactsList()
{
    TokenChecker(tokenList.at(index), COMMA);
    TokenChecker(tokenList.at(index), STRING);
    
    if (tokenList.at(index).GetTokenType() == COMMA){
        FactsList();
    }
    return;
}

//----------------------------------------- RULES ---------------------------------------

void ValidityChecker::RulesParser()
{
    if (tokenList.at(index).GetTokenType() == QUERIES){
        return;
    }
    HeadPredicateParser();
    TokenChecker(tokenList.at(index), COLON_DASH);
    RulesList();
    TokenChecker(tokenList.at(index), PERIOD);
    if (tokenList.at(index).GetTokenType() == ID){
        RulesParser();
    }
    return;
}


void ValidityChecker::RulesList()
{
    PredicateParser();
    
    if (tokenList.at(index).GetTokenType() == COMMA){
        TokenChecker(tokenList.at(index), COMMA);
        RulesList();
    }
    return;
}

void ValidityChecker::HeadPredicateParser()
{
    TokenChecker(tokenList.at(index), ID);
    TokenChecker(tokenList.at(index), LEFT_PAREN);
    TokenChecker(tokenList.at(index), ID);
    
    while (tokenList.at(index).GetTokenType() == COMMA){
        TokenChecker(tokenList.at(index), COMMA);
        TokenChecker(tokenList.at(index), ID);
    }
    
    TokenChecker(tokenList.at(index), RIGHT_PAREN);
    return;
}

void ValidityChecker::PredicateParser()
{
    TokenChecker(tokenList.at(index), ID);
    TokenChecker(tokenList.at(index), LEFT_PAREN);
    
    ParameterParser();
    
    while(tokenList.at(index).GetTokenType() == COMMA){
        TokenChecker(tokenList.at(index), COMMA);
        ParameterParser();
    }
    
    TokenChecker(tokenList.at(index), RIGHT_PAREN);
    return;
}

void ValidityChecker::ParameterParser()
{
    if (tokenList.at(index).GetTokenType() == STRING){
        TokenChecker(tokenList.at(index), STRING);
    }
    else if (tokenList.at(index).GetTokenType() == ID){
        TokenChecker(tokenList.at(index), ID);
    }
    else {
        ExpressionParser();
    }
    return;
}

void ValidityChecker::ExpressionParser()
{
    TokenChecker(tokenList.at(index), LEFT_PAREN);
    ParameterParser();
    if (tokenList.at(index).GetTokenType() == ADD){
        TokenChecker(tokenList.at(index), ADD);
    }
    else{
        TokenChecker(tokenList.at(index), MULTIPLY);
    }
    ParameterParser();
    TokenChecker(tokenList.at(index), RIGHT_PAREN);
    return;
}

//----------------------------------------- QUERIES ---------------------------------------
void ValidityChecker::QueriesParser()
{
    PredicateParser();
    TokenChecker(tokenList.at(index), Q_MARK);
    if (tokenList.at(index).GetTokenType() == ID){
        QueriesParser();
    }
 
    return;
}
