#include <iostream>

using namespace std;

const int QUEUE_SIZE = 5;
int queue[QUEUE_SIZE];
int front, rear;

void create_queue();
void enqueue(int item);
int dequeue();
bool isFull();
bool isEmpty();
void print_queue();

int main(){
    create_queue();

    dequeue();
    print_queue();
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);
    enqueue(6);
    dequeue();
    print_queue();

    return 0;
}

void create_queue(){
    front = -1; rear = -1;
}

void enqueue(int item){
    if(!isFull())
        queue[++rear] = item;
    else
        cout << "Queue is full !" << endl;
}

int dequeue(){
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
