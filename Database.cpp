/*
 Database.cpp
 */

#include "Database.h"

Database::Database(){}

//------------------------------------------------ Creating the Database ----------------------------------------------------
void Database::CreateDatabase(Schemes* s, Facts* f, Queries* q, Rules* r)
{
    schemes = s->GetSchemesList();
    facts = f->GetFactList();
    rules = r->GetRulesList();
    queries = q->GetQueries();
    rulesCounter = 0;
    changeFound = false;
    alreadyRecursed = false;
    
    for (unsigned int i = 0; i < schemes.size(); i++){
        relations.insert({schemes.at(i)->GetSchemeID()->GetId(), Relation(schemes.at(i))});
    }
    
    for (unsigned int i = 0; i < facts.size(); i++){
        relations.at(facts.at(i)->GetFactID()->GetId()).AddTuple(facts.at(i));
    }
    
    return;
}

//------------------------------------------------ Optimization of Rules ----------------------------------------------------
void Database::Optimization()
{
    AdjGraph dependencyGraph(rules);
    cout << "Dependency Graph" << endl;

    cout << dependencyGraph.toString() << endl;
    vector<int> ruleNumbers;
    ruleNumbers = dependencyGraph.GetRuleNumbers();
    
    AdjGraph mustBeExecutedBeforeGraph(rules);
    mustBeExecutedBeforeGraph.Invert();
   // cout << "inverted:" << endl;
   // cout << mustBeExecutedBeforeGraph.toString() << endl;
    mustBeExecutedBeforeGraph.CreateDFS();
    
    dependencyGraph.DependencyDFS(mustBeExecutedBeforeGraph.GetTopOrder());
    
    optimizedOrder = dependencyGraph.GetOptimizedOrder();
    
 /*   for(unsigned int i = 0; i < optimizedOrder.size(); i++){
        cout << i << ": ";

        for(unsigned int j = 0; j < optimizedOrder.at(i).size(); j++){
            cout << optimizedOrder.at(i).at(j) << " ";
        }
        cout << endl;
    } */

    cout << "Rule Evaluation" << endl;
    for(unsigned int i = 0; i < optimizedOrder.size(); i++){
        rulesCounter = 0;
        alreadyRecursed = false;
        OptimizedRuleEval(optimizedOrder.at(i));
   /*     rulesCounter--;
        if (rulesCounter == 0){
            rulesCounter++;
        }*/
        cout << rulesCounter << " passes: ";
        int counter = 0;
        for (unsigned int j = 0; j < optimizedOrder.at(i).size(); j++){
            if(counter == 0){
            cout << "R" << optimizedOrder.at(i).at(j).value;
            counter++;
            }
            else {
                cout << ",R" << optimizedOrder.at(i).at(j).value;
            }
        }
        cout << endl;
    }
    cout << endl;
    
    dependencyGraph.DeleteEverything();
    mustBeExecutedBeforeGraph.DeleteEverything();

    return;
}

//--------------------------------- Optimized rule eval -----------------------------------------
void Database::OptimizedRuleEval(vector<OptimizedRule> currSet)
{
    changeFound = false;
    for(unsigned int i = 0; i < currSet.size(); i++){
        vector<Relation> ruleRelations;
        vector<string> ruleCol;
        vector<ColCol> headCol;
        int currIndex = currSet.at(i).value;
        for (unsigned int j = 0; j < rules.at(currIndex)->GetHeadPredicate()->GetIDList().size(); j++){ //Getting predicate list
            ruleCol.push_back(rules.at(currIndex)->GetHeadPredicate()->GetIDList().at(j)->GetId());
        }
        
        ruleRelations = GetListOfPredicates(rules.at(currIndex));
        
        
        for(unsigned int j = 1; j < ruleRelations.size(); j++){ //Joining all the predicates
            ruleRelations.at(0).Join(ruleRelations.at(j));
        }
        
        Relation finalRelation = ruleRelations.at(0);
        
        finalRelation.Project(ruleCol);       //projecting final relation
        
        for(unsigned int j = 0; j < finalRelation.GetHeaders().size(); j++){    //getting column pairs
            for(unsigned int k = 0; k < ruleCol.size(); k++){
                if(ruleCol.at(k) == finalRelation.GetHeaders().at(j)){
                    headCol.push_back(ColCol(k, j));
                }
            }
        }
        
        set<Tuple> testTuples = OrderColumns(finalRelation, headCol);
        EvaluateRulesPartTwo(finalRelation, headCol, testTuples, ruleCol, rules.at(currIndex));
        
    /*    if(currSet.at(i).recursive && !alreadyRecursed){
            alreadyRecursed = true;
            rulesCounter++;
            OptimizedRuleEval(currSet);
        }*/
    }
    rulesCounter++;
    OptimizedRuleRecursionTest(currSet);
    
    return;
}

