#include <iostream>
#include <fstream>
#include <string>
#define MAX_VERTICES 8

using namespace std;

class Node {
    friend class Graph;
    friend class List;
private:
    int vertex;
    Node* link;
};


class List {
    friend class Graph;
private:
    Node* head;
public:
    List () {
        head = 0;
    }
    void append(int);
    void display();
};

void List::append(int vertex) {
    Node* temp = new Node;
    temp->vertex = vertex;
    temp->link = 0;
    if (head == 0)
        head = temp;
    else {
        Node* ptr = head;
        while (ptr->link != 0)
            ptr = ptr->link;
        ptr->link = temp;
    }
}

void List::display() {
    Node* ptr;
    ptr = head;
    while (ptr) {
        cout << ptr->vertex << " ";
        ptr = ptr->link;
    }
    cout << endl;
}


class Queue {
private:
    int queue[MAX_VERTICES];
    int front;
    int rear;
public:
    Queue(){
        front = -1;
        rear = -1;
    }
    void enqueue(int);
    int dequeue();
    bool isFull();
    bool isEmpty();
};

void Queue::enqueue(int item){
    if(!isFull())
        queue[++rear] = item;
    else
        cout << "Queue is full !" << endl;
}

int Queue::dequeue(){
    if(!isEmpty())
        return queue[++front];
    cout << "Queue is empty !" << endl;
}

bool Queue::isFull(){
    if(rear == MAX_VERTICES - 1)
        return true;
    return false;
}

bool Queue::isEmpty(){
    if(rear == front)
        return true;
    return false;
}


class Graph {
private:
    List graph[MAX_VERTICES];
    Queue q;
    bool visited[MAX_VERTICES];
public:
    Graph(){
        ifstream in;
        in.open("graph.txt");
        string line; int i = 0;
        while(getline(in, line)){
            for(int j = 0; j < line.length(); j += 2){
                graph[i].append(line[j] - '0');
            }
            i++;
        }
        init();
    }
    void DFS(int);
    void BFS(int);
    void init(){
        for(int i = 0; i < MAX_VERTICES; i++)
            visited[i] = false;
    }
};

void Graph::DFS(int v=0){
    Node* w;
    visited[v] = true;
    cout << v << " ";
    for(w = graph[v].head; w != NULL; w = w->link){
        if(!visited[w->vertex])
            DFS(w->vertex);
    }
}

void Graph::BFS(int v=0){
    Node* p;
    visited[v] = true;
    q.enqueue(v);
    cout << v << " ";
    while(!q.isEmpty()){
        v = q.dequeue();
        for(p = graph[v].head; p != NULL; p = p->link){
            if(!visited[p->vertex]){
                q.enqueue(p->vertex);
                visited[p->vertex] = true;
                cout << p->vertex << " ";
            }
        }
    }
}


int main() {
    Graph g1;
    g1.DFS();
    g1.init(); cout << endl;
    g1.BFS();
}
