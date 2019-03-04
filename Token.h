/*
Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
The Token class recoginzes token types and outputs the correct format
Inputs include TokenTypes (what token) and the actual string, as well as the line number each token is located on
Outputs include the token type, the actual tokena as seen on the input, and the line number it is located on. Ex: (COMMA,",",2)
*/

#ifndef Token_h
#define Token_h

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE, UNDEFINED, END_OF_FILE};

class Token {
public:
    Token();
    Token(TokenType tt, string one, int lineNum);
    TokenType GetTokenType();
    string GetValue();
    
    string ToString();

private:
    int line;
    string value;
    TokenType tt;
};

#endif /* Token_hpp */