void Database::OptimizedRuleRecursionTest(vector<OptimizedRule> currSet)
{
    if(currSet.size() == 1 && currSet.at(0).recursive == false){
        return;
    }
    else if (changeFound){
        OptimizedRuleEval(currSet);
    }
    
   /* else {
        for(unsigned int i = 0; i < currSet.size(); i++){
            if(currSet.at(i).recursive && !alreadyRecursed){
                alreadyRecursed = true;
                OptimizedRuleEval(currSet);
                return;
            }
        }
    }*/
    
    
    
    return;
}



//------------------------------------------------ Evaluating Rules ----------------------------------------------------
void Database::EvaluateRules()
{
    changeFound = false;
    for(unsigned int i = 0; i < rules.size(); i++){
            vector<Relation> ruleRelations;
            vector<string> ruleCol;
            vector<ColCol> headCol;
            for (unsigned int j = 0; j < rules.at(i)->GetHeadPredicate()->GetIDList().size(); j++){ //Getting predicate list
                ruleCol.push_back(rules.at(i)->GetHeadPredicate()->GetIDList().at(j)->GetId());
            }
            
            ruleRelations = GetListOfPredicates(rules.at(i));

            
            for(unsigned int j = 1; j < ruleRelations.size(); j++){ //Joining all the predicates
                ruleRelations.at(0).Join(ruleRelations.at(j));
            }
            
            Relation finalRelation = ruleRelations.at(0);

            finalRelation.Project(ruleCol);       //projecting final relation
            
            for(unsigned int j = 0; j < finalRelation.GetHeaders().size(); j++){    //getting column pairs
                for(unsigned int k = 0; k < ruleCol.size(); k++){
                    if(ruleCol.at(k) == finalRelation.GetHeaders().at(j)){
                        headCol.push_back(ColCol(k, j));
                    }
                }
            }
            
            set<Tuple> testTuples = OrderColumns(finalRelation, headCol);
        EvaluateRulesPartTwo(finalRelation, headCol, testTuples, ruleCol, rules.at(i));
        
    }
    rulesCounter++;
    if (changeFound){
        EvaluateRules();
    }
    
    return;
}

//-----------------------------------------------------------------------------------------
void Database::EvaluateRulesPartTwo(Relation finalRelation, vector<ColCol> headCol, set<Tuple> testTuples, vector<string> ruleCol, Rule* rule)
{
    headCol.clear();
    finalRelation.SetTuples(testTuples);
    
    for (unsigned int j = 0; j < ruleCol.size(); j++){
        headCol.push_back(ColCol(ruleCol.at(j), j));
    }
    
    finalRelation.Rename(headCol); //renaming column headers
    if (!changeFound){
        changeFound = relations.at(rule->GetHeadPredicate()->GetHeadPredID()->GetId()).Union(finalRelation);
        
    }
    else {
        relations.at(rule->GetHeadPredicate()->GetHeadPredID()->GetId()).Union(finalRelation);
    }

    return;
}
    


//---------***************----------- Getting a list of Predicates ----------***************--------
vector<Relation> Database::GetListOfPredicates(Rule *r)
{
    vector<Relation> ruleRelations;
    for(unsigned int j = 0; j < r->GetListOfPreds().size(); j++){
        Relation rel(EvaluatePredicates(r->GetListOfPreds().at(j))); 
        ruleRelations.push_back(rel);
    }
    
    return ruleRelations;
}


//--------***************------- Ordering Columns --------***************--------
set<Tuple> Database::OrderColumns(Relation finalRelation, vector<ColCol> headCol)
{
    set<Tuple> alteredTuples;
    set<Tuple> testTuples = finalRelation.GetTuples();
    
    for(set<Tuple>::iterator iter = testTuples.begin(); iter != testTuples.end(); iter++){
        Tuple tempTuple = *iter;
        vector<string> finalTuple = tempTuple.GetElements();
        vector<string> oneTuple = tempTuple.GetElements();
        
        for(unsigned int j = 0; j < headCol.size(); j++){
            finalTuple.at(headCol.at(j).indexOne) = oneTuple.at(headCol.at(j).indexTwo);
        }
        alteredTuples.insert(finalTuple);
    }
    
    return alteredTuples; 
}



