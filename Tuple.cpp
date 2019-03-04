/*
 Tuple.cpp
 */

#include "Tuple.h"

Tuple::Tuple(vector<string> strings)
{
    elements = strings;
}

Tuple::Tuple(){}

Tuple::~Tuple(){};

//------------------------------------------------ Getters ----------------------------------------------------
string Tuple::GetElementAt(int index)
{
    return elements.at(index);
}

vector<string> Tuple::GetElements()
{
    return elements;
}

unsigned int Tuple::GetNumberOfElements() const
{
    return elements.size();
}
//------------------------------------------------ Deleting an element in a Tuple ----------------------------------------------------
void Tuple::DeleteElement(int index)
{
    elements.erase(elements.begin() + index);
    return;
}

void Tuple::AddElement(string x)
{
    elements.push_back(x);
    return;
}

void Tuple::AlterElementAt(string x, int index)
{
    elements.at(index) = x;
    return;
}

void Tuple::DeleteEverything()
{
    for (unsigned int i = 0; i < elements.size();){
        elements.erase(elements.begin() + i);
    }
    return;
}
//------------------------------------------------ To String ----------------------------------------------------
string Tuple::ContentsToString() const
{
    stringstream OSS;
    for(unsigned int i = 0; i < elements.size(); i++){
        OSS << elements.at(i) << "  ";
    }
    OSS << endl;
    return OSS.str();
}

string Tuple::ToString(int headerIndex) const
{
    stringstream OSS;
    
    
    
    return OSS.str();
}

