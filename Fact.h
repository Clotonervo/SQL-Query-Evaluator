/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 Creates a single Fact, stores information in said fact
 Inputs: a list of Tokens
 Outputs: Fact information via a ToString
 */

#ifndef Fact_h
#define Fact_h

#include <stdio.h>
#include <sstream>
#include "Token.h"
#include "TokenChecker.h"
#include "Id.h"
#include "DLPString.h"

class Fact
{
public:
    Fact(vector<Token>& tokenList);
    ~Fact();
    
    Id* GetFactID();
    vector<DLPString*> GetListOfStrings();
    
    string ToString();
    
private:
    Id* factID;
    vector<DLPString*> listOfStrings;
};


#endif /* Fact_h */
