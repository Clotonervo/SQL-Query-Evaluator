/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 The Data Log Program parses through a list of tokens using a defined grammer to determine validity and the objects that are defined in a given input
 Input: a list of Tokens
 Output: outputs to a ToString the values of the Schemes, Facts, Rules, Queries and Domains onto the command consol
 */

#ifndef DatalogProgram_h
#define DatalogProgram_h

#include <stdio.h>
#include <vector>
#include <set>
#include <iostream>
#include "Token.h"
#include "Schemes.h"
#include "Facts.h"
#include "Rules.h"
#include "Queries.h"

using namespace std;


class DataLog {
public:
    DataLog(vector<Token>& tokenInput);
    ~DataLog();
    
    TokenType GetTokenType();
    string GetValue();
    void makeDomains(vector<Token> tokenInput);
    
    string ToString();
    string DomainToString();
    vector<Token> tokenList;
    
    Schemes* GetSchemes();
    Facts* GetFacts();
    Rules* GetRules();
    Queries* GetQueries();
    
private:
    int frontIndex;
    int index;
    Schemes* schemesStuff;
    Facts* factsStuff;
    Rules* rulesStuff;
    Queries* queriesStuff;
    set<string> domainStuff;
};

#endif /* DatalogProgram_h */
