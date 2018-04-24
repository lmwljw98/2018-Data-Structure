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
        void insertLast(int data);
        void forwardList(); // print from Head node
        void backwardList(); // Print from last node
        int listLength();
        void locateCurrent(int Nth);
        int isEmpty();
        void insertAfter(int Nth, int data);
        void insertBefore(int Nth, int data);
        void deleteNth(int Nth);
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
        while (p != 0) {
            cout << p->data << endl;
            p = p->prev;
        }
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
        // cout << "Position #" << pos << " data is " << current->data << endl;
    }
    else
        cout << "No such a line" << endl;
}

void List::insertAfter(int Nth, int data){
    locateCurrent(Nth);
    Node *temp = new Node(data);
    Node *p;
    if (head == 0)
        head = temp; // if empty list
    else {
        p = current;
        temp->next = p->next;
        temp->prev = p;
        p->next->prev = temp;
        p->next = temp;
    }
}

void List::insertBefore(int Nth, int data){
    locateCurrent(Nth);
    Node *temp = new Node(data);
    Node *p;
    if (head == 0)
        head = temp; // if empty list
    else {
        p = current;
        p->prev->next = temp;
        temp->prev = p->prev;
        temp->next = p;
        p->prev = temp;
    }
}

void List::deleteNth(int Nth) {
    Node *p, *q;
    locateCurrent(Nth);
    if (head == 0) {
        cout << "List is empty!" << endl;
    }
    else if (head == current) { // 삭제될 노드가 head 일 경우
        if (head->next != 0) { // head 가 only node 아닐경우
            p = head;
            head = head->next;
            head->prev = 0;
            delete p;
        }
        else
            head = 0; // head only node
    }
    else {
        p = current;
        if (p->next != 0) {
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
        }
        else if(p->next == 0){
            p->prev->next = 0;
            delete p;
        }
    }
}

int main() {
    List l1;
    l1.insertLast(10); l1.insertLast(20); l1.insertLast(30); l1.insertLast(100);
    l1.deleteNth(1);
    l1.forwardList();
    l1.insertAfter(2, 40);
    l1.forwardList();
    l1.insertBefore(3, 50);
    l1.forwardList();
    l1.deleteNth(5);
    l1.forwardList();
    l1.backwardList();
    l1.deleteNth(1);
    l1.forwardList();
}
