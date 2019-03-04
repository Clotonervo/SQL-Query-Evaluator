/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 This program creates a list of Rule objects to be stored and outputed
 Inputs: a list of tokens
 Outputs: outputs the list of Rule objects via a ToString
 */

#ifndef Rules_h
#define Rules_h

#include <stdio.h>
#include <sstream>
#include "Rule.h"
#include "Token.h"
#include "TokenChecker.h"
class Rules {
public:
    Rules(vector<Token>& tokenList);
    ~Rules();
    
    vector<Rule*> GetRulesList();
    
    string ToString();
    
private:
    vector<Rule*> listOfRules;
};

#endif /* Rules_h */
