/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 Checks to see the validity of a given TokenType and throws an error if invalid
 Inputs: a list of tokens and a TokenType
 Outputs: no outputs (or outputs token that causes error)
 */

#ifndef TokenChecker_h
#define TokenChecker_h

#include <stdio.h>
#include "Token.h"

class TokenChecker {
public:
    static void CheckToken(TokenType tt, vector<Token>& tokenList);
};

#endif /* TokenChecker_h */
