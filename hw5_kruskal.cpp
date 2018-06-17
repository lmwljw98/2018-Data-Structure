/*
    Data Structure Homework #5 - Kruskal Algorithm

    Name: 이정우
    Student ID: 20171676

    Variables:
    Node::vertex - Node의 목적지 vertex 데이터
    Node::link - 연결 되어있는 노드
    List::head - 연결 리스트의 head
    Union_Find::root[MAX_VERTICES] - root 배열의 원소의 값은 각 정점의 root를 나타낸다. root 본인은 음수값을 갖는다. 그룹의 크기가 클수록 더 작은 수를 가진다.
    Graph::graph[MAX_VERTICES] - 그래프를 인접 리스트로 표현
    Graph::minCostidx - 최소 비용을 가진 노드가 속한 인접 리스트의 인덱스 저장

    Algorithm:
    1. Graph 인스턴스 선언 후, 그래프 데이터를 받아 인접 리스트로 초기화한다.
    알파벳 순으로 출발 vertex를 먼저 append한 후, 차례로 끝 vertex와 cost 데이터를 append한다.

    2. Kruskal 알고리즘을 시작한다.

    2-1. 연결 리스트 클래스의 selectMinimumCost() 함수와 check(int) 함수를 이용하여 최소 비용을 가졌고, 아직 선택되지 않은 노드를 선택한다.
    한번 선택된 노드는 다시 선택되지 않는다.
    selectMinimumCost() -> 각 인접 리스트를 모두 탐색하여 각 노드 중 최소 비용을 가진 노드를 찾아 최소 비용을 리턴한다.
    단, 선택되지 않은 노드여야 한다.
    check(int) -> 위에서 찾은 최소 비용을 인자로 받아 각 인접 리스트를 모두 탐색하여 선택되지 않은 노드 중 인자로 받은 비용과 같은 비용을 가진 노드를 찾아 그 노드 포인터를 리턴한다.
    Graph의 selectMinCost() 함수는 위 두 함수를 이용하여 최종적으로 선택된 노드를 리턴해준다.

    2-2. 2-1에서 선택된 노드의 시작 정점과 끝 정점을 int 형으로 바꾸어 저장한 후, Union_Find 클래스를 이용하여 Cycle 여부를 확인한다.
    findRoot(int) -> 인자로 들어온 정점의 부모를 리턴한다. 만약 인자가 부모 자신이면 음수값을 리턴한다.
    findRoot의 비교에서 둘의 부모가 다르다는 것은 두 정점이 각각 속한 간선의 집합이 연결되있지 않다는 뜻이므로 Cycle에 해당하지 않는다.
    2-2-1. 만약 Cycle이라면 다음으로 넘어간다.
    2-2-2. 만약 Cycle이 아니라면 두 정점을 결합한다.(union_ 함수) 총합 비용 저장 변수에 두 정점 사이의 비용을 더한다. 두 정점과 비용을 출력한다.
    union_(int, int) -> 인자로 들어온 두 정점의 root를 저장한다. (root1, root2)
    만약 두 root가 같다면 이미 결합된 상태이므로 그대로 함수를 종료한다.
    그렇지 않다면, root1과 root2의 크기를 비교하여 root1이 더 큰 크기의 집합이 되도록 swap한 후, root1에 root2를 결합한다. root2의 부모는 root1으로 변경한다.
    2-3. 선택된 간선의 개수가 그래프가 가지는 최대 (vertex 값 - 1)이 될 때까지 위 사항을 반복한다.

    3. 최종 비용을 출력한다.


    File Name: hw5_kruskal.cpp
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_VERTICES = 6; // 그래프가 가지는 최대 vertex


// 연결 리스트 Node 클래스
class Node {
    friend class Graph;
    friend class List;
private:
    char vertex; // Node의 목적지 vertex 데이터
    int cost; // Node의 비용
    bool select; // Node가 최소 비용으로 선택된 적이 있는지 여부 확인 변수
    Node* link; // 연결되어 있는 노드
};


// 연결 리스트 클래스
class List {
    friend class Graph;
private:
    Node* head;
public:
    List () {
        head = 0;
    }
    void append(char, int); // 연결 리스트의 끝에 노드 추가
    void display(); // for debug
    int selectMinimumCost(); // 연결 리스트에서 아직 선택된 적이 없는 가장 작은 비용을 리턴
    Node* check(int); // selectMinimumCost()가 리턴한 비용을 가진 아직 선택된 적이 없는 노드 포인터를 리턴
    char getHeadVertex(); // 해당 리스트의 head노드의 vertex를 리턴
};

// 해당 리스트의 head노드의 vertex를 리턴
char List::getHeadVertex(){
    return head->vertex;
}

// 연결 리스트의 끝에 노드 추가
void List::append(char vertex, int cost) {
    Node* temp = new Node;
    temp->vertex = vertex;
    temp->cost = cost;
    temp->link = 0;
    temp->select = false; // 초기값 false
    if (head == 0)
        head = temp;
    else {
        Node* ptr = head;
        while (ptr->link != 0)
            ptr = ptr->link;
        ptr->link = temp;
    }
}

// for debug
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

// 연결 리스트에서 아직 선택된 적이 없는 가장 작은 비용을 리턴
int List::selectMinimumCost(){
    Node* ptr = head->link;
    int minimum = 9999;
    while(ptr) {
        if(minimum > ptr->cost && !ptr->select){ // 아직 선택되지 않았고 값이 더 작다면
            minimum = ptr->cost;
        }
        ptr = ptr->link;
    }
    return minimum;
}

// selectMinimumCost()가 리턴한 비용을 가진 아직 선택된 적이 없는 노드 포인터를 리턴
Node* List::check(int minimum){
    Node* ptr = head->link;
    while(ptr) {
        if(ptr->cost == minimum && !ptr->select){ // minimum과 해당 포인터의 cost가 같고 선택된 적이 없다면
            ptr->select = true; // select를 true로 하고 포인터 리턴
            return ptr;
        }
        ptr = ptr->link;
    }
    return NULL;
}


// Union-Find 자료구조 클래스
// 각 정점의 root를 찾아 cycle 여부를 확인한 뒤 각 정점이 연결된 그룹을 합친다.
class Union_Find{
private:
    int root[MAX_VERTICES]; // root 배열의 원소의 값은 각 정점의 root를 나타낸다.
                            // root 본인은 음수값을 갖는다. 그룹의 크기가 클수록 더 작은 수를 가짐
public:
    Union_Find(){ // 생성자
        for(int i = 0; i < MAX_VERTICES; i++){
            root[i] = -1; // -1로 초기화한다.
        }
    }

    // 정점의 root 노드를 리턴
    int findRoot(int vertex){
        if(root[vertex] < 0) { return vertex; } // 음수라면 root이므로 해당 정점 리턴
        root[vertex] = findRoot(root[vertex]);
        return root[vertex];
    }

    // 정점과 정점을 결합
    void union_(int a, int b){
        int root1 = findRoot(a); // 각 정점의 root를 저장
        int root2 = findRoot(b);

        if(root1 == root2){ // 두 root가 같다면 이미 결합된 상태이므로 리턴
            return;
        }

        // 크기가 큰 그룹에 작은 그룹을 합칠 것이기 때문에, 만약 root1의 그룹이 크기가 더 작다면, swap
        if(root[root1] > root[root2]){
            int temp = root[root1];
            root[root1] = root[root2];
            root[root2] = temp;
        }
        root[root1] += root[root2]; // root1에 root2를 결합
        root[root2] = root1; // root2의 부모는 root1으로 변경
    }
};


// Graph 클래스
class Graph {
private:
    List graph[MAX_VERTICES]; // 인접 리스트
    int minCostidx; // 최소 비용을 가진 노드가 속한 인접 리스트의 인덱스 저장
public:
    // 그래프 데이터 초기화
    Graph(){
        ifstream in;
        in.open("mst_data.txt");

        char start_vertex; int input_cost; char end_vertex;
        for(char ch = 'A'; ch < 'A' + MAX_VERTICES; ch++){
            graph[ch - 'A'].append(ch, 0); // 데이터가 나타내는 시작 정점을 초기화
        }
        int i = 0;
        while(in >> start_vertex >> input_cost >> end_vertex){
            for(char ch = 'A'; ch < 'A' + MAX_VERTICES; ch++){
                if(start_vertex == ch) {
                    i = ch - 'A'; // 시작 정점의 인덱스
                    break;
                }
            }
            graph[i].append(end_vertex, input_cost);
        }
        /* for debug
        for(int i = 0; i < MAX_VERTICES; i++){
            graph[i].display();
        }
        */
    }
    Node* selectMinCost(); // 인접 리스트에서 아직 선택된 적이 없는 최소 비용을 가진 노드 포인터 리턴
    int kruskal(); // Kruskal 알고리즘
};

