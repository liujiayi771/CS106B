#include "genlib.h"
#include "extgraph.h"
#include "vector.h"
#include "simpio.h"
#include "heap.h"
#include "graphics.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#define CIRCLE_RADIUS .05     // the radius of a node
#define FONT_SIZE 9           // for node name labels
#define ARC_COLOR "Dark gray" // normal arc color
#define NODE_COLOR "Black"    // normal node color
#define HIGHLIGHT_COLOR "Red" // color of chosen path/nodes
#define PAUSE_TIME .02            // time to pause when animating algorithm

struct coordT {
    double x, y;
};

struct cityT {
    coordT pos;
    string name;
};

struct arcT {
    cityT start;
    cityT end;
    double length;
};

struct pathT {
    Vector<arcT> path;
    cityT start;
    cityT end;
    int totalLength = 0;
};

struct nodeT {
    string name;
    Vector<cityT> pathName;
    double length = 0;
};

int cmpFnArc(arcT one, arcT two)
{
    if(one.length == two.length) {
        return 0;
    }
    if(one.length < two.length) {
        return 1;
    }
    return -1;
}

int cmpFnNode(nodeT one, nodeT two)
{
    if(one.length == two.length) {
        return 0;
    }
    if(one.length < two.length) {
        return 1;
    }
    return -1;
}

void reachCur(Vector<arcT> rest, string start, string end, bool & target)
{
    if(rest.size() == 0) {
        return;
    } else {
        for(int i = 0; i < rest.size(); i++) {
            if(rest[i].start.name == start) {
                if(rest[i].end.name == end) {
                    target = true;
                    return;
                }
                Vector<arcT> temp = rest;
                temp.removeAt(i);
                reachCur(temp, rest[i].end.name, end, target);
            }
            if(rest[i].end.name == start) {
                if(rest[i].start.name == end) {
                    target = true;
                    return;
                }
                Vector<arcT> temp = rest;
                temp.removeAt(i);
                reachCur(temp, rest[i].start.name, end, target);
            }
        }
    }
}

bool canReach(Vector<arcT> minTree, string start, string end)
{
    bool target = false;
    reachCur(minTree, start, end, target);
    return target;
}

void DrawFilledCircleWithLabel(coordT center, double radius, string color, string label)
{
    MovePen(center.x + radius, center.y);
    SetPenColor(color);
    StartFilledRegion(1.0);
    DrawArc(radius, 0, 360);
    EndFilledRegion();
    MovePen(center.x + radius, center.y);
    SetFont("Helvetica");
    SetPointSize(FONT_SIZE);
    DrawTextString(label);
}


void DrawLineBetween(coordT start, coordT end, string color)
{
    SetPenColor(color);
    MovePen(start.x, start.y);
    DrawLine(end.x - start.x, end.y - start.y);
}

coordT GetMouseClick()
{
    coordT where;
    WaitForMouseDown();
    WaitForMouseUp();
    where.x = GetMouseX();
    where.y = GetMouseY();
    return where;
}

void Dijkstra(Vector<cityT> cities, Vector<arcT> arcs, int size, string startCity, Vector<nodeT> & nodes)
{
    Heap<nodeT> source(cmpFnNode);
    nodeT start;
    bool tag;
    start.name = startCity;
    start.length = 0;
    cityT city;
    city.name = startCity;
    for(int i = 0; i < cities.size(); i++) {
        if(cities[i].name == startCity) {
            city.pos = cities[i].pos;
        }
    }
    start.pathName.add(city);
    source.add(start);
    while(nodes.size() != size) {
        tag = false;
        nodeT temp = source.remove(cmpFnNode);
        for(int i = 0; i < nodes.size(); i++) {
            if(nodes[i].name == temp.name) {
                tag = true;
            }
        }
        if(!tag) {
            nodes.add(temp);
        }
        for(int i = 0; i < arcs.size(); i++) {
            if(arcs[i].start.name == temp.name) {
                nodeT newCity;
                cityT newPath;
                newPath.name = arcs[i].end.name;
                for(int j = 0; j < cities.size(); j++) {
                    if(cities[j].name == arcs[i].end.name) {
                        newPath.pos = cities[j].pos;
                    }
                }
                newCity.name = arcs[i].end.name;
                newCity.length = temp.length + arcs[i].length;
                newCity.pathName = temp.pathName;
                newCity.pathName.add(newPath);
                source.add(newCity);
            } else if(arcs[i].end.name == temp.name) {
                nodeT newCity;
                cityT newPath;
                newPath.name = arcs[i].start.name;
                for(int j = 0; j < cities.size(); j++) {
                    if(cities[j].name == arcs[i].start.name) {
                        newPath.pos = cities[j].pos;
                    }
                }
                newCity.name = arcs[i].start.name;
                newCity.length = temp.length + arcs[i].length;
                newCity.pathName = temp.pathName;
                newCity.pathName.add(newPath);
                source.add(newCity);
            }
        }
    }
}

