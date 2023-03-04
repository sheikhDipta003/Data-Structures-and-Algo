#include <iostream>
using namespace std;
 
// Define the default capacity of the stack
#define SIZE 10
 
// A class to represent a stack
class Stack
{
    int *arr;
    int top;
    int capacity;
 
public:
    Stack(int size = SIZE);         // constructor
    ~Stack();                       // destructor
 
    void push(int);
    int pop();
    int peek();
 
    int size();
    bool isEmpty();
    bool isFull();
};
 
// Constructor to initialize the stack
Stack::Stack(int size)
{
    arr = new int[size];
    capacity = size;
    top = -1;
}
 
// Destructor to free memory allocated to the stack
Stack::~Stack() {
    delete[] arr;
}
 
// Utility function to add an element `x` to the stack
void Stack::push(int x)
{
    if (isFull())
    {
        cout << "Overflow\nProgram Terminated\n";
        return size();
    }
    arr[++top] = x;
}
 
// Utility function to pop a top element from the stack
int Stack::pop()
{
    // check for stack underflow
    if (isEmpty())
    {
        cout << "Underflow\nProgram Terminated\n";
        return size();
    } 
    return arr[top--];
}
 
// Utility function to return the top element of the stack
int Stack::peek()
{
    if (!isEmpty()) {
        return arr[top];
    }
    else {
        cout << "Stack empty\n";
        return size();
    }
}
 
// Utility function to return the size of the stack
int Stack::size() {
    return top + 1;
}
 
// Utility function to check if the stack is empty or not
bool Stack::isEmpty() {
    return !size();
}
 
// Utility function to check if the stack is full or not
bool Stack::isFull() {
    return size() == capacity;
}
 
int main()
{
    Stack pt(3);
 
    pt.push(1);
    pt.push(2);
 
    pt.pop();
    pt.pop();
 
    pt.push(3);
 
    cout << "The top element is " << pt.peek() << endl;
    cout << "The stack size is " << pt.size() << endl;
 
    pt.pop();
 
    if (pt.isEmpty()) {
        cout << "The stack is empty\n";
    }
    else {
        cout << "The stack is not empty\n";
    }
 
    return 0;
}