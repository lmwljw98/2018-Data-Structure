#include <iostream>

using namespace std;

class Node {
    private:
        int data;
        Node *next;
        Node *prev;
        Node (int val){
            data = val; next = 0; prev = 0;
        }
    friend class List;
};
class List {
    private:
        Node *head;
        Node *current;
    public:
        List();
        ~List();
        void insertFirst(int data);
        void insertLast(int data);
        void insertList(int data); //Node insert
        void deleteList(int key); //Node delete
        void forwardList(); // print from Head node
        void backwardList(); // Print from last node
        void searchList(int key); // search data
        int listLength();
        void locateCurrent(int Nth);
        int isEmpty();
};

List::List() {
    head = 0;
    current = 0;
}

int List::isEmpty() {
    return (head == 0);
}

List::~List() {
    Node *p;
    while (head != 0) {
        p = head; head = head->next;
        delete p;
    }
}

void List::insertFirst (int data) {
    Node *temp = new Node(data);
    if (head == 0) head = temp;
    else {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
}

void List::insertLast(int data) {
    Node *temp = new Node(data); Node *p;
    if (head == 0) head = temp; // if empty list
    else {
        p = head;
        while (p->next != 0) p = p->next; // move to the last
        p->next = temp;
        temp->prev = p;
    }
}

void List::insertList(int data) {   // 숫자의 경우(오름차순)
    Node *temp = new Node(data);
    Node *p, *q;
    if (head == 0) // 첫노드일때
        head = temp;
    else if (temp->data < head->data) { //head node 앞에 삽입
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
    else { // 가운데 삽입
        p = head;
        q = head;
        while ((p != 0) && (p->data < temp->data)) { //이동
            q = p;
            p = p->next;
        }
        if (p != 0) { // 중간에 삽입
            temp->next = p;
            temp->prev = q;
            q->next = temp;
            p->prev = temp;
        }
        else { // temp 가 큰경우
            q->next = temp;
            temp->prev = q;
        }
    }
}

void List::deleteList(int key) {
    Node *p, *q;
    if (head == 0) {
        cout << "List is empty!" << endl;
    }
    else if (head->data == key) { // 삭제될 노드가 head 일 경우
        if (head->next != 0) { // head 가 only node 아닐경우
            p = head;
            head = head->next;
            head->prev = 0;
            delete p;
        }
        else
            head = 0; // head only node
    }
    else { // 가운데 노드가 삭제될 경우
        q = head; p = head;
        while (p != 0 && p->data != key) { //이동
            q = p;
            p = p->next;
        }
        if(!p){
            cout << key << " is not in the list\n";
            return;
        }
        if (p->next != 0 && p->data==key) {
            q->next = p->next;
            p->next->prev = q;
            delete p;
        }
        else if (p->next == 0 && p->data == key){
            q->next = 0;
            delete p;
        }
    }
}

void List::forwardList() {
    if (!isEmpty()) {
        Node *p = head;
        cout << "----- Forward List -----\n";
        while (p != 0) {
            cout << p->data << endl;
            p = p->next;
        }
    }
    else
        cout << "List is empty!\n";
}

void List::backwardList() {
    if (!isEmpty()) {
        Node *p = head;
        while (p->next != 0)
            p = p->next;
        cout << "----- Backward List -----\n";
        while (p!= 0) {
            cout << p->data << endl;
            p = p->prev;
        }
    }
    else
        cout << "List is empty!\n";
}

void List::searchList(int key) {
    if (!isEmpty()) {
        Node *p = head;
        while (p != 0 && p->data != key)
            p = p->next;
        if (p != 0)
            cout << p->data << " is in the list\n";
        else
            cout << key << " is not in the list\n";
    }
    else
        cout << "List is empty!\n";
}

int List::listLength() {
    int count = 0;
    if (!isEmpty()) {
        Node *p = head;
        while (p != 0) {
            p = p->next;
            count++;
        }
    }
    else
        cout << "List is empty!\n";
    return count;
}

void List::locateCurrent(int Nth) {
    Node *p; int pos = 1;
    if (head == 0)
        cout << "List is empty!" << endl;
    else if (listLength() >= Nth) {
        p = head;
        while (pos != Nth) {
            p = p->next;
            pos++;
        }
        current = p;
        cout << "Position #" << pos << " data is " << current->data << endl;
    }
    else
        cout << "No such a line" << endl;
}

int main() {
    List l1;
    l1.insertList(1);
    l1.insertList(0);
    l1.insertLast(3);
    l1.forwardList();
    cout << l1.listLength() << endl;
    l1.locateCurrent(3);
    l1.deleteList(2);
    l1.forwardList();
    l1.backwardList();
    l1.deleteList(0); l1.deleteList(1); l1.deleteList(3);
    l1.forwardList();
    l1.backwardList();
    l1.locateCurrent(2);
    l1.listLength();
    l1.deleteList(2);
}
