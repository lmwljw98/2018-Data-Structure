#include <iostream>

using namespace std;

const int MAX_SIZE = 7;

class HashTable{
public:
    int key;
    bool empty;
    HashTable(){
        key = -1;
        empty = true;
    }
};
bool findKey(HashTable [], int);
bool insertKey(HashTable [], int);
bool deleteKey(HashTable [], int);
int hashFunc(HashTable [], int);
bool isFull(HashTable []);

int index;

int hashFunc(int key){
    return key % MAX_SIZE;
}

bool isFull(HashTable h1[]){
    for(int i = 0; i < MAX_SIZE; i++){
        if(h1[i].empty) { return false; }
    }
    return true;
}

bool findKey(HashTable h1[], int key){
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

bool insertKey(HashTable h1[], int key){
    if(isFull(h1)) {
        cout << "is full" << endl;
        return false;
    }
    bool check = findKey(h1, key);
    if(check) return false;
    if(!h1[index].empty) return false;
    else{
        h1[index].key = key;
        h1[index].empty = false;
        return true;
    }
}

bool deleteKey(HashTable h1[], int key){
    bool check = findKey(h1, key);
    if(!check) return false;
    else{
        h1[index].empty = true;
        return true;
    }
}

void printTable(HashTable h1[]){
    for(int i = 0; i < MAX_SIZE; i++){
        if(h1[i].empty) { cout << "_" << " "; }
        else { cout << h1[i].key << " "; }
    }
    cout << endl;
}

int main(){
    HashTable h1[MAX_SIZE];
    char ch; bool check; int key;
    while(ch != 'q'){
        cout << "Enter Command(i, f, d, q): ";
        cin >> ch;
        if(ch != 'q'){
            cout << "Enter key: ";
            cin >> key;
            switch(ch){
                case 'i':
                    check = insertKey(h1, key);
                    if(!check) cout << "Cannot insert " << key << endl;
                    break;
                case 'f':
                    check = findKey(h1, key);
                    if(!check) cout << "Cannot Find " << key << endl;
                    else cout << "Found " << key << endl;
                    break;
                case 'd':
                    check = deleteKey(h1, key);
                    if(!check) cout << "Cannot Delete " << key << endl;
                    break;
                default:
                    cout << "Bad Command" << endl;
                }
        }
        else break;

        printTable(h1);
    }
    return 0;
}
