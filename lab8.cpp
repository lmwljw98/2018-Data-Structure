#include <iostream>
#include <fstream>
#include <string>
#define MAX_VERTICES 6

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
    cout << "V";
    while (ptr) {
        if(ptr == head){
            cout << ptr->vertex;
            cout << ": ";
        }
        else if(ptr->link != NULL){
            cout << ptr->vertex << "->";
        }
        else{
            cout << ptr->vertex;
        }
        ptr = ptr->link;
    }
    cout << endl;
}


class Graph {
private:
    List graph[MAX_VERTICES];
    bool visited[MAX_VERTICES];
public:
    Graph(string filename){
        cout << "Graph Data" << endl;
        ifstream in;
        in.open(filename);
        string line; int i = 0;
        while(getline(in, line)){
            for(int j = 0; j < line.length(); j += 2){
                graph[i].append(line[j] - '0');
            }
            graph[i].display();
            i++;
        }
        init();
    }
    void DFS(int);
    void init(){
        for(int i = 0; i < MAX_VERTICES; i++)
            visited[i] = false;
    }
};

void Graph::DFS(int v=0){
    Node* w;
    visited[v] = true;
    cout << "V" << v << " ";
    for(w = graph[v].head; w != NULL; w = w->link){
        if(!visited[w->vertex])
            DFS(w->vertex);
    }
}


int main() {
    Graph g1("lab8.txt");
    cout << endl << "DFS OUTPUT : ";
    g1.DFS(); cout << endl;
}
