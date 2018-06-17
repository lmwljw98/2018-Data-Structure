/*
    Data Structure Homework #4 - Breadth First Search

    Name: 이정우
    Student ID: 20171676

    Variables:
    Node::vertex - 노드의 데이터값
    Node::link - 연결 되어있는 노드
    List::head - 연결 리스트의 head
    Queue::queue[MAX_VERTICES]; - queue로 사용할 배열
    Queue::front - queue의 front
    Queue::rear - queue의 rear
    Graph::graph[MAX_VERTICES] - 그래프를 연결 리스트로 표현
    Graph::q - queue
    Graph::visited[MAX_VERTICES] - 방문 여부 기록을 위한 배열

    Algorithm:
    1. Graph 인스턴스 선언 후, 인접 행렬을 출력한다. Graph 생성자에서는 파일에서 graph 데이터를 입력받은 후 인접 행렬을 생성한다. 그 후 방문 여부를 모두 false로 초기화한다.
    visited 배열은 각 vertex를 위치로 하여 방문했을 경우 true, 아닐 경우 false를 기록한다.

    2. BFS 탐색 경로를 출력한다.
    2-1. 각 노드를 가리킬 임시 Node를 선언한다.
    가장 처음 방문할 vertex를 정한 후, visited에 그 위치에 있는 원소를 true로 한다.
    Queue에 enqueue한 후 해당 vertex를 출력한다.

    2-2. 이제 Queue가 empty가 될 때까지 아래 작업을 반복한다.
    - Queue에서 dequeue하여 리턴된 값을 방문할 연결 리스트의 vertex로 한다.
    - vertex가 가리키는 연결 리스트를 끝까지 탐색한다
    - - 만약 리스트에서 포인터가 가리키는 노드가 방문하지 않았던 노드라면
    - - Queue에 노드의 데이터를 enqueue하고, visited에 true로 기록, 그 후 출력한다.

    3. 2번이 모두 끝나면 BFS 탐색 경로가 출력되어 있는 상태이다.


    File Name: hw3_BFS.cpp
 */

#include <iostream>
#include <fstream>
#include <string>
#define MAX_VERTICES 8 // 최대 vertex

using namespace std;

int matrix[MAX_VERTICES][MAX_VERTICES] = {0}; // 인접 행렬

// 연결 리스트 노드 class
class Node {
    friend class Graph; // Graph class에서 노드 데이터 참조 가능
    friend class List; // List class 에서 노드 데이터 참조 가능
private:
    int vertex; // 노드의 data
    Node* link; // 연결 되어있는 노드
};

// 연결 리스트 class
class List {
    friend class Graph; // Graph class에서 참조 가능
private:
    Node* head; // 연결 리스트의 head
public:
    List () {
        head = 0; // 생성시 head 초기화
    }
    void append(int); // 연결 리스트의 끝에 노드 추가
    void adj_matrix_setting(int); // 그래프의 인접행렬 구현
};

void List::append(int vertex) { // 연결 리스트의 끝에 노드 추가
    Node* temp = new Node; // 임시 노드 선언
    temp->vertex = vertex;
    temp->link = 0;
    if (head == 0) // 처음 추가할 경우
        head = temp;
    else { // 이미 데이터가 한 개 이상 존재할 경우
        Node* ptr = head;
        while (ptr->link != 0)
            ptr = ptr->link; // 포인터를 끝까지 이동
        ptr->link = temp; // 새로운 노드 연결
    }
}

void List::adj_matrix_setting(int row) { // 그래프의 인접 행렬 구현
    Node* ptr = head->link; // 연결 리스트의 head 다음 노드부터 시작
    while (ptr) { // 리스트의 끝까지
        matrix[row][ptr->vertex] = 1; // 노드의 데이터가 가리키는 열에 표시
        ptr = ptr->link; // 다음 노드로 이동
    }
}

