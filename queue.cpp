#include <iostream>
#include <vector>
using namespace std;

// Singly qNodeed list node
class qNode {
public:
    int val; // Value for this node
    qNode *next; // Pointer to next node in list
    // Constructors
    qNode(const int& _val, qNode* nextval =nullptr)
    { val = _val; next = nextval; }

    qNode(qNode* nextval =nullptr) { next = nextval; }
};

// qNodeed queue implementation
class Queue {
private:
    qNode* front; // Pointer to front queue node
    qNode* rear; // Pointer to rear queue node
    int size; // Number of vals in queue

public:
    Queue() // Constructor
    { front = rear = new qNode(); size = 0; }

    ~Queue() { delete front; } // Destructor

    void enqueue(const int& it) { // Put val on rear
        rear->next = new qNode(it, nullptr);
        rear = rear->next;
        size++;
    }

    int dequeue() { // Remove val from front
        if(size <= 0) return -1;
        int it = front->next->val; // Store dequeued value
        qNode* temp = front->next; // Hold dequeued qNode
        front->next = temp->next; // Advance front
        if (rear == temp) rear = front; // Dequeue last val
        delete temp; // Delete qNode
        size --;
        return it; // Return val value
    }

    const int& frontValue() const { // Get front val
        return front->next->val;
    }

    int length() const { return size; }
    
    void print(){
        if(!size){
            cout << "\n[ ]\n"; return;
        }
        qNode* temp = front;
        cout << "\n[";
        while(temp->next){
            temp = temp->next;
            cout << " " << temp->val;
        }
        cout << " ]\n";
    }
};

int main(){
    Queue myQueue;
    myQueue.enqueue(1);
    myQueue.enqueue(3);
    myQueue.enqueue(6);
    myQueue.enqueue(8);
    myQueue.print();
    for(int i = 0; i < 4; i++){
        myQueue.dequeue();
        myQueue.print();
    }
    
    return 0;
}