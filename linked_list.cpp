#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class LinkedList {
    int count;
public:
    ListNode* insert(ListNode* head, ListNode* _node, int pos){
        if(!head){
            cout << "\nList empty, new list created.";
            _node->next = nullptr;
            head = _node;
            count++;
            return head;
        }
        if(pos < 0){
            cout << "\nIndex cannot be negative, inserting at pos 0.";
            pos = 0;
        } else if(pos > count){
            cout << "\nNot enough elements, inserting at the end.";
            pos = count;
        }
        if(!pos){
            _node->next = head;
            head = _node;
            count++;
            return head;
        }
        ListNode* temp = head;
        for(int i = 0; i < pos-1; i++){
            temp = temp->next;
        }
        _node->next = temp->next;
        temp->next = _node;
        count++;
        return head;
    }
    ListNode* rotateRight(ListNode* head, int k) {  //returns head of the modified list
        if(!head || !head->next) return head;
        k = k % count;       //list is unchanged if it is rotated length() times
        for(int i=0; i < k; i++){
            ListNode* secondLast=head, *last=head->next;
            while(last->next){
                secondLast = secondLast->next;
                last = last->next;
            }
            last->next = head;
            secondLast->next = nullptr;
            head = last;
        }
        return head;
    }

    ListNode* getNode(ListNode* head, int pos){     //returns reference of a node in this list at 'pos' index
        if(pos < 0 || pos >= count) return nullptr;
        ListNode* temp = head;
        for(int i = 0; i < pos ; i++){
            temp = temp->next;
        }
        return temp;
    }

    int binSearch(ListNode* head, int key, int low, int high){  //returns the position a new 'key' must go in a sorted list
        int mid;
        while(low <= high){
            mid = (low + high) / 2;
            ListNode* temp = getNode(head, mid);
            if(temp->val < key) low++;
            else if(temp->val > key) high--;
            else return mid;
        }
        return (high+1);
    }

    void printVector(vector<int> vect){     //print node-values of the binary tree
        cout << "[";
        for(int i = 0; i < vect.size(); i++){
            cout << " " << vect.at(i);
        }
        cout << " ]\n";
    }

    ListNode* _sortList(ListNode* head) {    //returns 'head' of the sorted list (ascending) [insertion sort]
        if(count <= 1) return head;

        ListNode *p1, *p2, *min_p;
        long min;
        p1 = head;
        p2 = head;
        min_p = head;
        min = (1<<31) - 1;

        while(p1->next){        //no need to compare the last element
            while(p2){
                if(p2->val < min){
                    min = p2->val;
                    min_p = p2;
                }
                p2 = p2->next;
            }

            if(p1->val != min_p->val){  //exchange only if the values are different
                p1->val = p1->val + min_p->val;
                min_p->val = p1->val - min_p->val;
                p1->val = p1->val - min_p->val;
            }

            p1 = p1->next;
            p2 = p1;
            min_p = p1;
            min = (1<<31) - 1;
        }

        return head;
    }

    ListNode* sortList(ListNode* head) {    //returns 'head' of the sorted list (ascending) [using sort()]
        if(count <= 1) return head;

        ListNode* temp = head;
        vector<int> values;
        for(int i = 0; i < count; i++){     //O(n)
            values.push_back(temp->val);
            temp = temp->next;
        }

        sort(values.begin(), values.end());     //O(nlogn)
        // printVector(values);
        temp = head;
        for(int i = 0; i < count; i++){     //O(n)
            temp->val = values[i];
            temp = temp->next;
        }

        return head;
    }

    void printList(ListNode* head){
        ListNode* temp = head;
        cout << "\n[ ";
        for(int i = 0; i < count; i++){
            if(i < count-1) cout << temp->val << " -> ";
            else    cout << temp->val << " ]\n";
            temp = temp->next;
        }
    }
};

int main(){
    int n;
    ListNode n3(3, nullptr);
    ListNode n2(2, &n3);
    ListNode n4(4, &n2);
    ListNode* head = &n4;

    LinkedList LL;
    // LL.printList(head);
    // head = LL.rotateRight(head, 3);
    // LL.printList(head);
    // n = LL.length(head);
    // cout << LL.binSearch(head, 7, 0, n-1) << endl;
    // cout << LL.getNode(head, 3)->val << endl;
    // head = LL.sortList(head);
    // LL.printList(head);
    ListNode n1(1);
    head = LL.insert(nullptr, &n1, 5);
    LL.printList(head);
}