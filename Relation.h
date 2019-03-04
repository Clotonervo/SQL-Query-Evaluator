/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 ...
 Input:
 Output:
 */
#ifndef Relation_h
#define Relation_h

#include <stdio.h>
#include <iostream>
#include <set>
#include "Relation.h"
#include "Scheme.h"
#include "Fact.h"
#include "Id.h"
#include "Tuple.h"
#include "ColCol.h"

class Relation {
public:
    Relation(Scheme* s);
    
    void AddTuple(Fact* f);
    void AddTuple(Tuple t);
    void SetTuples(set<Tuple> newTuples);
    
    Scheme* GetSchema();
    string GetHeader(int index);
    set<Tuple> GetTuples();
    vector<string> GetHeaders();
    
    bool CheckForDup(vector<string> x, string input);
    bool isJoinable(vector<ColCol> columns, Tuple tOne, Tuple tTwo);
    Tuple combineTuples(vector<ColCol> columns, Tuple tOne, Tuple tTwo);
    Tuple combineJoinableTuples(vector<ColCol> columns, Tuple tOne, Tuple tTwo);
    
    void DeleteColumn(int x);
    void AddColumn(string x);
    
    void Select(string x, int columnNumber);
    void Select(int colOne, int colTwo);
    void Project(vector<string> x);
    void Rename(vector<ColCol> headerNames);
    void Join(Relation secondRelation);
    void JoinPartTwo(Relation secondRelation, vector<ColCol> matchingColumns, set<Tuple> newTuples);
    bool Union(Relation secondRelation);

    string ToString() const;
private:
    string name;
    Scheme* schema;
    set<Tuple> tuples;
    vector<string> headers;
};

#endif /* Relation_hpp */
