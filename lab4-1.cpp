#include <iostream>

using namespace std;

// Stack
const int Stack_Size = 2;

class Stack {
    private:
        char stack[Stack_Size]; int top;
    public:
        Stack() {
                top = -1;
        }
        void push(int val) {
            if(!isFull())
                stack[++top] = val;
            else
                cout << "Stack is full" << endl;
        }
        char pop() {
            if(!isEmpty())
                return stack[top--];
            else
                cout << "Stack is empty" << endl;
        }
        bool isEmpty() {
                return top == -1;
        }
        bool isFull() {
                return top == Stack_Size - 1;
        }
        void displayStack();
        };

void Stack::displayStack()
{
        int sp; sp = top;
        while (sp != -1) { cout << stack[sp--] << endl; }
        cout << endl;
};

// Queue
const int QUEUE_SIZE = 3;
char queue[QUEUE_SIZE];
int front, rear;

void create_queue();
void enqueue(char item);
char dequeue();
bool isFull();
bool isEmpty();
void print_queue();

int main(){
    Stack s1;
    create_queue();

    s1.push('a');
    enqueue('b');
    enqueue('c');
    enqueue('d');
    s1.push('e');

    s1.push('a');
    enqueue('a');

    s1.displayStack();
    print_queue();

    cout << s1.pop();
    cout << dequeue();
    cout << dequeue();
    cout << dequeue();
    cout << s1.pop() << endl;

    s1.pop();
    dequeue();

    return 0;
}

void create_queue(){
    front = -1; rear = -1;
}

void enqueue(char item){
    if(!isFull())
        queue[++rear] = item;
    else
        cout << "Queue is full !" << endl;
}

char dequeue(){
    if(!isEmpty())
        return queue[++front];
    cout << "Queue is empty !" << endl;
}

bool isFull(){
    if(rear == QUEUE_SIZE - 1)
        return true;
    return false;
}

bool isEmpty(){
    if(rear == front)
        return true;
    return false;
}

void print_queue(){
    if(!isEmpty()){
        for (int i = front + 1; i <= rear; i++){
            cout << queue[i] << " ";
        }
        cout << endl;
    }
    else{
        cout << "Queue is empty !" << endl;
    }
}
