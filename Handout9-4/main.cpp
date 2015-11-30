#include <iostream>
#include "set.h"
#include "map.h"
#include "lexicon.h"
#include "queue.h"

using namespace std;

struct arcT;

struct nodeT {
    string name;
    Set<arcT *> connected;
};

struct arcT {
    nodeT * start;
    nodeT * end;
};

struct graphT {
    Set<nodeT *> allNodes;
};

void createNode(string word, graphT & graph);
void constructGraph(graphT & graph, Lexicon & lex);
Stack<nodeT *> FindShortestLaddder(graphT & graph, nodeT * start, nodeT * end);
void RecFindLongest(nodeT * node, Set<nodeT *> & visited, Stack<nodeT *> & current, Stack<nodeT *> & longest);
Stack<nodeT *> FindLongestLadder(graphT & graph, nodeT * word);

int main()
{
    Lexicon lex("lexicon.dat");
    graphT graph;
    constructGraph(graph, lex);
    Set<nodeT *>::Iterator iterNode = graph.allNodes.iterator();
//    while(iterNode.hasNext()) {
//        nodeT * currentNode = iterNode.next();
//        Set<arcT *>::Iterator iterArc = currentNode->connected.iterator();
//        cout << currentNode->name << " --> ";
//        while(iterArc.hasNext()) {
//            arcT * currentArc = iterArc.next();
//            cout << currentArc->end->name << " --> ";
//        }
//        cout << endl;
//    }
    nodeT * cat;
    nodeT * run;
    Set<nodeT *>::Iterator iter = graph.allNodes.iterator();
    while(iter.hasNext()) {
        nodeT * temp = iter.next();
        if(temp->name == "cat") {
            cat = temp;
        }
        if(temp->name == "run") {
            run = temp;
        }
    }
    Stack<nodeT *> shortestLadder = FindShortestLaddder(graph, cat, run);
    while(!shortestLadder.isEmpty()) {
        cout << shortestLadder.pop()->name << " --> ";
    }
    cout << endl;
    Stack<nodeT *> longestLadder = FindLongestLadder(graph, cat);
    while(!longestLadder.isEmpty()) {
        cout << longestLadder.pop()->name << " --> ";
    }
    return 0;
}

void createNode(string word, graphT & graph)
{
    nodeT * newNode = new nodeT;
    newNode->name = word;
    graph.allNodes.add(newNode);
}

void constructGraph(graphT & graph, Lexicon & lex)
{
    lex.mapAll<graphT>(createNode, graph);
    Map<nodeT *> wordMap;
    Set<nodeT *> ::Iterator iter = graph.allNodes.iterator();
    while(iter.hasNext()) {
        nodeT * currentNode = iter.next();
        wordMap.add(currentNode->name, currentNode);
    }
    iter = graph.allNodes.iterator();
    while(iter.hasNext()) {
        nodeT * currentNode = iter.next();
        string currentWord = currentNode->name;
        int size = currentWord.size();
        for(int i = 0; i < size; i++) {
            for(int replaceChar = 'a'; replaceChar <= 'z'; replaceChar++) {
                string newWord = currentWord.substr(0, i) + (char)replaceChar + currentWord.substr(i + 1);
                if(lex.containsWord(newWord) && newWord != currentWord) {
                    nodeT * otherNode = wordMap.get(newWord);
                    arcT * edge = new arcT;
                    edge->start = currentNode;
                    edge->end = otherNode;
                    currentNode->connected.add(edge);
                }
            }
        }
    }
}

Stack<nodeT *> FindShortestLaddder(graphT & graph, nodeT * start, nodeT * end)
{
    Queue<Stack<nodeT *>> ladders;
    Set<nodeT *> visited;
    Stack<nodeT *> startLadder;
    startLadder.push(start);
    visited.add(start);
    ladders.enqueue(startLadder);
    while(!ladders.isEmpty()) {
        Stack<nodeT *> currentLadder = ladders.dequeue();
        nodeT * currentNode = currentLadder.peek();
        if(currentNode == end) {
            return currentLadder;
        }
        Set<arcT *>::Iterator iter = currentNode->connected.iterator();
        while(iter.hasNext()) {
            arcT * currentArc = iter.next();
            if(!visited.contains(currentArc->end)) {
                Stack<nodeT *> newLadder = currentLadder;
                newLadder.push(currentArc->end);
                ladders.enqueue(newLadder);
                visited.add(currentArc->end);
            }
        }
    }
    Stack<nodeT *> emptyStack;
    return emptyStack;
}

void RecFindLongest(nodeT * node, Set<nodeT *> & visited, Stack<nodeT *> & current, Stack<nodeT *> & longest)
{
    if(visited.contains(node))
        return;
    current.push(node);
    visited.add(node);
    if(current.size() > longest.size())
        longest = current;
    Set<arcT *>::Iterator iter = node->connected.iterator();
    while(iter.hasNext()) {
        arcT * currArc = iter.next();
        RecFindLongest(currArc->end, visited, current, longest);
    }
    current.pop();
    visited.remove(node);
}

Stack<nodeT *> FindLongestLadder(graphT & graph, nodeT * word)
{
    Set<nodeT *> visited;
    Stack<nodeT *> current;
    Stack<nodeT *> longest;
    RecFindLongest(word, visited, current, longest);
    return longest;
}
