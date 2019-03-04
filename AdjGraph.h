//
//  AdjGraph.hpp
//  Rule Optimization
//
//  Created by Sam Hopkins on 11/30/18.
//  Copyright © 2018 Sam Hopkins. All rights reserved.
//

#ifndef AdjGraph_h
#define AdjGraph_h

#include <stdio.h>
#include "Rules.h"
#include "sstream"
#include "OptimizedRule.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <list>
#include <set>
#include <stack>

class AdjGraph {
    
//------------------- Node stuff
    struct AdjListNode
    {
        int value;
        struct AdjListNode* next;
        bool recursive;
        bool wasVisited;
    };
    
    struct AdjListHead
    {
        struct AdjListNode* head;
    };
    
    AdjListNode* newAdjListNode(int adjColumn)
    {
        AdjListNode* newNode = new AdjListNode;
        newNode->value = adjColumn;
        newNode->next = NULL;
        newNode->recursive = false;
        newNode->wasVisited = false;
        return newNode;
    }
    
    AdjListHead* addNewHeadNodeToList(int column)
    {
        AdjListHead* newHead = new AdjListHead;
        AdjListNode* head = newAdjListNode(column);
        newHead->head = head;
        return newHead;
    }
    
//----------------------------- Class stuff
public:
    AdjGraph(vector<Rule*> rules);
    void newEdge(int value, AdjListHead* headNode);
    string toString();
    vector<int> GetRuleNumbers();
    void Invert();
    void CreateDFS();
    void DFSRecursion(AdjListNode*& currNode);
    unsigned int numOfElements(AdjListNode* node);
    void DependencyDFS(stack<int> topigraphicalOrd);
    void DependencyRecursion(AdjListNode*& currNode);
    stack<int> GetTopOrder();
    vector<vector<OptimizedRule>> GetOptimizedOrder();
    bool AllNodesVisited(AdjListNode* currNode);
    
    void DeleteEverything();
    void DeleteHead(AdjListNode*& listHead);
    
private:
    map<string,vector<int>> relationNameAndColumns;
    vector<AdjListHead*> adjListContainer;
    vector<Rule*> rulesStuff;
    stack<int> topOrder;
    vector<OptimizedRule> stronglyConnectedList;
    vector<vector<OptimizedRule>> SCC;

};




#endif /* AdjGraph_hpp */
