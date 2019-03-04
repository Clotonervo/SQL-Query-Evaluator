

#include "AdjGraph.h"

//------------------------------------------------ Constructor ----------------------------------------------------
AdjGraph::AdjGraph(vector<Rule*> rules)
{
    rulesStuff = rules;
    for (unsigned int i = 0; i < rules.size(); i++) {
        vector<int> columns;
        if (relationNameAndColumns.find((rules.at(i)->GetHeadPredicate()->GetHeadPredID()->GetId())) != relationNameAndColumns.end()){
            relationNameAndColumns.at(rules.at(i)->GetHeadPredicate()->GetHeadPredID()->GetId()).push_back(i);
        }
        else {
            columns.push_back(i);
            relationNameAndColumns.insert({rules.at(i)->GetHeadPredicate()->GetHeadPredID()->GetId(), columns});
        }
    }
    
 /*   for(map<string, vector<int>>::iterator iter = relationNameAndColumns.begin(); iter != relationNameAndColumns.end(); ++iter){
        cout << iter->first << ": ";
        for (unsigned int i = 0; i < iter->second.size(); i++){
            cout << iter->second.at(i) << " ";
        }
        cout << endl;
    } */
    
    for (unsigned int i = 0; i < rules.size(); i++){
        AdjListHead* currHeadNode = addNewHeadNodeToList(i);
        for(unsigned int j = 0; j < rules.at(i)->GetListOfPreds().size(); j++){

            if (relationNameAndColumns.find(rules.at(i)->GetListOfPreds().at(j)->GetPredicateID()->GetId()) != relationNameAndColumns.end()){
                for (unsigned int k = 0; k < relationNameAndColumns.at(rules.at(i)->GetListOfPreds().at(j)->GetPredicateID()->GetId()).size(); k++){
                    newEdge(relationNameAndColumns.at(rules.at(i)->GetListOfPreds().at(j)->GetPredicateID()->GetId()).at(k), currHeadNode);
                }
            }
        }
        adjListContainer.push_back(currHeadNode);
        
    }
    
}

void AdjGraph::DeleteEverything()
{
    for (unsigned int i = 0; i < adjListContainer.size(); i++){
        DeleteHead(adjListContainer.at(i)->head);
        delete adjListContainer.at(i);
        adjListContainer.at(i) = NULL;
    }
    
    return;
}

void AdjGraph::DeleteHead(AdjListNode*& listHead)
{
    AdjListNode* currNode = listHead;
    while (currNode->next != NULL){
        DeleteHead(currNode->next);
        currNode->next = NULL;
    }
    delete listHead;
    
    return;
}

//------------------------------------------------ Adding an Edge ----------------------------------------------------
void AdjGraph::newEdge(int value, AdjListHead* headNode)
{
    AdjListNode* currNode = headNode->head;
    while(currNode->next != NULL){
        currNode = currNode->next;
        if (currNode->value == value){
            return;
        }
    }
    
    currNode->next = newAdjListNode(value);
    if(currNode->next->value == headNode->head->value){
        headNode->head->recursive = true;
    }
    
    return;
}

//------------------------------------------------ Getting Rule Numbers ----------------------------------------------------
vector<int> AdjGraph::GetRuleNumbers()
{
    vector<int> ruleNum;
    
    for (unsigned int i = 0; i < adjListContainer.size(); i++){
       ruleNum.push_back(adjListContainer.at(i)->head->value);
    }
    
    return ruleNum;
}

//------------------------------------------------ Invert ----------------------------------------------------
void AdjGraph::Invert()
{
    vector<AdjListHead*> invertedList;
    
    for (unsigned int i = 0; i < rulesStuff.size(); i++){
        AdjListHead* currHeadNode = addNewHeadNodeToList(i);
        invertedList.push_back(currHeadNode);
    }
    
    for (unsigned int i = 0; i < adjListContainer.size(); i++){
        AdjListNode* tempNode = adjListContainer.at(i)->head;
        
        while (tempNode->next != NULL){
            tempNode = tempNode->next;
            newEdge(adjListContainer.at(i)->head->value, invertedList.at(tempNode->value));
        }
    }
    DeleteEverything();
    adjListContainer = invertedList;
    
    return;
}


//------------------------------------------------ All nodes visited ----------------------------------------------------
bool AdjGraph::AllNodesVisited(AdjListNode *currNode)
{
    AdjListNode* tempNode = currNode;
    while(tempNode->next != NULL){
        tempNode = tempNode->next;
        if (adjListContainer.at(tempNode->value)->head->wasVisited == false){
            return false;
        }
    }
    
    return true;
}

