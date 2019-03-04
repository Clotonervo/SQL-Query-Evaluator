/*
Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
The Lex class is the Lexical Analyzer that uses the InputStream class to parse through a given string to recognize tokens, and creates a Token class for each token found. As shown, Lex is a finite state machine that contains multiple methods as "states" through which tokens are determined.
Inputs are given by the InputStream class in the form of characters (as seen in the constructor)
Outputs include a Token class (which is then output using the Token's toString method).
 */

#ifndef Lex_h
#define Lex_h

#include <stdio.h>
#include <vector>
#include "Token.h"
#include "Input Stream.h"
using namespace std;

class Lex {
public:
    Lex();
    Lex(string inputString);
    ~Lex();
    
    void CreateToken(TokenType type, string tokenString);
    void CreateMultiLineToken(TokenType type, string tokenString, int beginLineNum);

    void StartState();
    void CharacterState();
    void CharacterStatePartTwo();
    
    void CommaState();
    void PeriodState();
    void QMarkState();
    void LeftParenState();
    void RightParenState();
    void ColonState();
    void ColonDashState();
    void MultiplyState();
    void AddState();
    
    void SchemesState();
    void FactsState();
    void RulesState();
    void QueriesState();
    
    void IDState();
    void StringState();
    void EndStringState();
    
    void CommentState();
    void SingleLineState();
    void BlockCommentState();
    void SawBarState();
    
    void EndOfFileState();
    
    void ErrorState();
    
    vector<Token> tokenList;
    InputStream* istream;

protected:
    string valueSoFar;
    bool isString;
    bool isComment;
    int lineMarker;
};




#endif /* Lex_h */
