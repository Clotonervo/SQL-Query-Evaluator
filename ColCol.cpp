/*
 Relation.cpp
 */

#include "ColCol.h"

ColCol::ColCol(string input, int indexNum)
{
    x = input;
    indexOne = indexNum;
    indexTwo = -1;
}

ColCol::ColCol(int firstCol, int secCol)
{
    x = "none";
    indexOne = firstCol;
    indexTwo = secCol;
}
