#include <iostream>

using namespace std;

const int MAX_SIZE = 6;

int cost[MAX_SIZE][MAX_SIZE] = {
                                {0, 50, 10, 999, 45, 999},
                                {999, 0, 15, 999, 10, 999},
                                {20, 999, 0, 15, 999, 999},
                                {999, 20, 999, 0, 35, 999},
                                {999, 999, 999, 30, 0, 999},
                                {999, 999, 999, 3, 999, 0}
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

        for(int j = 0; j < MAX_SIZE; j++){
            if(!found[j]){
                dist[j] = min(dist[min_index] + cost[min_index][j], dist[j]);
            }
        }
        cout << dist[i] << " ";
    }
}

int choose(){
    int min_index, minimum = 999;
    for(int i = 0; i < MAX_SIZE; i++){
        if(dist[i] < minimum && !found[i]){
            minimum = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

int main(){
    shortestPath(0);
}
