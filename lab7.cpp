#include <iostream>

using namespace std;

class Heap{
private:
    int max_size;
    int current_size;
    int* heap;
public:
    Heap(int max_size){
        this->max_size = max_size;
        heap = new int[max_size+1];
        current_size = 0;
    }
    bool isFull(){
        return current_size == max_size;
    }
    bool isEmpty(){
        return !current_size;
    }
    void insertHeap(int data);
    int popHeap();
    void showHeap();
    int HeapLevel();
    ~Heap(){
        delete[] heap;
    }
};

void Heap::insertHeap(int data){
    if(isFull()){
        cout << "Heap is Full" << endl;
        return;
    }
    int i = ++current_size;
    while((i != 1) && (data > heap[i/2] )){
        heap[i] = heap[i/2];
        i = i/2;
    }
    heap[i] = data;
}

int Heap::popHeap(){
    if(isEmpty()){
        cout << "Heap is Empty" << endl;
        return -1;
    }
    int parent = 1, child = 2;
    int item = heap[1]; // 가장 높은 수 저장
    int temp = heap[current_size--]; // 마지막 원소와 swap

    while(child <= current_size){
        if((child < current_size) && (heap[child] < heap[child+1]))
            child++;
        if(temp >= heap[child]) break;
        heap[parent] = heap[child];
        parent = child;
        child = child * 2;
    }
    heap[parent] = temp;
    return item;
}

void Heap::showHeap(){
    if(!isEmpty()){
        for(int i = 1; i < current_size + 1; i++){
            cout << heap[i] << " ";
        }
        cout << endl;
    }
    else { cout << "Heap is Empty" << endl; }
}

int Heap::HeapLevel(){
    int temp = current_size;
    int level = 0;
    while(temp != 1){
        temp /= 2;
        level++;
    }
    return level + 1;
}

int main(){
    Heap t1(8);
    if(t1.isEmpty())
        cout << "Heap is Empty" << endl;

    t1.insertHeap(8);
    t1.insertHeap(6);
    t1.insertHeap(4);
    t1.insertHeap(2);
    t1.insertHeap(5);
    t1.insertHeap(3); // Initialize
    //t1.popHeap();
    t1.showHeap();

    t1.insertHeap(9); // insert test
    t1.showHeap();
    t1.insertHeap(7); // insert test
    t1.showHeap();

    if(t1.isFull())
        cout << "Heap is Full" << endl;

    cout << "Heap Level " << t1.HeapLevel() << endl;

    t1.popHeap(); // delete test
    t1.showHeap();
}
