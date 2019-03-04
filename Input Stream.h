/*
Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
The InputStream class is what receives the input string and parses through it character by character using a vector of char and a character location integer, recognizing each new line as well as the end of a file.
Inputs include a string that will be used by the Lexical Analyzer, labeled here as "filename" in the constructor.
Outputs inlcude giving the line number of each character being analyzed.
 */

#ifndef Input_Stream_h
#define Input_Stream_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class InputStream{
public:
    InputStream();
    InputStream(string filename);
    
    char CurrentChar();
    void Advance();
    int GetCurrentLineNumber();
    
    bool endOfFile;

private:
    unsigned int charLoc;
    vector<char> currentString;
    int currentLineNumber;
};


#endif /* Input_Stream_h */
