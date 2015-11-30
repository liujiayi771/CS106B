#include <iostream>
#include "set.h"

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

bool RecIsCyclic(nodeT * currentNode, nodeT * targetNode, int hops, Set<nodeT *> &visited) {

    if (hops > 2 && currentNode == targetNode)
        return true;

    if (currentNode != targetNode)
        visited.add(currentNode);

    Set<arcT *>::Iterator itr = currentNode->connected.iterator();

    while (itr.hasNext()) {
        arcT * link = itr.next();
        cout << " Link is (" << hops+1 << ") : " << link->end->name << endl;
        if (!visited.contains(link->end) && !(hops+1 < 3 && link->end == targetNode)) {
            cout << " Checking: " << link->end->name << endl;
            if (RecIsCyclic(link->end, targetNode, hops+1, visited))
                return true;
        }
    }
    return false;
}

bool IsCyclicGraph(graphT & graph) {

    Set<nodeT *>::Iterator itr = graph.allNodes.iterator();

    while (itr.hasNext()) {
        nodeT * currentNode = itr.next();
        Set<nodeT *> visited;
        cout << "Node is: " << currentNode->name << endl;
        if (RecIsCyclic(currentNode, currentNode, 0, visited))
            return true;
    }
    return false;
}

int main()
{
    graphT graph;
    nodeT * n1 = new nodeT;
    nodeT * n2 = new nodeT;
    nodeT * n3 = new nodeT;
    nodeT * n4 = new nodeT;
    nodeT * n5 = new nodeT;
    arcT * a1 = new arcT;
    arcT * a2 = new arcT;
    arcT * a3 = new arcT;
    arcT * a4 = new arcT;
    arcT * a5 = new arcT;
    a1->start = n1;
    a1->end = n2;
    a2->start = n2;
    a2->end = n3;
    a3->start = n3;
    a3->end = n4;
    a4->start = n4;
    a4->end = n5;
    a5->start = n5;
    a5->end = n1;
    n1->name = "n1";
    n1->connected.add(a1);
    n1->connected.add(a5);
    n2->name = "n2";
    n2->connected.add(a2);
    n2->connected.add(a1);
    n3->name = "n3";
    n3->connected.add(a2);
    n3->connected.add(a3);
    n4->name = "n4";
    n4->connected.add(a4);
    n4->connected.add(a3);
    n5->name = "n5";
    n5->connected.add(a5);
    n5->connected.add(a4);
    graph.allNodes.add(n1);
    graph.allNodes.add(n2);
    graph.allNodes.add(n3);
    graph.allNodes.add(n4);
    graph.allNodes.add(n5);
    if(IsCyclicGraph(graph)) {
        cout << "Has cycle!" << endl;
    } else {
        cout << "Does not have cycle!" << endl;
    }
    return 0;
}
