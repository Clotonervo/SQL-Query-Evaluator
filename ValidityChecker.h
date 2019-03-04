/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 The Validity checker parses through the input and ensures that it is part of the language before allowing the Datalog to make the final check. (this is a fix for memory leaks)
 Input: a list of Tokens
 Output: No output
 */

#ifndef ValidityChecker_h
#define ValidityChecker_h

#include <stdio.h>
#include <vector>
#include <set>
#include <iostream>
#include "Token.h"

class ValidityChecker {
public:
    ValidityChecker(vector<Token> tokenInput);
    
    void BigParser();
    void SchemesParser();
    void SchemeListParser();
    void FactsParser();
    void FactsList();
    void RulesParser();
    void RulesList();
    void QueriesParser();
    
    void PredicateParser();
    void HeadPredicateParser();
    void ParameterParser();
    void ExpressionParser();
    
    void TokenChecker(Token x, TokenType tt);
    
private:
    int index;
    vector<Token> tokenList;
};

#endif /* ValidityChecker_h */
