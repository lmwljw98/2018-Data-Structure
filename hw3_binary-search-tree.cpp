/*
    Data Structure Homework #3 - Binary Search Tree

    Name: 이정우
    Student ID: 20171676

    Variables:
    TreeNode::data - 노드의 데이터값
    TreeNode::left, TreeNode::right - 노드의 왼쪽, 오른쪽을 가리키는 포인터
    Tree::root - 트리의 root 노드

    Algorithm:
    1. TreeNode 클래스에 Node를 구현하고, Tree 클래스에 BST에 대한 메소드를 구현한다.

    2. Main에서 입력을 받는다.
    2-1. 1번 입력이 들어온 경우 insertNode를 이용하여 새로운 노드를 추가한다.
    만약 처음으로 insert된다면, 기본적으로 설정되어있는 root의 data를 -1에서 인자값으로 바꿔준다.
    그렇지 않을 경우, 인자로 들어온 root부터 시작하여 재귀함수를 통한 탐색을 시작한다.
    BST의 정의에 따라 추가하고자 하는 값이 현재 방문중인 Node의 값보다 작다면 왼쪽으로 방문하고, 더 크다면 오른쪽으로 방문한다.
    BST는 같은 값이 없는 자료구조이므로 같은 값이 들어오는 상황은 고려하지 않았다.
    계속해서 탐색하다가 현재 포인터가 비어있는 경우 새로운 Node를 생성한다.

    2-2. 2번 입력이 들어온 경우 deleteNode를 이용하여 인자로 들어온 key와 같은 data를 가진 Node를 삭제한다.
    이 경우도 root부터 시작하여 재귀함수를 통하여 key와 같은 data를 가진 노드를 탐색한다.
    탐색하여 조건에 맞는 Node를 발견하면, 그 Node를 삭제하는데, 경우가 3가지로 나뉜다.

    2-2-1. 만약 조건에 맞는 Node가 양쪽 child가 모두 없는 Leaf Node라면, 바로 현재 Node를 삭제한다.
    2-2-2. 만약 조건에 맞는 Node가 한쪽 child만 존재하는 경우, 현재 노드를 임시로 저장한 후, 현재 포인터를 child가 존재하는 방향으로 옮긴다.
    그 후, 임시로 저장한 노드를 삭제한다.
    2-2-3. 만약 조건에 맞는 Node가 양쪽 child 모두 가지고 있다면, find_min 함수를 이용하여 현재 Node의 subtree에서 가장 작은 값을 찾아 temp에 저장한다.
    ※ find_min 함수는 가장 처음에 오른쪽 child를 인자로 받아 재귀적으로 왼쪽 child를 계속 탐색한다.(항상 더 작은 값이기 때문)
    삭제하려는 Node의 data를 temp의 data로 바꾼다.
    그 후 가장 작은 값을 가지고 있던 Node를 재귀적으로 탐색하여 삭제한다. (가장 마지막 level에 있으므로 2-2-1 조건에 따라 삭제될 것이다.)

    2-3. 3번 입력이 들어온 경우 searchNode를 이용하여 사용자가 입력한 값을 탐색한다.
    이 메소드 또한 재귀적으로 탐색한다. 만약 찾고자 하는 Node의 data가 현재 포인터의 data보다 작다면 왼쪽으로, 더 크다면 오른쪽으로 탐색한다.
    만약 발견한다면 "OO is found."를 출력하고, 발견하지 못했다면, "Not Found"를 출력한다.

    2-4. 4번 입력이 들어온 경우 drawBSTree를 이용하여 트리를 출력한다.
    가장 오른쪽 노드부터 시작하여 단계적으로 출력한다.

    2-5. 5번 입력이 들어온 경우 프로그램을 종료한다.

    File Name: hw3_binary-search-tree.cpp
 */

#include <iostream>

using namespace std;

