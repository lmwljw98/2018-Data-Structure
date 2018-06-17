#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_VERTICES = 6;

int lengthOfArray(const int []);
void printMatrix();

int cost[MAX_VERTICES][MAX_VERTICES] = { {100, 6, 1, 5, 100, 100}, {6, 100, 4, 100, 3, 100}, {1, 4, 100, 5, 6, 5},
                                        {5, 100, 5, 100, 100, 2}, {100, 3, 6, 100, 100, 6}, {100, 100, 5, 2, 6,100} };

class Graph {
private:
    int T[MAX_VERTICES];
    bool selected[MAX_VERTICES];
public:
    int minCost;
    Graph(){
        init();
    }
    void init(){
        minCost = 0;
        for(int i = 0; i < MAX_VERTICES; i++){
            selected[i] = false;
            T[i] = -1;
        }
    }
    int prim();
    int prim_extra();
};

int Graph::prim(){
    int minCost = 0;
    T[0] = 0;
    selected[0] = true;
    while(lengthOfArray(T) < MAX_VERTICES){
        int len = lengthOfArray(T);
        int minimum = 100;
        int select_row = 0;
        int select_col = 0;
        int i = T[len-1];
        for(int j = 0; j < MAX_VERTICES; j++){
            int temp_min = cost[i][j];
            if(minimum > temp_min && !selected[j]){
                minimum = temp_min;
                select_row = i;
                select_col = j;
            }
        }

        if(minimum == 100) break;

        T[len] = select_col;
        selected[select_col] = true;

        if (lengthOfArray(T) < MAX_VERTICES){
            cout << select_row + 1 << "," << select_col + 1 << " > ";
        }
        else{
            cout << select_row + 1 << "," << select_col + 1 << endl;
        }

        minCost += minimum;
    }
    if(lengthOfArray(T) < MAX_VERTICES) { cout << "No Spanning Tree" << endl; return -1; }
    return minCost;
}

int Graph::prim_extra(){
    int minCost = 0;
    T[0] = 0;
    selected[0] = true;
    while(lengthOfArray(T) < MAX_VERTICES){
        int len = lengthOfArray(T);
        int minimum = 100;
        int select_row = 0;
        int select_col = 0;
        for(int i = 0; i < len; i++){
            for(int j = 0; j < MAX_VERTICES; j++){
                int temp_min = cost[T[i]][j];
                if(minimum > temp_min && !selected[j]){
                    minimum = temp_min;
                    select_row = T[i];
                    select_col = j;
                }
            }
        }
        if(minimum == 100) break;

        T[len] = select_col;
        selected[select_col] = true;

        if (lengthOfArray(T) < MAX_VERTICES){
            cout << select_row + 1 << "," << select_col + 1 << " > ";
        }
        else{
            cout << select_row + 1 << "," << select_col + 1 << endl;
        }

        minCost += minimum;
    }
    if(lengthOfArray(T) < MAX_VERTICES) { cout << "No Spanning Tree" << endl; return -1; }
    return minCost;
}


int lengthOfArray(const int a[]){
    for(int i = 0; i < MAX_VERTICES; i++){
        if(a[i] == -1){
            return i;
        }
    }
    return MAX_VERTICES;
}

void printMatrix(){
    cout << "     ";
    for(int i = 0; i < MAX_VERTICES; i++){
        cout << "v" << i+1 << "   ";
    }
    cout << endl;
    for(int i = 0; i < MAX_VERTICES; i++){
        for(int j = 0; j < MAX_VERTICES; j++){
            if(j == 0) cout << "v" << i+1 << "  ";
            cout << cost[i][j] << "   ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    Graph g1;
    printMatrix();
    cout << "Prim's Algorithm Total cost: " << g1.prim() << endl;
    g1.init(); cout << endl;
    cout << "Prim's Algorithm Total cost: " << g1.prim_extra() << endl;
}
