/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 ...
 Input:
 Output:
 */

#ifndef Tuple_h
#define Tuple_h

#include "vector"
#include "string"
#include "DLPString.h"
#include <iostream>
#include <sstream>


using namespace std;

class Tuple {
public:
    Tuple(vector<string> strings);
    Tuple();
    ~Tuple();
    
    vector<string> GetElements();
    unsigned int GetNumberOfElements() const;
    string GetElementAt(int index);
    void DeleteElement(int index);
    void DeleteEverything();
    void AddElement(string x);
    void AlterElementAt(string x, int index);
    
    string ContentsToString() const;
    string ToString(int headerIndex) const;

    bool operator< (const Tuple t) const {
        return elements < t.elements;
    }
    
private:
    vector<string> elements;
    
};

#include <stdio.h>

#endif /* Tuple_h */
