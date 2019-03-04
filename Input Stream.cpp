/*
 InputStream.cpp
 */

#include "Input Stream.h"

//----------------------------------------- Constructors ---------------------------------------
InputStream::InputStream()
{
    charLoc = -1;
    currentLineNumber = 0;
    endOfFile = true;
}

InputStream::InputStream(string filename)
{
    charLoc = 0;
    currentLineNumber = 1;
    for (unsigned int i = 0; i < filename.length(); i++){
        currentString.push_back(filename.at(i));
    }
    if (currentString.size() == 0){
        endOfFile = true;
    }
    else {
    endOfFile = false;
    }
}

//----------------------------------------- Current Character ---------------------------------------
char InputStream::CurrentChar()
{
    if (charLoc >= currentString.size()){
        return -1;
    }
    else {
        return currentString.at(charLoc);
    }
}

//---------------------------------- Advance to Next Character---------------------------------------
void InputStream::Advance()
{
    int const ONE_LESS = 1;
    if (charLoc >= (currentString.size() - ONE_LESS)){
        if (!endOfFile){
            currentLineNumber++;
        }
        endOfFile = true;
        return;
    }
    else if (CurrentChar() == '\n'){
        currentLineNumber++;
        charLoc++;
    }
    else {
        charLoc++;
    }
    return;
}

//----------------------------------------- Get Current Line Number ---------------------------------------
int InputStream::GetCurrentLineNumber()
{
    return currentLineNumber;
}








