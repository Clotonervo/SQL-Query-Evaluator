/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 Stores the values of multiple Facts
 Inputs: a list of Tokens
 Outputs: All Fact information via a ToString
 */
#ifndef Facts_h
#define Facts_h

#include <stdio.h>
#include "Token.h"
#include "Fact.h"
#include <sstream>
#include <set>
using namespace std;

class Facts
{
public:
    Facts(vector<Token>& tokenList);
    ~Facts();
    
    vector<Fact*> GetFactList();
    
    string ToString();
    
private:
    vector<Fact*> listOfFacts;
};
#endif /* Facts_h */
