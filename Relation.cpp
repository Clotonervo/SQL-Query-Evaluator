/*
 Relation.cpp
 */

#include "Relation.h"

Relation::Relation(Scheme* s)
{
    schema = s;
    name = schema->GetSchemeID()->GetId();
    for (unsigned int i = 0; i < schema->GetIdList().size(); i++){
        headers.push_back(schema->GetIdList().at(i)->GetId());
    }
}


//------------------------------------------------ Getters ----------------------------------------------------
Scheme* Relation::GetSchema()
{
    return schema;
}

string Relation::GetHeader(int index)
{
    return headers.at(index);
}

set<Tuple> Relation::GetTuples()
{
    return tuples;
}

vector<string> Relation::GetHeaders()
{
    return headers;
}
//------------------------------------------------ Tuple Stuff ----------------------------------------------------
void Relation::AddTuple(Fact* f)
{
    vector<string> strings;
    for (unsigned int i = 0; i < f->GetListOfStrings().size(); i++){
        strings.push_back(f->GetListOfStrings().at(i)->GetString());
    }
    Tuple newTuple = Tuple(strings);
    tuples.insert(newTuple);
    return;
}

void Relation::AddTuple(Tuple t)
{
    tuples.insert(t);
    return;
}

void Relation::SetTuples(set<Tuple> newTuples)
{
    tuples = newTuples;
    return;
}

void Relation::DeleteColumn(int x)
{
    vector<Tuple> tempTupleList;
    for(set<Tuple>::iterator iter = tuples.begin(); iter != tuples.end(); ++iter){
        Tuple tempTuple = *iter;
        tempTuple.DeleteElement(x);
        tempTupleList.push_back(tempTuple);
    }
    
    set<Tuple> newSetOfTuples;
    for (unsigned int i = 0; i < tempTupleList.size(); i++) {
        newSetOfTuples.insert(tempTupleList.at(i));
    }
    SetTuples(newSetOfTuples);
    
    return;
}

void Relation::AddColumn(string x)
{
    vector<Tuple> tempTupleList;
    for(set<Tuple>::iterator iter = tuples.begin(); iter != tuples.end(); ++iter){
        Tuple tempTuple = *iter;
        tempTuple.AddElement(x);
        tempTupleList.push_back(tempTuple);
    }
    
    set<Tuple> newSetOfTuples;
    for (unsigned int i = 0; i < tempTupleList.size(); i++) {
        newSetOfTuples.insert(tempTupleList.at(i));
    }
    SetTuples(newSetOfTuples);
    
    return;
}

//------------------------------------------------ SELECT ----------------------------------------------------
void Relation::Select(string x, int columnNumber)
{
    for(set<Tuple>::iterator iter = tuples.begin(); iter != tuples.end();){
        Tuple tempTuple = *iter;
        if (tempTuple.GetElementAt(columnNumber) != x){
            tuples.erase(tempTuple);
            iter = tuples.begin();
        }
        else {
            iter++;
        }
    }
}

void Relation::Select(int colOne, int colTwo)
{
    for(set<Tuple>::iterator iter = tuples.begin(); iter != tuples.end();){
        Tuple tempTuple = *iter;
        if (tempTuple.GetElementAt(colOne) != tempTuple.GetElementAt(colTwo)){
            tuples.erase(tempTuple);
            iter = tuples.begin();
        }
        else {
            iter++;
        }
    }
    return;
}

//------------------------------------------------ PROJECT ----------------------------------------------------
void Relation::Project(vector<string> x)                
{
    for (unsigned int i = 0; i < headers.size(); i++) {
        bool found = false;
        
        for (unsigned int j = 0; j < x.size(); j++) {
            if (x.at(j) == headers.at(i)){
                found = true;
            }
        }
        if (!found){
            headers.erase(headers.begin() + i);
            DeleteColumn(i);
            i--;
        }
    }
    
    return;
}


//------------------------------------------------ RENAME ----------------------------------------------------
void Relation::Rename(vector<ColCol> headerNames)
{
    for (unsigned int i = 0; i < headers.size(); i++) {
        headers.at(i) = headerNames.at(i).x;
    }

    return;
}