// 인접 리스트에서 아직 선택된 적이 없는 최소 비용을 가진 노드 포인터 리턴
Node* Graph::selectMinCost(){
    int minimum = 9999;
    for(int i = 0; i < MAX_VERTICES; i++){
        int temp = graph[i].selectMinimumCost(); // 아직 선택되지 않은 최소 비용 선택
        if(minimum > temp){
            minimum = temp;
        }
    }

    for(int i = 0; i < MAX_VERTICES; i++){
        Node* node = graph[i].check(minimum); // selectMinimumCost()가 리턴한 비용을 가진 아직 선택된 적이 없는 노드 포인터 저장
        if(node != NULL){
            minCostidx = i; // 최소 비용을 가진 노드가 속한 인접 리스트의 인덱스 저장
            return node; // 노드 포인터 리턴
        }
    }
    return NULL;
}

int Graph::kruskal(){
    Union_Find S; // Union_Find 인스턴스 생성
    int total_cost = 0; // 총합 비용
    int count = 0; // 선택된 간선의 개수
    while(count < MAX_VERTICES-1){
        Node* minimum = selectMinCost(); // 최소 비용을 가진 노드 선택
        int from = graph[minCostidx].getHeadVertex() - 'A'; // 시작 정점
        int to = minimum->vertex - 'A'; // 끝 정점

        // 둘의 부모가 다르다는 것은 두 정점이 속한 집합은 연결되있지 않다는 뜻 == No Cycle
        if(S.findRoot(from) != S.findRoot(to)){
            S.union_(from, to); // 두 정점 결합
            total_cost += minimum->cost; // 비용 추가
            cout << "Edge " << count+1 << ": ";
            cout << char(from +'A') << " " << minimum->cost << " " << char(to +'A') << endl; // 출력
            count++;
        }
    }
    return total_cost;
}


int main(){
    Graph g1;
    cout << "Total Cost: " << g1.kruskal() << endl;
}
