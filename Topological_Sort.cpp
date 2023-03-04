#include <iostream>
#include <string>
#include <vector>
#include "GraphList.cpp"
using namespace std;

void printVector(vector<int> vect){
    cout << "[";
    for(int i = 0; i < vect.size(); i++){
        cout << " " << vect.at(i);
    }
    cout << " ]\n";
}

void tophelp(GraphList G, int v) { // Process vertex v
    G.setMark(v, 1);
    for (int w=G.first(v); w != -1; w = G.next(v,w))
        if (G.getMark(w) == 0)
            tophelp(G, w);
    cout << " " << v;
}
void topsort(GraphList G) { // Topological sort: recursive
    for (int i=0; i<G.n(); i++) G.setMark(i, 0);
    for (int i=0; i<G.n(); i++)
        if (G.getMark(i) == 0) 
            tophelp(G, i);
}

int main() {
    GraphList G(2);
    G.setEdge(0, 1, 10);
    G.setEdge(1, 0, 3);
    // G.setEdge(0, 3, 20);
    // G.setEdge(1, 3, 5);
    // G.setEdge(2, 1, 2);
    // G.setEdge(2, 4, 15);
    // G.setEdge(3, 4, 11);

    cout << hasCycle(&G) << endl;
    // topsort(G);
}
