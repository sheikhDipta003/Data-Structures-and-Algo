// Merge sort in C++
#include <iostream>
#include <vector>
using namespace std;

void printVector(vector<int> vect){     //print node-values of the binary tree
    cout << "[";
    for(int i = 0; i < vect.size(); i++){
        cout << " " << vect.at(i);
    }
    cout << " ]\n";
}

// Merge two subarrays L and M into arr
void merge(vector<int>& arr, int p, int q, int r) {
  
  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr.at(k) = L[i];
      i++;
    } else {
      arr.at(k) = M[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr.at(k) = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr.at(k) = M[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(vector<int>& arr, int l, int r) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    // Merge the sorted subarrays
    merge(arr, l, m, r);
  }
}

void countSort(vector<int>& vect) {
  int max = -10001, N = vect.size(), min = 10001, offset;

  // Find the largest element of the array
  for (int i = 0; i < N; i++) {
      if (vect[i] > max) max = vect[i];
      if(vect[i] < min) min = vect[i];
  }
  
  offset = (min < 0) ? (-min) : 0;
  if(min < 0){  //offset all values if min < 0
      for (int i = 0; i < N; i++) {
          vect.at(i) += offset;
      }
      max += offset;
  }

  vector<int> output(max+1);
  vector<int> count(max+1);
  for (int i = 0; i < max+1; i++) {
      count.push_back(0); output.push_back(0);
  }

  // Store the count of each element
  for (int i = 0; i < N; i++) {
      count.at(vect[i])++;
  }

  // Store the cummulative count of each array
  for (int i = 1; i <= max; i++) {
      count.at(i) += count.at(i - 1);
  }

  // Find the index of each element of the original array in count array, and
  // place the elements in output array
  for (int i = N - 1; i >= 0; i--) {
      output.at(count.at(vect[i]) - 1) = vect[i];
      count.at(vect[i])--;
  }

  // Copy the sorted elements into original array
  for (int i = 0; i < N; i++) {
      vect.at(i) = output[i] - offset;
  }
}

int main(){
    vector<int> int_v;
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        int temp; cin >> temp; int_v.push_back(temp);
    }
    countSort(int_v);
    printVector(int_v);

    return 0;
}