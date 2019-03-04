/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 Creates a Rule
 Inputs: a list of tokens
 Outputs: Outputs the contents of a rule via a ToString
 */

#ifndef Rule_h
#define Rule_h

#include <stdio.h>
#include <vector>
#include <sstream>
#include <string>
#include "TokenChecker.h"
#include "Token.h"
#include "HeadPredicate.h"
#include "Predicate.h"

class Rule {
public:
    Rule(vector<Token>& tokenList);
    ~Rule();
    
    HeadPredicate* GetHeadPredicate();
    vector<Predicate*> GetListOfPreds();
    
    string ToString();
private:
    HeadPredicate* headPred;
    vector<Predicate*> listOfPreds;
};

#endif /* Rule_h */
