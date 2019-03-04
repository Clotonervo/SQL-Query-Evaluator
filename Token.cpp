/*
    Token.cpp
*/

#include "Token.h"
#include <iostream>
#include <sstream>
using namespace std;

//----------------------------------------- Constructors ---------------------------------------
Token::Token()
{
    tt = UNDEFINED;
    value = "none";
    line = -1;
}

Token::Token(TokenType typeOfToken, string one, int lineNum)
{
    tt = typeOfToken;
    value = one;
    line = lineNum;
}
//----------------------------------------- Getting Value and TokenType ---------------------------------------
TokenType Token::GetTokenType()
{
    return tt;
}

string Token::GetValue()
{
    return value;
}

//----------------------------------------- Token ToString ---------------------------------------
string Token::ToString()
{
    stringstream OSS;
    switch (tt) {
        case COMMA:
            OSS << "(COMMA,\"";
            break;
        case PERIOD:
            OSS << "(PERIOD,\"";
            break;
        case Q_MARK:
            OSS << "(Q_MARK,\"";
            break;
        case LEFT_PAREN:
            OSS << "(LEFT_PAREN,\"";
            break;
        case RIGHT_PAREN:
            OSS << "(RIGHT_PAREN,\"";
            break;
        case COLON:
            OSS << "(COLON,\"";
            break;
        case COLON_DASH:
            OSS << "(COLON_DASH,\"";
            break;
        case MULTIPLY:
            OSS << "(MULTIPLY,\"";
            break;
        case ADD:
            OSS << "(ADD,\"";
            break;
        case SCHEMES:
            OSS << "(SCHEMES,\"";
            break;
        case FACTS:
            OSS << "(FACTS,\"";
            break;
        case RULES:
            OSS << "(RULES,\"";
            break;
        case QUERIES:
            OSS << "(QUERIES,\"";
            break;
        case ID:
            OSS << "(ID,\"";
            break;
        case STRING:
            OSS << "(STRING,\"";
            break;
        case COMMENT:
            OSS << "(COMMENT,\"";
            break;
        case WHITESPACE:
            break;
        case UNDEFINED:
            OSS << "(UNDEFINED,\"";
            break;
        case END_OF_FILE:
            OSS << "(EOF,\"";
            break;
        default:
            break;
    }
    OSS << value << "\"," << line << ")" << endl;
    
    return OSS.str();
}


