#include <iostream>

using namespace std;

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
    create_queue();

    enqueue('a');
    enqueue('b');
    enqueue('c');
    dequeue();
    enqueue('a');

    print_queue();

    dequeue();
    dequeue();
    dequeue();

    return 0;
}

void create_queue(){
    front = -1; rear = -1;
}

void enqueue(char item){
    if (isFull()){
        cout << "Queue is full" << endl;
    }
    else{
        rear = (rear+1) % QUEUE_SIZE;
        queue[rear] = item;
    }
}

char dequeue(){
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
        for(int index = front + 1; index < QUEUE_SIZE; index++){
            cout << queue[index] << " ";
        }
        cout << endl;
    }
    else{
        cout << "Queue is empty !" << endl;
    }
}
