/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 Stores ID Tokens and checks them to see if they are valid
 Input: a list of Tokens
 Output: the ID value in the form of a string
 */

#ifndef Id_h
#define Id_h

#include <stdio.h>
#include "TokenChecker.h"
#include "Token.h"
class Id {
public:
    Id(vector<Token>& tokenVector);
    string GetId();
    
private:
    string id;
};

#endif /* Id_h */
