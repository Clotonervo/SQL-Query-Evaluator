/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 This creates a combination of IDs to create a single Scheme
 Inputs: a list of Tokens
 Outputs: a ToString with a combination of all the IDs located in the scheme
 */

#ifndef Scheme_h
#define Scheme_h

#include <stdio.h>
#include <vector>
#include <sstream>
#include <string>
#include "Token.h"
#include "Id.h"
using namespace std;

class Scheme{
public:
    Scheme(vector<Token>& tokenList);
    ~Scheme();
    
    Id* GetSchemeID();
    vector<Id*> GetIdList();
    
    string ToString();
private:
    Id* schemeId;
    vector<Id*> idList;
};

#endif /* Scheme_h */
