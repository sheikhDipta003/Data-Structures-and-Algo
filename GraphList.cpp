#include <iostream>
#include <vector>
using namespace std;

class Edge {
    int v, wt;

public:
    Edge(){
        v = -1;
        wt = 0;
    }

    Edge(int v, int w) {
        this->v = v; wt = w;
    }

    int vertex() {
        return this->v;
    }

    int weight() {
        return wt;
    }
    void setVertex(int v){this->v = v;}
    void setWeight(int wt){this->wt = wt;}
};

class GraphList {
    vector<vector<Edge>> lst;
    int numEdge;
    vector<int> Color;
    vector<int> Mark;

public:
    GraphList(int n = 5){
        lst.resize(n);
        for(int i = 0; i < n; i++){
            lst.at(i).resize(n);
            for(int j = 0; j < n; j++){
                lst.at(i).at(j) = Edge();
            }
        }
        Mark.resize(n, 0);
        Color.resize(n, 0);
    }


    int n() {
        return lst.size();
    }


    int e() {
        return numEdge;
    }


    int first(int v) {      //returns the first neighbor of vertex 'v'
        vector<Edge> temp = lst.at(v);
        if(temp.size() <= 1)    return -1;
        return temp.at(1).vertex();
    }


    int next(int v, int w) {    //returns the vertex next to 'w' in 'v's neighbor list
        vector<Edge> temp = lst.at(v);
        if(temp.size() <= 1)    return -1;

        for(int k = 1; k < temp.size(); k++){
            if(temp.at(k).vertex() == w)   {
                if(k+1 >= temp.size())  break;
                return temp.at(k+1).vertex();
            }
        }

        return -1;
    }
    
    bool isEdge(int i, int j) {      //'true' if there is an edge between vertices 'i' and 'j'
        vector<Edge> temp = lst.at(i);
        if(temp.size() <= 1)    return false;
        for(int k = 1; k < temp.size(); k++){
            if(temp.at(k).vertex() == j)   return true;
        }
        return false;
    }

    void setEdge(int i, int j, int w) { //sets an edge of weight 'w' between vertices 'i' and 'j'
        if(!isEdge(i, j))    numEdge++;
        lst.at(i).at(j).setVertex(j);
        lst.at(i).at(j).setWeight(w);
    }


    void delEdge(int i, int j) {    //deletes the edge (if exists) between vertices 'i' and 'j'
        if(isEdge(i, j))    numEdge--;
        vector<Edge> temp = lst.at(i);
        for(int k = 1; k < temp.size(); k++){
            if(temp.at(k).vertex() == j)   temp.erase(temp.begin()+k);
        }
    }

    int weight(int i, int j) {      //returns the weight of the edge between 'i' and 'j'
        vector<Edge> temp = lst.at(i);
        for(int k = 1; k < temp.size(); k++){
            if(temp.at(k).vertex() == j)   return temp.at(k).weight();
        }
        return -1;
    }

    void setMark(int v, int val) { Mark.at(v) = val; }
    int getMark(int v) { return Mark[v]; }

    int getColor(int v) {
        return Color[v];
    }
    void setColor(int v, int c) {
        Color.at(v) = c;
    }
    
    void print(){
        int n = lst.size();
        cout << "\n";
        for(int i = 0; i < n; i++){
            cout << i << ":";
            for(int j = 0; j < n; j++){
                cout << " " << lst[i][j].weight();
            }
            cout << endl;
        }
    }

};

// int main() {
//     GraphList G(5);
//     G.setEdge(0, 1, 10);
//     G.setEdge(0, 2, 3);
//     G.setEdge(0, 3, 20);
//     G.setEdge(1, 3, 5);
//     G.setEdge(2, 1, 2);
//     G.setEdge(2, 4, 15);
//     G.setEdge(3, 4, 11);
//     G.print();
    
//     return 0;
// }