//------------------------------------------------ DFS ----------------------------------------------------
void AdjGraph::CreateDFS()
{
    for(unsigned int i = 0; i < adjListContainer.size(); i++){
        if(adjListContainer.at(i)->head->wasVisited){
            continue;
        }
        else {
            DFSRecursion(adjListContainer.at(i)->head);
        }
    }
    
    return;
}

void AdjGraph::DFSRecursion(AdjListNode*& currNode)
{
    AdjListNode* nextDest = adjListContainer.at(currNode->value)->head;

  /*  if(adjListContainer.at(currNode->value)->head->wasVisited){
        if(adjListContainer.at(currNode->value)->head->next != NULL){
            DFSRecursion(nextDest);
        }
        else {
            return;
        }
    } */

    adjListContainer.at(currNode->value)->head->wasVisited = true;
    if (nextDest->next == NULL){
    }
    else if ((adjListContainer.at(nextDest->next->value)->head->wasVisited == false) && nextDest->next != NULL){
        DFSRecursion(nextDest->next);
    }
    
    if(!AllNodesVisited(nextDest)){
        while (nextDest->next != NULL){
            nextDest = nextDest->next;
            if(adjListContainer.at(nextDest->value)->head->wasVisited == false){
                DFSRecursion(nextDest);
            }
        }
    }

    topOrder.push(currNode->value);
    
    return;
}

//------------------------------------------------ Dependency DFS ----------------------------------------------------
void AdjGraph::DependencyDFS(stack<int> topigraphicalOrd)
{
    topOrder = topigraphicalOrd;
    
/*    cout << "stack:" << endl;
    for (unsigned int i = 0; i != topOrder.size();) {
        cout << topigraphicalOrd.top() << " ";
        topigraphicalOrd.pop();
    } */
    
    for (unsigned int i = 0; i != topOrder.size();) {
        DependencyRecursion(adjListContainer.at(topOrder.top())->head);
        
        if (stronglyConnectedList.size() == 0){
            topOrder.pop();
            continue;
        }
        
        SCC.push_back(stronglyConnectedList);
        stronglyConnectedList.erase(stronglyConnectedList.begin(),stronglyConnectedList.end());
        topOrder.pop();
    }
    
    return;
}

void AdjGraph::DependencyRecursion(AdjListNode*& currNode)
{
    if(adjListContainer.at(currNode->value)->head->wasVisited){
        return;
    }
    adjListContainer.at(currNode->value)->head->wasVisited = true;
    
    AdjListNode* nextDest = adjListContainer.at(currNode->value)->head;
    if ((nextDest->next != NULL) && (nextDest->next->wasVisited == false)){
        DependencyRecursion(nextDest->next);
    }
    
    if (!AllNodesVisited(currNode)){
        while(nextDest->next != NULL){
            nextDest = nextDest->next;
            if (nextDest->wasVisited == false){
                DependencyRecursion(nextDest);
            }
        }
    }
    OptimizedRule newFinalRule;
    newFinalRule.value = currNode->value;
    newFinalRule.recursive = currNode->recursive;
    stronglyConnectedList.push_back(newFinalRule);
    
    return;
}

//------------------------------------------------ List size ----------------------------------------------------
unsigned int AdjGraph::numOfElements(AdjListNode* node)
{
    unsigned int counter = 0;
    
    while (node->next != NULL){
        node = node->next;
        counter++;
    }
    
    return counter;
}

//------------------------------------------------ Get Stack ----------------------------------------------------
stack<int> AdjGraph::GetTopOrder()
{
    return topOrder;
}

vector<vector<OptimizedRule>> AdjGraph::GetOptimizedOrder()
{
    for (unsigned int i = 0; i < SCC.size(); i++){
        for (unsigned int j = 0; j < SCC.at(i).size(); j++){
            std::sort(SCC.at(i).begin(),SCC.at(i).end());
        }
    }
    return SCC;
}
//------------------------------------------------ ToString ----------------------------------------------------
string AdjGraph::toString()
{
    stringstream OSS;
    vector<vector<int>> copy;
    for (unsigned int i = 0; i < adjListContainer.size(); i++){
        vector<int> subCopy;
        AdjListNode* currNode = adjListContainer.at(i)->head;
        while(currNode->next != NULL){
            currNode = currNode->next;
            subCopy.push_back(currNode->value);
        }
        std::sort(subCopy.begin(), subCopy.end());
        copy.push_back(subCopy);
    }
    
    
    
    for (unsigned int i = 0; i < copy.size(); i++){
        OSS << "R" << adjListContainer.at(i)->head->value << ":";
        bool counter = false;

        for(unsigned int j = 0; j < copy.at(i).size(); j++){
                if (!counter){
                    OSS << "R" << copy.at(i).at(j);
                    counter = true;
                }
                else {
                    OSS << ",R" << copy.at(i).at(j);
                }
            }
        OSS << endl;
    }
    return OSS.str();
    
}