// Tree의 노드 class
class TreeNode {
    friend class Tree; // Tree에서 Node의 데이터 참조 가능
private:
    int data; // 노드의 데이터
    TreeNode* left; // 노드의 왼쪽 노드
    TreeNode* right; // 노드의 오른쪽 노드
public:
    TreeNode(int data, TreeNode* left = NULL, TreeNode* right = NULL) { // 생성자, default값으로 왼쪽 노드와 오른쪽 노드는 비어있음.
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

// Tree class
class Tree {
private:
    TreeNode* root; // root 노드가 기본적으로 존재
public:
    Tree(){ // // root 노드가 기본적으로 존재
        root = new TreeNode(-1); // Tree를 생성할 때 아무런 인자도 없다면, 비어있다는 의미로 root 노드의 data에 -1을 부여한다.
    }
    Tree(int data){
        root = new TreeNode(data); // 인자가 있다면 인자로 들어온 수를 root 노드의 data로 한다.
    }

    TreeNode* getRoot(){ // root의 getter 메소드
        return root;
    }
    TreeNode* searchNode(TreeNode* ptr, int key); // Node 검색 메소드
    TreeNode* insertNode(TreeNode* ptr, int key); // Node 삽입 메소드
    TreeNode* deleteNode(TreeNode* ptr, int key); // Node 삭제 메소드
    TreeNode* find_min(TreeNode* ptr); // deleteNode에서 이용되는 메소드. 시작포인터의 Subtree에서 최솟값을 리턴한다.
    void drawBSTree(TreeNode* p, int level); // Tree를 보여주는 메소드
};

TreeNode* Tree::searchNode(TreeNode* ptr, int key){ // Node 검색 메소드
    if (ptr == NULL){
        cout << "Not Found" << endl;
        return NULL; // key를 찾지 못했을 경우
    }
    else {
        if (key == ptr->data){
            cout << key << " is found." << endl;
            return ptr; // key를 찾았을 경우
        }
        else if (key < ptr->data)
            ptr = searchNode(ptr->left, key); // key가 현재 포인터의 data보다 작을 경우 왼쪽 subtree로 이동한다.
        else if (key > ptr->data)
            ptr = searchNode(ptr->right, key); // key가 현재 포인터의 data보다 클 경우 오른쪽 subtree로 이동한다.
    }
    return ptr;
 }

TreeNode* Tree::insertNode(TreeNode* ptr, int key){ // Node 삽입 메소드
    if (ptr == NULL) {
        ptr = new TreeNode(key); // 비어있는 부분에 key를 data로 가지는 새로운 Node 생성
    }
    else if(ptr->data == -1){
        ptr->data = key; // root가 초기 상태일 경우 root의 data를 key로 수정한다.
    }
    else if (key < ptr->data){
        ptr->left = insertNode(ptr->left, key); // key가 현재 방문중인 포인터의 data보다 작을 경우 왼쪽 subtree로 이동한다.
    }
    else if (key > ptr->data){
        ptr->right = insertNode(ptr->right, key); // key가 현재 방문중인 포인터의 data보다 클 경우 오른쪽 subtree로 이동한다.
    }
    return ptr;
}

TreeNode* Tree::deleteNode(TreeNode* ptr, int key) { // Node 삭제 메소드
    if (ptr != NULL) {
        if (key < ptr->data) // key가 현재 포인터의 data보다 작을 경우
            ptr->left = deleteNode(ptr->left, key); // 왼쪽으로 이동
        else if (key > ptr->data) // key가 현재 포인터의 data보다 클 경우
            ptr->right = deleteNode(ptr->right, key); // 오른쪽으로 이동
        else if ((ptr->left == NULL) && (ptr->right == NULL))
            ptr = NULL; // leaf node일 경우 바로 삭제
        else if (ptr->left == NULL) { // right child만 존재할 경우
            TreeNode* p = ptr;
            ptr = ptr->right;
            p = NULL; // 현재 포인터를 오른쪽 노드로 옮긴 후, 삭제한다.
        }
        else if (ptr->right == NULL) { // left child만 존재할 경우
            TreeNode* p = ptr;
            ptr = ptr->left;
            p = NULL; // 현재 포인터를 왼쪽 노드로 옮긴 후, 삭제한다.
        }
        else { // 삭제하려는 노드의 양쪽 모두 존재할 경우
            TreeNode* temp = find_min(ptr->right); // 해당 노드의 subtree에섯 최솟값을 찾아 temp에 저장
            ptr->data = temp->data; // 현재 포인터와 temp의 data를 swap한다.
            ptr->right = deleteNode(ptr->right, ptr->data); // 원래 최솟값이 있던 위치로 찾아가 삭제한다.
        }
    }
    else{ // 삭제할 key를 찾지 못한 경우
        cout << "Not Found" << endl;
    }
    return ptr;
}

TreeNode* Tree::find_min(TreeNode* ptr){ // subtree 에서 가장 작은것 선택
     if (ptr->left == NULL) return ptr;
     else find_min(ptr->left);
}

void Tree::drawBSTree(TreeNode* p, int level=1) { // Tree를 보여주는 메소드
    if (p != 0 && level <= 7) {
        drawBSTree(p->right, level+1); // 가장 오른쪽 노드로 이동
        for (int i = 1; i <= (level-1); i++) // (level - 1)만큼 공백 추가
            cout << "    ";
        cout << p->data; // 데이터 출력
        if (p->left != 0 && p->right != 0) cout << " <" << endl; // 현재 노드에 왼쪽, 오른쪽 child가 존재하는 경우
        else if (p->right != 0) cout << " /" << endl; // 현재 노드에 오른쪽 노드만 존재하는 경우
        else if (p->left != 0) cout << " \\" << endl; // 현재 노드에 왼쪽 노드만 존재하는 경우
        else cout << endl; // 아무런 child가 존재하지 않는다면 다음줄로 넘어간다.
        drawBSTree(p->left, level+1); // 현재 노드에서 왼쪽 노드로 이동
    }
}

int main(){
    int num; int input;
    Tree t1;
    while(1){
        cout << "Select Command - 1.insert | 2.delete | 3.search | 4.print | 5.quit : ";
        cin >> num;
        switch(num){
            case 1:
                cout << "Enter number : ";
                cin >> input;
                t1.insertNode(t1.getRoot(), input);
                break;
            case 2:
                cout << "Enter number : ";
                cin >> input;
                t1.deleteNode(t1.getRoot(), input);
                break;
            case 3:
                cout << "Enter number : ";
                cin >> input;
                t1.searchNode(t1.getRoot(), input);
                break;
            case 4:
                cout << endl;
                t1.drawBSTree(t1.getRoot());
                cout << endl;
                break;
            case 5:
                return 0;
            default:
                break;
        }
    }
}
