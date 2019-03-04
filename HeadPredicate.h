/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 Creates a HeadPredicate object
 Inputs: a list of tokens
 Outputs: elements located in a HeadPredicate via a ToString
 */

#ifndef HeadPredicate_h
#define HeadPredicate_h

#include <stdio.h>
#include <vector>
#include <sstream>
#include <string>
#include "Token.h"
#include "Id.h"

class HeadPredicate {
public:
    HeadPredicate(vector<Token>& tokenList);
    ~HeadPredicate();
    
    Id* GetHeadPredID();
    vector<Id*> GetIDList();
    
    string ToString();
    
private:
    Id* headPredicateID;
    vector<Id*> idList;
};

#endif /* HeadPredicate_hpp */
