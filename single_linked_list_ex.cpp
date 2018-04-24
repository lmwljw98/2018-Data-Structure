#include <iostream>

using namespace std;

struct Node {
        int data;
        Node *next;
};

class List {
    private:
        Node *head;
    public:
        List () {
            head = 0;
        }
    void insert(int);
    void append(int);
    void deleteNode(int);
    bool isEmpty();
    void display();
};

void List::insert(int data) // 맨앞에 삽입
{
        Node *temp = new Node;
        temp->data = data;
        temp->next = 0;
        if (head != 0) {
                temp->next = head;
                head = temp;
        }
        else head = temp;
}

void List::append(int data) // 맨뒤에 추가
{
        Node *temp = new Node;
        temp->data = data;
        temp->next = 0;
        if (head == 0)
                head = temp;
        else {
                Node *ptr = head;
                while (ptr->next != 0)
                        ptr = ptr->next;
                ptr->next = temp;
        }
}

void List::deleteNode(int num)
{
        Node *p, *q;
        if (head->data == num) { //head 삭제
                p = head;
                head = head->next;
                delete p;
        }
        else {
                p = head;
                while (p != 0 && p->data != num) {
                        q = p;
                        p = p->next;
                }
                if (p != 0) {
                        q->next = p->next;
                        delete p;
                }
                else
                        cout << num << " is not in the list\n";
        }
}

bool List::isEmpty()
{
        if (head == 0) return true;
        else return false;
}

void List::display()
{
        Node *ptr;
        ptr = head;
        while (ptr) {
                cout << ptr->data;
                ptr = ptr->next;
        }
        cout << endl;
}

int main()
{
        List l1;
        l1.insert(40);
        l1.insert(30);
        l1.append(50);
        l1.append(80);
        l1.deleteNode(80);
        l1.display();
}
