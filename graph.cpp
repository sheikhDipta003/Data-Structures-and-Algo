#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

void print(vector<int> mark, int high){
    cout << "\n[";
    for(int i = 0; i <= high; i++){
        cout << " " << mark[i];
    }
    cout << "]\n";
}

class Solution {
    vector<int> mark;
    vector<Node*> clones;
public:
    Solution(){
        mark.resize(101, 0);
        clones.resize(101);
    }
    Node* cloneGraph(Node* node) {
        if(mark[node->val]) return node;
        Node nodecopy(node->val);
        Node* root, *temp;
        root = &nodecopy;
        mark.at(root->val) = 1;
        clones.at(root->val) = root;
        for(int i = 0; i < node->neighbors.size(); i++){
            if(!mark[node->neighbors[i]->val]){
                temp = cloneGraph(node->neighbors[i]);
                root->neighbors.push_back(temp);
            }
            else{
                root->neighbors.push_back(clones.at(i));
            }
        }
        return root;
    }
};

int main(){
    Node n1(1), n2(2), n3(3), n4(4);
    n1.neighbors.push_back(&n2); 
    n1.neighbors.push_back(&n4);
    n2.neighbors.push_back(&n1); 
    n2.neighbors.push_back(&n3);
    n3.neighbors.push_back(&n2);
    n3.neighbors.push_back(&n4);
    n4.neighbors.push_back(&n1); 
    n4.neighbors.push_back(&n3);
    Solution soln;
    soln.cloneGraph(&n1);

    return 0;
}