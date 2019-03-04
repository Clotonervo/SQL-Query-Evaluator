/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 ...
 Input:
 Output:
 */

#ifndef ColCol_h
#define ColCol_h

#include <stdio.h>
#include <string>

using namespace std;

class ColCol {
public:
    ColCol(string input, int indexNum);
    ColCol(int firstCol, int secCol);
    
    string x;
    int indexOne;
    int indexTwo;
    
};

#endif /* ColCol_hpp */
