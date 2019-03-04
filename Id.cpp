/*
 Id.cpp
 */

#include "Id.h"

//----------------------------------------- Constructors and Destructors ---------------------------------------
Id::Id(vector<Token>& tokenVector)
{
    id = tokenVector.begin()->GetValue();
    TokenChecker::CheckToken(ID, tokenVector);
}

string Id::GetId()
{
    return id;
}