//------------------------------------------------ Evaluating Predicates ----------------------------------------------------
Relation Database::EvaluatePredicates(Predicate* p)
{
    vector<Parameter*> parameters;
    vector<ColCol> parameterIds;
    vector<string> headers;
    string relationName;
    int firstCol = 0;
    
    relationName = p->GetPredicateID()->GetId();
    parameters = p->GetListOfParameters();
    Relation r(relations.at(relationName).GetSchema());
    r.SetTuples(relations.at(relationName).GetTuples());
    
    if (parameters.size() > r.GetHeaders().size()){
        set<Tuple> emptyTuples;
        emptyTuples.clear();
        r.SetTuples(emptyTuples);
        return r;
    }
    
    for (unsigned int j = 0; j < parameters.size(); j++) {
        if(CheckParameters(parameters.at(j))){
            
            r.Select(parameters.at(j)->GetParameterString()->GetString(), j);
        }
        else {
            if (CheckForDuplicates(parameterIds, parameters.at(j)->GetParameterID()->GetId())){
                firstCol = GetDupColNum(parameterIds, parameters.at(j)->GetParameterID()->GetId());
                r.Select(firstCol, j);
            }
            else {
                parameterIds.push_back(ColCol(parameters.at(j)->GetParameterID()->GetId(), j));
                headers.push_back(r.GetHeader(j));
            }
        }
    }
    r.Project(headers);
    
    r.Rename(parameterIds);
    
    return r;
}


//------------------------------------------------ Evaluating Queries ----------------------------------------------------
void Database::EvaluateQueries()
{
    for (unsigned int i = 0; i < queries.size(); i++) {
        vector<Parameter*> parameters;
        vector<ColCol> parameterIds;
        vector<string> headers;
        string relationName;
        int firstCol = 0;
        
        relationName = queries.at(i)->GetPredicate()->GetPredicateID()->GetId();
        parameters = queries.at(i)->GetPredicate()->GetListOfParameters();
        Relation r(relations.at(relationName).GetSchema());
        r.SetTuples(relations.at(relationName).GetTuples());
        
        if (parameters.size() > r.GetHeaders().size()){
            set<Tuple> emptyTuples;
            emptyTuples.clear();
            r.SetTuples(emptyTuples);
            cout << QueryToString(r, queries.at(i));
            return;
        }
        
        for (unsigned int j = 0; j < parameters.size(); j++) {
            if(CheckParameters(parameters.at(j))){
                
                r.Select(parameters.at(j)->GetParameterString()->GetString(), j);               
            }
            else {
                if (CheckForDuplicates(parameterIds, parameters.at(j)->GetParameterID()->GetId())){
                    firstCol = GetDupColNum(parameterIds, parameters.at(j)->GetParameterID()->GetId());
                    r.Select(firstCol, j);
                }
                else {
                    parameterIds.push_back(ColCol(parameters.at(j)->GetParameterID()->GetId(), j));
                    headers.push_back(r.GetHeader(j));
                }
            }
        }
        r.Project(headers);
        
        r.Rename(parameterIds);
        
        cout << QueryToString(r, queries.at(i));
        
    }
    return;
}

//------------------------------------------------ Checking for Duplicates ----------------------------------------------------
bool Database::CheckForDuplicates(vector<ColCol>& v, string testString)
{
    for (unsigned int i = 0; i < v.size(); i++) {
        if (v.at(i).x == testString){
            return true;
        }
    }
    return false;
}

//------------------------------------------------ Getting the Duplicate Column Number ----------------------------------------------------
int Database::GetDupColNum(vector<ColCol> &v, string testString)
{
    for (unsigned int i = 0; i < v.size(); i++) {
        if (v.at(i).x == testString){
            return v.at(i).indexOne;
        }
    }
    return -1;
}

//------------------------------------------------ Checking Parameter Types ----------------------------------------------------
bool Database::CheckParameters(Parameter* p)
{
    if (p->GetParameterTokenType() == STRING){
        return true;
    }
    else {
        return false;
    }    
}

//------------------------------------------------ To String ----------------------------------------------------
string Database::ToString()
{
    stringstream OSS;
    
    for(map<string, Relation>::iterator it = relations.begin(); it != relations.end(); ++it){
        cout << it->first << endl << it->second.ToString();
    }
    return OSS.str();
}

string Database::QueryToString(Relation r, Query* q)
{
    stringstream OSS;
    
    cout << q->ToString();
    
    if(r.GetTuples().size() == 0){
        OSS << " No" << endl;
    }
    else {
        cout << " Yes(" << r.GetTuples().size() << ")" << endl;
        set<Tuple> tempTuples = r.GetTuples();
        set<Tuple>:: iterator iter = tempTuples.begin();
        
        if ((tempTuples.size() == 1) && (iter->GetNumberOfElements() == 0)){
            return OSS.str();
        }
        else {
            for(iter = tempTuples.begin(); iter != tempTuples.end(); ++iter){
                Tuple temporaryTuple = *iter;
                for (unsigned int i = 0; i < r.GetHeaders().size(); i++) {
                    if (i == 0){
                        cout << "  " << r.GetHeader(i) << "=" << temporaryTuple.GetElementAt(i);
                    }
                    else {
                        cout << ", " << r.GetHeader(i) << "=" << temporaryTuple.GetElementAt(i);
                    }
                }
                cout << endl;
            }
        }
    }
    
    
    return OSS.str();
}
