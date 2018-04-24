/*
    Data Structure Homework #2 - Single Linked List

    Name: 이정우
    Student ID: 20171676

    Used Algorithm:
    1. data1.txt에서 값을 읽어와 하나의 연결 리스트로 작성한다. List 클래스의 append 함수를 사용한다.
    (append 함수)
    처음 추가할 경우 - head는 인자 그대로 만들어진다.
    그 이후로는 - 임시 포인터를 선언해 마지막 노드까지 이동 후, 마지막 노드의 next에 새로운 노드를 추가해준다.
    2. 만들어진 연결 리스트를 오름차순으로 정렬한다. 버블 정렬을 이용하여 정렬한다.
    버블 정렬이란 연속한 2개의 원소의 값을 비교해 기준에 따라 비교하여 2개의 값을 swap하여 정렬하는 것을 의미한다.
    해당 프로그램에서는 각 원소의 이름을 오름차순으로 정렬하기로 하여 이름의 알파벳을 기준으로 비교하였다. 비교하여 노드의 각 데이터를 swap 해준다.
    3. 성적 "A"를 받은 사람만 출력하기 위하여 포인터가 가리키는 값이 0이 될 때까지(끝까지) 반복하여 모든 값을 출력하는 display 함수에서 조건문을 추가하여 조건에 맞는 원소만 출력한다.
    4. data2.txt를 읽어 새로운 연결 리스트를 작성하고, 기존 리스트의 마지막 노드와 새로운 리스트의 head 노드를 연결하여 병합해준다.
    병합된 리스트를 다시 버블 정렬한 후, (3)에서 사용한 방법과 동일하게 전공이 "CS"인 원소만 출력한다.

    File Name: hw2_single-linked-list.cpp

    Variables: name, id, major, grade - data에서 불러올 정보들을 담을 변수
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
        char name; int id; string major; char grade;
        Node *next;
}; // 노드 구조체 선언

class List {
    private:
        Node *head;
    public:
        List () {
            head = 0;
        }
    void append(char name, int id, string major, char grade); // 리스트에 원소를 추가하는 함수
    void display(); // 리스트의 모든 원소를 출력하는 함수
    void display(char grade); // 특정 grade를 필터링하여 출력하는 함수
    void display(string major); // 특정 major를 필터링하여 출력하는 함수
    void bubble_sort(); // 리스트를 버블 정렬하는 함수
    void concat(List link); // 하나의 리스트의 끝에 새로운 리스트를 붙이는 함수
};

// Function: List::append
// Description: 리스트에 원소를 추가하는 함수
void List::append(char name, int id, string major, char grade){
        // 임시 노드 선언
        Node* temp = new Node;
        temp->name = name;
        temp->id = id;
        temp->major = major;
        temp->grade = grade;
        temp->next = 0;
        if (head == 0)  // 처음 추가할 경우
                head = temp;
        else {
                Node *ptr = head;
                while (ptr->next != 0)  // 포인터를 끝까지 이동
                        ptr = ptr->next;
                ptr->next = temp;
        }
}

// Function: List::display
// Description: 리스트의 모든 원소를 출력하는 함수
void List::display(){
        Node* ptr = head;
        while (ptr) {   // 포인터가 마지막을 가리킬 때까지
                cout << ptr->name << " " << ptr->id << " " << ptr->major << " " << ptr->grade << endl;
                ptr = ptr->next;
        }
        cout << endl;
}

// Function: List::display(char)
// Description: 특정 grade를 필터링하여 출력하는 함수. 필터링을 원하는 grade를 인자로 받음
void List::display(char grade){
        Node* ptr = head;
        while (ptr) {   // 포인터가 마지막을 가리킬 때까지
            if(ptr->grade == grade){    // 조건에 맞는 경우만 출력
                cout << ptr->name << " " << ptr->id << " " << ptr->major << " " << ptr->grade << endl;
            }
                ptr = ptr->next;
        }
        cout << endl;
}

// Function: List::display(string)
// Description: 특정 major를 필터링하여 출력하는 함수. 필터링을 원하는 major를 인자로 받음
void List::display(string major){
        Node* ptr = head;
        while (ptr) {   // 포인터가 마지막을 가리킬 때까지
            if(ptr->major == major){    // 조건에 맞는 경우만 출력
                cout << ptr->name << " " << ptr->id << " " << ptr->major << " " << ptr->grade << endl;
            }
                ptr = ptr->next;
        }
        cout << endl;
}

// Function: List::bubble_sort
// Description: 리스트를 버블 정렬하는 함수
void List::bubble_sort(){
	Node* ptr = head;  // 현재 가리키고 있는 포인터
    char name; int id; string major; char grade;
	int counter = 0;
	while (ptr) {
		ptr = ptr->next;
		counter++;
	}  // 노드의 개수 확인
	ptr = head;

	for (int j=0; j < counter; j++){
		while (ptr->next){    // 마지막 원소의 바로 전 원소를 가리킬때 까지
			if (ptr->name > ptr->next->name){    // 알파벳 비교
                // 임시 변수에 포인터의 데이터 저장
                name = ptr->name;
                id = ptr->id;
                major = ptr->major;
                grade = ptr->grade;

                // 데이터 swap
                ptr->name = ptr->next->name;
                ptr->id = ptr->next->id;
                ptr->major = ptr->next->major;
                ptr->grade = ptr->next->grade;

                ptr->next->name = name;
                ptr->next->id = id;
                ptr->next->major = major;
                ptr->next->grade = grade;
            }
            ptr = ptr->next;    // 포인터 이동
		}
        // 처음으로 초기화 해줌
		ptr = head;
	}
}

// Function: List::concat
// Description: 하나의 리스트의 끝에 새로운 리스트를 붙이는 함수
void List::concat(List link){
        Node* ptr = head;
        while (ptr) {   // 포인터가 마지막을 가리킬 때까지
            if(!ptr->next){ // 포인터가 마지막일때
                ptr->next = link.head;  // 기존 리스트의 마지막 노드의 next는 새로 붙일 리스트의 head가 된다.
                return;
            }
            ptr = ptr->next;
        }
}

// Main
// 구현한 함수 실행 부분
int main(){
    // 읽어온 데이터를 저장할 변수
    char name; int id; string major; char grade;

    List list;
    ifstream inStream;
    inStream.open("data1.txt");
    // data1.txt를 읽어와 리스트로 만들어줌
    while(inStream >> name >> id >> major >> grade){
        list.append(name, id, major, grade);
    }
    list.bubble_sort();
    cout << "Problem 1 output: " << endl; list.display();
    cout << "Problem 2 output: " << endl; list.display('A');
    inStream.close();

    List list2;
    inStream.open("data2.txt");
    while(inStream >> name >> id >> major >> grade){
        list2.append(name, id, major, grade);
    }   // 새로운 리스트 생성
    list.concat(list2); // data2.txt를 읽어와 만든 list2를 기존 list에 붙임
    list.bubble_sort();
    cout << "Problem 3 output: " << endl; list.display("CS");

    inStream.close();

}
