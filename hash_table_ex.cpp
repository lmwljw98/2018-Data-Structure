#include <iostream>

using namespace std;

const int MAX_SIZE = 7;

bool findKey(int);
int insertKey(int);
int deleteKey(int);
int hashFunc(int);
bool isFull();

class HashTable{
public:
    int key;
    bool empty;
    HashTable(){
        key = -1;
        empty = true;
    }
};
HashTable h1[MAX_SIZE];
int index;

int hashFunc(int key){
    return key % MAX_SIZE;
}

bool isFull(){
    for(int i = 0; i < MAX_SIZE; i++){
        if(h1[i].empty) { return false; }
    }
    return true;
}

bool findKey(int key){
    bool found = false;
    index = hashFunc(key);
    int checkFinish = index;

    while(true){
        if(h1[index].key == key){
            found = true;
            break;
        }
        else{
            index = (index + 1) % MAX_SIZE;
            if(index == checkFinish){
                while(!h1[index].empty)
                    index = (index + 1) % MAX_SIZE;
                break;
            }
        }
    }
    return found;
}

int insertKey(int key){
    if(isFull()) {
        cout << "is full" << endl;
        return -1;
    }
    bool check = findKey(key);
    if(check) return -1;
    if(!h1[index].empty) return -1;
    else{
        h1[index].key = key;
        h1[index].empty = false;
        return 1;
    }
}

int deleteKey(int key){
    bool check = findKey(key);
    if(!check) return -1;
    else{
        h1[index].empty = true;
        return 1;
    }
}

int main(){
    insertKey(2);
    insertKey(9);
    insertKey(16);
    insertKey(23);
    insertKey(30);
    insertKey(37);
    insertKey(44);
    insertKey(51);
    for(int i = 0; i < MAX_SIZE; i++)
        cout << h1[i].key << endl;
    return 0;
}