// Queue class
class Queue {
private:
    int queue[MAX_VERTICES]; // queue로 사용할 배열 선언
    int front; // queue의 front
    int rear; // queue의 rear
public:
    Queue(){ // queue 초기화
        front = -1;
        rear = -1;
    }
    void enqueue(int); // enqueue
    int dequeue(); // dequeue
    bool isFull(); // queue가 full인지 아닌지 체크
    bool isEmpty(); // queue가 empty인지 아닌지 체크
};

void Queue::enqueue(int item){ // enqueue
    if(!isFull()) // full이 아닌 경우
        queue[++rear] = item; // rear를 1 증가 시킨 후 그 위치에 item 등록
    else
        cout << "Queue is full !" << endl;
}

int Queue::dequeue(){ // dequeue
    if(!isEmpty()) // empty가 아닌 경우
        return queue[++front]; // front를 1 증가 시킨 후 그 자리에 있는 원소 리턴
    cout << "Queue is empty !" << endl;
}

bool Queue::isFull(){ // queue가 full인지 아닌지 체크
    if(rear == MAX_VERTICES - 1)
        return true;
    return false;
}

bool Queue::isEmpty(){ // queue가 empty인지 아닌지 체크
    if(rear == front)
        return true;
    return false;
}

// Graph 클래스
class Graph {
private:
    List graph[MAX_VERTICES]; // 그래프를 연결 리스트로 표현
    Queue q; // queue 선언
    bool visited[MAX_VERTICES]; // 방문 여부 기록을 위한 배열
public:
    Graph(){ // 생성자
        ifstream in;
        /* 파일에서 그래프 데이터를 읽어옴.
        각 행의 첫번째 수는 vertex */
        in.open("graph.txt");
        string line; int i = 0;
        while(getline(in, line)){ // 한 행씩 읽음
            for(int j = 0; j < line.length(); j += 2){
                graph[i].append(line[j] - '0'); // 각 수를 연결 리스트에 추가
            }
            graph[i].adj_matrix_setting(i); // 인접 행렬을 구현
            i++;
        }
        init(); // 방문 여부 기록 배열을 초기화
    }
    void BFS(int); // BFS 탐색
    void init(){ // 방문 여부 기록 배열을 초기화
        for(int i = 0; i < MAX_VERTICES; i++)
            visited[i] = false;
    }
};

void Graph::BFS(int v=0){
    Node* p; // 노드 포인터 선언
    visited[v] = true; // 가장 처음 방문한 노드의 위치에 true
    q.enqueue(v); // 방문한 노드는 enqueue
    cout << "v" << v << " "; // 출력
    while(!q.isEmpty()){ // queue가 not empty인 동안
        v = q.dequeue(); // queue의 가장 앞의 원소 dequeue하여 현재 방문중인 vertex 저장
        for(p = graph[v].head; p != NULL; p = p->link){ // 현재 vertex의 연결 리스트를 끝까지 탐색
            if(!visited[p->vertex]){ // 만약 현재 노드가 방문하지 않았던 곳이면
                q.enqueue(p->vertex); // enqueue
                visited[p->vertex] = true; // 방문 여부에 true
                cout << "v" << p->vertex << " "; // 출력
            }
        }
    }
}


int main() {
    Graph g1; // 그래프 인스턴스 선언
    // 인접 행렬 출력
    cout << "***** Adjacent Matrix" << endl;
    cout << "   ";
    for(int i = 0; i < MAX_VERTICES; i++){
        cout << "v" << i << "  ";
    }
    cout << endl;
    for(int i = 0; i < MAX_VERTICES; i++){
        for(int j = -1; j < MAX_VERTICES; j++){
            if(j == -1) { cout << "v" << i << "  "; continue; }
            cout << matrix[i][j] << "   ";
        }
        cout << endl;
    }
    // BFS 탐색 경로 출력
    cout << endl << "***** Breadth First Search (BFS)" << endl;
    g1.BFS();
    cout << endl;
}
