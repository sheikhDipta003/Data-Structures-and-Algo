#include <iostream>
#include <vector>
using namespace std;

//max-heap
// Function to swap position of two elements
void swap(int *a, int *b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}

// Function to heapify the tree
void heapify(vector<int> &hT, int i) {
  int size = hT.size();
  
  // Find the largest among root, left child and right child
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  if (l < size && hT[l] > hT[largest])
    largest = l;
  if (r < size && hT[r] > hT[largest])
    largest = r;

  // Swap and continue heapifying if root is not largest
  if (largest != i) {
    swap(&hT[i], &hT[largest]);
    heapify(hT, largest);
  }
}

// Function to build a Max-Heap from the given array
void buildHeap(vector<int>& ht)
{
    // Index of last non-leaf node
    int N = ht.size();
  
    // Perform reverse level order traversal
    // from last non-leaf node and heapify
    // each node
    for (int i = N/2 - 1; i >= 0; i--) {
        heapify(ht, i);
    }
}

// Function to insert an element into the tree
void insert(vector<int> &hT, int newNum) {
  int size = hT.size();
  if (size == 0) {
    hT.push_back(newNum);
  } else {
    hT.push_back(newNum);
    for (int i = size / 2 - 1; i >= 0; i--) {
      heapify(hT, i);
    }
  }
}

// Function to delete an element from the tree
void remove(vector<int> &hT, int num) {
  int size = hT.size();
  int i;
  for (i = 0; i < size; i++) {
    if (num == hT[i])
      break;
  }
  swap(&hT[i], &hT[size - 1]);

  hT.pop_back();
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(hT, i);
  }
}

int height(vector<int> &ht) {  //returns height of the priority queue (in number of nodes)
    if(ht.size() <= 1) return ht.size();
    int k = 0;
    for(int i = 0; i < ht.size(); ){
        k++;
        i = 2 * i + 1;
    }
    return k;
}

int extractMax(vector<int> &ht){
    int result = ht[0];
    remove(ht, result);
    return result;
}

// Print the tree
void printArray(vector<int> &hT) {
  for (int i = 0; i < hT.size(); ++i)
    cout << hT[i] << " ";
  cout << "\n";
}

// Driver code
int main() {
    vector<int> heapTree;
    heapTree.push_back(3);
    heapTree.push_back(1);
    heapTree.push_back(2);
    heapTree.push_back(4);
    buildHeap(heapTree);
    printArray(heapTree);
}
