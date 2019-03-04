/*
 Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net
 ...
 Input:
 Output:
 */

#ifndef Database_h
#define Database_h

#include <stdio.h>
#include <map>
#include <vector>
#include <iostream>
#include "Schemes.h"
#include "Facts.h"
#include "Rules.h"
#include "Queries.h"
#include "Relation.h"
#include "ColCol.h"
#include "AdjGraph.h"
#include "OptimizedRule.h"

class Database {
public:
    Database();
    
    void CreateDatabase(Schemes* s, Facts* f, Queries* q, Rules* r);
    
    void EvaluateRules();
    void EvaluateQueries();
    Relation EvaluatePredicates(Predicate* p);
    vector<Relation> GetListOfPredicates(Rule* r);
    set<Tuple> OrderColumns(Relation finalRelation, vector<ColCol> headCol);
    void EvaluateRulesPartTwo(Relation finalRelation, vector<ColCol> headCol, set<Tuple> testTuples, vector<string> ruleCol, Rule* rule);
    void Optimization();
    void OptimizedRuleEval(vector<OptimizedRule> currSet);
    void OptimizedRuleRecursionTest(vector<OptimizedRule> currSet);
    
    bool CheckForDuplicates(vector<ColCol>& v, string x);
    int GetDupColNum(vector<ColCol>& v, string x);
    bool CheckParameters(Parameter* p);
    
    string ToString();
    string QueryToString(Relation r, Query* q);
    int rulesCounter;
    
private:
    map<string,Relation> relations;
    vector<Scheme*> schemes;
    vector<Fact*> facts;
    vector<Rule*> rules;
    vector<Query*> queries;
    bool changeFound;
    bool alreadyRecursed;
    vector<vector<OptimizedRule>> optimizedOrder;
};



#endif /* Database_h */
