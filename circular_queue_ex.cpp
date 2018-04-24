#include <iostream>

using namespace std;

const int QUEUE_SIZE = 4;
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

    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);
    dequeue();
    dequeue();
    print_queue();
    enqueue(6);
    enqueue(7);
    print_queue();

    return 0;
}

void create_queue(){
    front = 0; rear = 0;
}

void enqueue(int item){
    if (isFull()){
        cout << "Queue is full" << endl;
    }
    else{
        rear = (rear+1) % QUEUE_SIZE;
        queue[rear] = item;
    }
}

int dequeue(){
    if (isEmpty()){
        cout << "Queue is empty" << endl;
        return -1;
    }
    else {
        front = (front+1) % QUEUE_SIZE;
        return queue[front];
    }
}

bool isFull(){
    if(front == (rear + 1) % QUEUE_SIZE)
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
        for(int index = front + 1; index != (rear+1) % QUEUE_SIZE; index = (index+1) % QUEUE_SIZE){
            cout << queue[index] << " ";
        }
        cout << endl;
    }
    else{
        cout << "Queue is empty !" << endl;
    }
}
