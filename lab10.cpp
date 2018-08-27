#include <iostream>

using namespace std;

const int MAX_SIZE = 6;

int cost[MAX_SIZE][MAX_SIZE] = {
                                {100, 20, 15, 100, 100, 100},
                                {100, 100, 100, 100, 10, 30},
                                {100, 4, 100, 100, 100, 10},
                                {100, 100, 100, 100, 100, 100},
                                {100, 100, 100, 15, 100, 100},
                                {100, 100, 100, 4, 10, 100}
                            };
bool found[MAX_SIZE];
int dist[MAX_SIZE];

void shortestPath(int);
int choose();

void shortestPath(int start_vertex){
    for(int i = 0; i < MAX_SIZE; i++){
        found[i] = false;
        dist[i] = cost[start_vertex][i];
    }
    found[start_vertex] = true;
    dist[start_vertex] = 0;

    for(int i = 0; i < MAX_SIZE; i++){
        int min_index = choose();
        found[min_index] = true;

        if(i < MAX_SIZE-1){
            cout << "Dist: ";
            for(int k = 0; k < MAX_SIZE; k++)
                cout << dist[k] << " ";
            cout << "(Selected Node: " << min_index << ")";
            cout << endl;
        }

        for(int j = 0; j < MAX_SIZE; j++){
            if(!found[j]){
                dist[j] = min(dist[min_index] + cost[min_index][j], dist[j]);
            }
        }

    }
}

int choose(){
    int min_index, minimum = 100;
    for(int i = 0; i < MAX_SIZE; i++){
        if(dist[i] < minimum && !found[i]){
            minimum = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

int main(){
    for(int i = 0; i < MAX_SIZE; i++){
        for(int j = 0; j < MAX_SIZE; j++){
            cout << cost[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    shortestPath(0);
}
