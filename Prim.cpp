#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_VERTICES = 7;

int lengthOfArray(const char []);


class Node {
    friend class Graph;
    friend class List;
private:
    char vertex;
    int cost;
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
    void append(char, int);
    void display();
    int findMinCost(bool []);
    char findNodebyCost(int, bool[]);
    char getHeadVertex();
};

void List::append(char vertex, int cost) {
    Node* temp = new Node;
    temp->vertex = vertex;
    temp->cost = cost;
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
        cout << ptr->cost << " ";
        ptr = ptr->link;
    }
    cout << endl;
}

char List::getHeadVertex(){
    Node* ptr = head;
    return ptr->vertex;
}

int List::findMinCost(bool selected[]){
    Node* ptr;
    ptr = head->link;
    int minimum = 10000;
    while (ptr) {
        if(minimum > ptr->cost && !selected[ptr->vertex - 'A']) { minimum = ptr->cost; }
        ptr = ptr->link;
    }
    return minimum;
}

char List::findNodebyCost(int cost, bool selected[]){
    Node* ptr;
    ptr = head->link;
    while (ptr) {
        if(ptr->cost == cost){
            selected[ptr->vertex - 'A'] = true;
            return ptr->vertex;
        }
        ptr = ptr->link;
    }
    return '1';
}


class Graph {
private:
    List graph[MAX_VERTICES];
    char T[MAX_VERTICES];
    bool selected[MAX_VERTICES];
public:
    int minCost;
    Graph(){
        init();
        ifstream in;
        in.open("mst_data.txt");

        char start_vertex; int input_cost; char end_vertex;
        for(char ch = 'A'; ch < 'A' + MAX_VERTICES; ch++){
            graph[ch - 'A'].append(ch, 0);
        }
        int i = 0;
        while(in >> start_vertex >> input_cost >> end_vertex){
            for(char ch = 'A'; ch < 'A' + MAX_VERTICES; ch++){
                if(start_vertex == ch) {
                    i = ch - 'A';
                    break;
                }
            }
            graph[i].append(end_vertex, input_cost);
        }

        // for append reverse direction in list
        ifstream in2;
        in2.open("mst_data.txt");
        i = 0;
        while(in2 >> start_vertex >> input_cost >> end_vertex){
            for(char ch = 'A'; ch < 'A' + MAX_VERTICES; ch++){
                if(end_vertex == ch) {
                    i = ch - 'A';
                    break;
                }
            }
            graph[i].append(start_vertex, input_cost);
        }
        /*
        for(int k = 0; k < MAX_VERTICES; k++){
            graph[k].display();
        }
        */
    }
    void init(){
        minCost = 0;
        for(int i = 0; i < MAX_VERTICES; i++){
            selected[i] = false;
            T[i] = 0;
        }
    }
    int prim();
};

int Graph::prim(){
    T[0] = 'A';
    selected[0] = true;
    int edgeCount = 0;
    while(lengthOfArray(T) < MAX_VERTICES){
        int len = lengthOfArray(T);
        int minimum = 10000;
        int select_idx = 0;
        for(int i = 0; i < len; i++){
            int temp_min = graph[T[i] - 'A'].findMinCost(selected);
            if(minimum > temp_min){
                minimum = temp_min;
                select_idx = i;
            }
        }
        if(minimum == 10000) break;
        // cout << minimum << endl;
        T[len] = graph[T[select_idx] - 'A'].findNodebyCost(minimum, selected);
        edgeCount++;
        if(T[select_idx] < T[len]) {
            cout << "Edge " << edgeCount << ": ";
            cout << T[select_idx] << " " << minimum << " "<< T[len];
            cout << endl;
        }
        else {
            cout << "Edge " << edgeCount << ": ";
            cout << T[len] << " " << minimum << " " << T[select_idx];
            cout << endl;
        }
        minCost += minimum;
    }
    if(lengthOfArray(T) < MAX_VERTICES) { cout << "No Spanning Tree" << endl; return -1; }
    return minCost;
}


int lengthOfArray(const char a[]){
    for(int i = 0; i < MAX_VERTICES; i++){
        if(a[i] == 0){
            return i;
        }
    }
    return MAX_VERTICES;
}

int main() {
    Graph g1;
    cout << "Prim's Algorithm Total cost: " << g1.prim() << endl;
}
