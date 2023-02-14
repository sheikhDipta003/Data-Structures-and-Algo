#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BinaryTree {
    bool isBST(TreeNode* root, long min, long max){ //helper function for isValidBST(root)
        // Base Case
        if( root == nullptr) return true;
        
        if(root->val > min && root->val < max){
            bool left = isBST(root->left,min,root->val);
            bool right = isBST(root->right, root->val, max);
            return left && right;
        }
        return false;
    }
public:
    int height(TreeNode* root) {  //returns height of the tree (in number of nodes)
        if(root == nullptr) return 0;
        else if(root->left == nullptr && root->right == nullptr) return 1;
        int d1 = height(root->left);
        int d2 = height(root->right);
        return 1 + max(d1, d2);
    }

    vector<int> preorderTraversal(TreeNode* root) {    //returns node-values in preorder sequence
        vector<int> path;
        if(root == nullptr) return path;
        path.push_back(root->val);
        if(root->left != nullptr) {
            vector<int> ret = preorderTraversal(root->left);
            path.insert(path.end(), ret.begin(), ret.end());
        }
        if(root->right != nullptr) {
            vector<int> ret = preorderTraversal(root->right);
            path.insert(path.end(), ret.begin(), ret.end());
        }
        return path;
    }

    vector<int> inorderTraversal(TreeNode* root) {    //returns node-values in inorder sequence
        vector<int> path;
        if(root == nullptr) return path;
        if(root->left != nullptr) {
            vector<int> ret = inorderTraversal(root->left);
            path.insert(path.end(), ret.begin(), ret.end());
        }
        path.push_back(root->val);
        if(root->right != nullptr) {
            vector<int> ret = inorderTraversal(root->right);
            path.insert(path.end(), ret.begin(), ret.end());
        }
        return path;
    }

    vector<int> postorderTraversal(TreeNode* root) {    //returns node-values in postorder sequence
        vector<int> path;
        if(root == nullptr) return path;
        if(root->left != nullptr) {
            vector<int> ret = postorderTraversal(root->left);
            path.insert(path.end(), ret.begin(), ret.end());
        }
        if(root->right != nullptr) {
            vector<int> ret = postorderTraversal(root->right);
            path.insert(path.end(), ret.begin(), ret.end());
        }
        path.push_back(root->val);
        return path;
    }

    /* Print nodes at a current level */
    vector<int> traverseCurrLevel(TreeNode* root, int level)
    {
        vector<int> path, temp;
        if (!root)
            return path;
        if (level == 1)
            path.push_back(root->val);
        else if (level > 1) {
            temp = traverseCurrLevel(root->left, level - 1);
            path.insert(path.end(), temp.begin(), temp.end());
            temp = traverseCurrLevel(root->right, level - 1);
            path.insert(path.end(), temp.begin(), temp.end());
        }
        return path;
    }

    /* Function to print level
    order traversal a tree*/
    vector<int> levelOrderTraversal(TreeNode* root)
    {
        int h = height(root);
        int i;
        vector<int> result, temp;
        for (i = 1; i <= h; i++)
        {
            temp = traverseCurrLevel(root, i);
            result.insert(result.end(), temp.begin(), temp.end());
        }
        return result;
    }

    TreeNode* find(TreeNode* root, int key){    //[BST only] returns ref to the node with val == key if found, null otherwise
        if(root == nullptr) return nullptr;
        if(root->val == key) return root;
        else if(root->val < key) return find(root->right, key);
        else return find(root->left, key);
    }

    TreeNode* getParentOf(TreeNode* root, int key){     //[BST only] root-> root of the whole tree(initially), key-> value of the node to find parent of
        TreeNode* temp = find(root, key);
        if(temp == nullptr) return nullptr;     //the node with (val == key) is not present in this BST
        while(root != nullptr){
            if(root->val == key) return nullptr;
            else if(root->val < key) {
                if(root->right->val == key) break;
                root = root->right;
            }
            else {
                if(root->left->val == key) break;
                root = root->left;
            }
        }
        return root;
    }

    TreeNode* predecessor(TreeNode* root, int key){   //[BST only] returns predecessor of the node with val==key
        vector<int> ret = inorderTraversal(root);
        if(ret.size() <= 1) return nullptr;
        for(int i = ret.size()-1; i >= 0; i--){
            if(ret.at(i) < key) return find(root, ret.at(i));
        }
        return nullptr;
    }

    TreeNode* successor(TreeNode* root, int key){   //[BST only] returns successor of the node with val==key
        vector<int> ret = inorderTraversal(root);
        if(ret.size() <= 1) return nullptr;
        for(int i = 0; i < ret.size(); i++){
            if(ret.at(i) > key) return find(root, ret.at(i));
        }
        return nullptr;
    }

    bool isValidBST(TreeNode* root, long LONG_MIN, long LONG_MAX) {    //returns true if this binary tree is a valid binary search tree
        return isBST(root, LONG_MIN, LONG_MAX);
    }

    int kthSmallest(TreeNode* root, int k) {    //[BST only] returns kth smallest value in a BST
        vector<int> nodeValues = inorderTraversal(root);
        return nodeValues.at(k-1);  //k starts from 1
    }

    TreeNode* deleteNode(TreeNode* root, int key) {     //[BST only], returns the modified root of the BST after deletion
        if(root){
            if(key < root->val) root->left = deleteNode(root->left, key);     //We recursively call the function until we find the target node
            else if(key > root->val) root->right = deleteNode(root->right, key);       
            else{
                if(!root->left && !root->right) return NULL;          //No child condition
                if (!root->left || !root->right)
                    return root->left ? root->left : root->right;    //One child contion -> replace the node with it's child
					                                                //Two child condition   
                TreeNode* temp = root->left;                        //(or) TreeNode *temp = root->right;
                while(temp->right != NULL) temp = temp->right;     //      while(temp->left != NULL) temp = temp->left;
                root->val = temp->val;                            //       root->val = temp->val;
                root->left = deleteNode(root->left, temp->val);  //        root->right = deleteNode(root->right, temp);		
            }
        }
        return root;
    }   

    bool isBalanced(TreeNode* root) {   //true if this binary tree is height-balanced
        if(!root) return true;
        int hL = height(root->left);
        int hR = height(root->right);
        if(abs(hL-hR) <= 1) return true;
        return false;
    }

    void printVector(vector<int> vect){     //print node-values of the binary tree
        cout << "[";
        for(int i = 0; i < vect.size(); i++){
            cout << " " << vect.at(i);
        }
        cout << " ]\n";
    }

    vector<TreeNode*> flatten(TreeNode* root) {  //[BST only] convert a BST to a right-justified linked list
        vector<int> nodes = inorderTraversal(root);
        vector<TreeNode*> list, noderefs;
        TreeNode* to_list;
        
        int n = nodes.size(); if(!n) return list;

        for(int i = 0; i < n; i++){
            noderefs.push_back(find(root, nodes.at(i)));
        }

        for(int i = 0; i < n-1; i++){
            to_list = noderefs.at(i);
            to_list->left = nullptr;
            to_list->right = noderefs.at(i+1);
            list.push_back(to_list);
        }
        to_list = noderefs.at(n-1);
        to_list->left = nullptr;
        to_list->right = nullptr;
        list.push_back(to_list);

        return list;
    }
};

int main(){
    BinaryTree t;
    TreeNode* root;
    TreeNode n2(2, nullptr, nullptr);
    TreeNode n4(4, nullptr, nullptr);
    TreeNode n7(7, nullptr, nullptr);
    TreeNode n3(3, &n2, &n4);
    TreeNode n6(6, nullptr, &n7);
    TreeNode n5(5, &n3, &n6);
    root = &n5;
    
    t.printVector(t.levelOrderTraversal(root));
    
    return 0;
}