//------------------------------------------------ JOIN ----------------------------------------------------
void Relation::Join(Relation secondRelation)
{
    vector<ColCol> matchingColumns;
    set<Tuple> newTuples;
    
    for (unsigned int i = 0; i < headers.size(); i++) {
        for (unsigned int j = 0; j < secondRelation.headers.size(); j++) {
            if (headers.at(i) == secondRelation.headers.at(j)){
                matchingColumns.push_back(ColCol(i, j));
            }
        }
    }
    
    for (unsigned int i = 0; i < secondRelation.headers.size(); i++) {
        if(!CheckForDup(headers, secondRelation.headers.at(i))){
            headers.push_back(secondRelation.headers.at(i));
        }
    }
    
    JoinPartTwo(secondRelation, matchingColumns, newTuples);
    
    return;
}

//------------------------------------------------ JOIN PART 2 ----------------------------------------------------
void Relation::JoinPartTwo(Relation secondRelation, vector<ColCol> matchingColumns, set<Tuple> newTuples)
{
    vector<string> x;
    for(set<Tuple>::iterator iter = tuples.begin(); iter != tuples.end(); iter++){
        
        for(set<Tuple>::iterator iterTwo = secondRelation.tuples.begin(); iterTwo != secondRelation.tuples.end(); iterTwo++){
            
            if (isJoinable(matchingColumns, *iter, *iterTwo)) {
                newTuples.insert(combineJoinableTuples(matchingColumns, *iter, *iterTwo));
            }
            else if (iter->GetNumberOfElements() + iterTwo->GetNumberOfElements() == headers.size()){
                newTuples.insert(combineTuples(matchingColumns, *iter, *iterTwo));
            }
        }
    }

    SetTuples(newTuples);
    
    return;
}


//------------------------------------------------ Other Join Functions ----------------------------------------------------
bool Relation::isJoinable(vector<ColCol> columns, Tuple tOne, Tuple tTwo)
{
    unsigned int counter = 0;
    
    if (columns.size() == 0 || tOne.GetNumberOfElements() == 0){
        return false;
    }
    
    for(unsigned int i = 0; i < columns.size(); i++){
        if(tOne.GetElementAt(columns.at(i).indexOne) == tTwo.GetElementAt(columns.at(i).indexTwo)){
            counter++;
        }
    }
    
    if (counter == columns.size()){
        return true;
    }
    else {
        return false;
    }
}

//--------**************----- Combining tuple -----***************-------
Tuple Relation::combineTuples(vector<ColCol> columns, Tuple tOne, Tuple tTwo)
{

    if (tOne.GetNumberOfElements() + tTwo.GetNumberOfElements() == headers.size()){
        for (unsigned int i = 0; i < tTwo.GetElements().size(); i++){
            tOne.AddElement(tTwo.GetElementAt(i));
        }
        return tOne;
    }

    else {
        tOne.DeleteEverything();
        return tOne;
    }
}

//--------**************----- Combining Joinable tuples -----***************-------
Tuple Relation::combineJoinableTuples(vector<ColCol> columns, Tuple tOne, Tuple tTwo)
{
  /*  if (tOne.GetElements() == tTwo.GetElements()){
        return tOne;
    } */
    
    for (unsigned int i = 0; i < tTwo.GetElements().size(); i++){
        bool foundDup = true;
   
        for (unsigned int j = 0; j < columns.size(); j++){
            unsigned int workAround = columns.at(j).indexTwo;
            if (i == workAround){
                foundDup = false;
            }
        }
        if (foundDup){
            tOne.AddElement(tTwo.GetElementAt(i));
        }
    }

    
    return tOne;
}


//--------**************----- Checking for duplicates -----***************-------
bool Relation::CheckForDup(vector<string> x, string input)
{
    for (unsigned int i = 0; i < x.size(); i++){
        if (x.at(i) == input){
            return true;
        }
    }
    return false;
}


//------------------------------------------------ UNION ----------------------------------------------------
bool Relation::Union(Relation secondRelation)
{
    unsigned int numTuples = tuples.size();
    set<Tuple> secondRelationTuples = secondRelation.GetTuples();
    
    for(set<Tuple>::iterator iter = secondRelationTuples.begin(); iter != secondRelationTuples.end(); iter++){
        Tuple tempTuple = *iter;
        AddTuple(tempTuple);
    }
    
    if (tuples.size() != numTuples){
        return true;
    }
    else {
        return false;
    }
}

//------------------------------------------------ To String ----------------------------------------------------
string Relation::ToString() const{
    stringstream OSS;
    
    for (unsigned int i = 0; i < headers.size(); i++){
        OSS << headers.at(i) << "    ";
    }
    OSS << endl;
    for(set<Tuple>::iterator iter = tuples.begin(); iter != tuples.end(); ++iter){
        Tuple tuplePrint = *iter;
        OSS << tuplePrint.ContentsToString();
    }

    return OSS.str();
}