void Kruskal(Vector<arcT> arcs, Vector<arcT> & minTree, int size)
{
    Heap<arcT> source(cmpFnArc);
    for(int i = 0; i < arcs.size(); i++) {
        source.add(arcs[i]);
    }

    while(minTree.size() != size - 1) {
        arcT temp = source.remove(cmpFnArc);

        if(!canReach(minTree, temp.start.name, temp.end.name)) {
            minTree.add(temp);
        }
    }
    double sum = 0;
    for(int i = 0; i < minTree.size(); i++) {
        sum += minTree[i].length;
    }
    cout << "Total length: " << sum << endl;
}

int readFile(Vector<cityT> & cities, Vector<arcT> & arcs, string & mapname)
{
    cout << "Your options are:" << endl;
    cout << "    (1) Choose a new graph data file" << endl;
    cout << "    (2) Find shortest path using Dijkstra's algorithm" << endl;
    cout << "    (3) Compute the minimal spanning tree using Kruskal's algorithm" << endl;
    cout << "    (4) Quit" << endl;
    cout << "Enter choice: ";
    int choice = GetInteger();
    while(choice > 4 || choice < 1) {
        cout << "Please enter the correct choice" << endl;
        cout << "Enter choice: ";
        choice = GetInteger();
    }
    if(choice == 1) {
        cities.clear();
        arcs.clear();
        string filename;
        string cell;
        int nodesTag = 0;
        int arcsTag = 0;
        cityT tempCity;
        arcT tempArc;
        ifstream file_in;
        cout << "Enter the file name: ";
        filename = GetLine();
        file_in.open(filename.c_str());
        while(!file_in) {
            cout << "Please Enter the correct file name!" << endl;
            cout << "Enter the file name: ";
            filename = GetLine();
            file_in.open(filename.c_str());
        }
        file_in >> mapname;
        while(file_in >> cell) {
            if(cell == "NODES") {
                while(1) {
                    file_in >> cell;
                    if(cell == "ARCS") {
                        break;
                    }
                    if(nodesTag == 0) {
                        tempCity.name = cell;
                        nodesTag ++;
                    } else if(nodesTag == 1) {
                        tempCity.pos.x = atof(cell.c_str());
                        nodesTag ++;
                    } else {
                        tempCity.pos.y = atof(cell.c_str());
                        cities.add(tempCity);
                        nodesTag = 0;
                    }
                }
            }
            if(cell == "ARCS") {
                while(1) {
                    if(!(file_in >> cell)) {
                        break;
                    }
                    if(arcsTag == 0) {
                        for(int i = 0; i < cities.size(); i++) {
                            if(cities[i].name == cell) {
                                tempArc.start = cities[i];
                            }
                        }
                        arcsTag ++;
                    } else if(arcsTag == 1) {
                        arcsTag ++;
                    } else if(arcsTag == 2) {
                        for(int i = 0; i < cities.size(); i++) {
                            if(cities[i].name == cell) {
                                tempArc.end = cities[i];
                            }
                        }
                        arcsTag ++;
                    } else {
                        tempArc.length = atof(cell.c_str());
                        arcs.add(tempArc);
                        arcsTag = 0;
                    }
                }
            }
        }
        InitGraphics();
        SetWindowTitle("CS106 Pathfinder");
        SetWindowSize(7, 4.02);
        DrawNamedPicture(mapname);
        for(int i = 0; i < cities.size(); i++) {
            DrawFilledCircleWithLabel(cities[i].pos, 0.05, "Blue", cities[i].name);
        }
        for(int i = 0; i < arcs.size(); i++) {
            DrawLineBetween(arcs[i].start.pos, arcs[i].end.pos, "Blue");
        }
        return 1;
    } else if(choice == 2) {
        if(cities.size() == 0) {
            cout << "Please choose a graph data file first" << endl;
            return 1;
        }
        double mouseX;
        double mouseY;
        string cityName[2];
        for(int k = 0; k < 2;) {
            WaitForMouseDown();
            mouseX = GetMouseX();
            mouseY = GetMouseY();
            if(MouseButtonIsDown()) {
                for(int i = 0; i < cities.size(); i++) {
                    if(abs(cities[i].pos.x - mouseX) < 0.06 && abs(cities[i].pos.y - mouseY) < 0.06) {
                        cityName[k] = cities[i].name;
                        DrawFilledCircleWithLabel(cities[i].pos, 0.05, "Red", cities[i].name);
                        k++;
                    }
                }
            }
            WaitForMouseUp();
        }
        Vector<nodeT> nodes;
        Dijkstra(cities, arcs, cities.size(), cityName[0], nodes);
        for(int i = 0; i < nodes.size(); i++) {
            if(nodes[i].name == cityName[1]) {
                cout << "Length: " << nodes[i].length << endl;
                for(int j = 0; j < nodes[i].pathName.size(); j++) {
                    DrawFilledCircleWithLabel(nodes[i].pathName[j].pos, 0.05, "Red", nodes[i].pathName[j].name);
                    if(j != nodes[i].pathName.size() - 1) {
                        cout << nodes[i].pathName[j].name << " --> ";
                    } else {
                        cout << nodes[i].pathName[j].name << endl;
                    }
                }
                for(int j = 0; j < nodes[i].pathName.size() - 1; j++) {
                    DrawLineBetween(nodes[i].pathName[j].pos, nodes[i].pathName[j + 1].pos, "Red");
                }
            }
        }
        cout << "Click anywhere to begin" << endl;
        WaitForMouseDown();
        WaitForMouseUp();
        InitGraphics();
        SetWindowTitle("CS106 Pathfinder");
        SetWindowSize(7, 4.02);
        DrawNamedPicture(mapname);
        for(int i = 0; i < cities.size(); i++) {
            DrawFilledCircleWithLabel(cities[i].pos, 0.05, "Blue", cities[i].name);
        }
        for(int i = 0; i < arcs.size(); i++) {
            DrawLineBetween(arcs[i].start.pos, arcs[i].end.pos, "Blue");
        }
        return 1;
    } else if(choice == 3) {
        if(cities.size() == 0) {
            cout << "Please choose a graph data file first" << endl;
            return 1;
        }
        Vector<arcT> minTree;
        Kruskal(arcs, minTree, cities.size());
        InitGraphics();
        SetWindowTitle("CS106 Pathfinder");
        SetWindowSize(7, 4.02);
        DrawNamedPicture(mapname);
        for(int i = 0; i < cities.size(); i++) {
            DrawFilledCircleWithLabel(cities[i].pos, 0.05, "Blue", cities[i].name);
        }
        for(int i = 0; i < minTree.size(); i++) {
            DrawLineBetween(minTree[i].start.pos, minTree[i].end.pos, "Red");
        }
        cout << "Click anywhere to begin" << endl;
        WaitForMouseDown();
        WaitForMouseUp();
        InitGraphics();
        SetWindowTitle("CS106 Pathfinder");
        SetWindowSize(7, 4.02);
        DrawNamedPicture(mapname);
        for(int i = 0; i < cities.size(); i++) {
            DrawFilledCircleWithLabel(cities[i].pos, 0.05, "Blue", cities[i].name);
        }
        for(int i = 0; i < arcs.size(); i++) {
            DrawLineBetween(arcs[i].start.pos, arcs[i].end.pos, "Blue");
        }
        return 1;
    } else {
        return 0;
    }
}


int main()
{
    Vector<cityT> cities;
    Vector<arcT> arcs;
    string mapname;
    InitGraphics();
    while(1) {
        if(!readFile(cities, arcs, mapname)) {
            return 0;
        }
        cout << endl;
    }
    return (0);
}
