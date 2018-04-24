#include <iostream>
#include <fstream>

using namespace std;
int findMax(int* data, int n);
int findMin(int data[], int n);
int maxindex = 0;
int minindex = 0;
int main(){
    int data[10];
    ifstream in;
    in.open("lab0-1.dat");
    for(int i = 0; i < 10; i++)
        in >> data[i];
    int a = findMax(data, 10);
    int b = findMin(data, 10);
    cout << a << " " << b << endl;
    cout << maxindex+1 << " " << minindex+1 << endl;
}

int findMax(int* data, int n){
    int max = data[0];
    for(int i = 1; i < n; i++){
        if(max < data[i]){
            max = data[i];
            maxindex = i;
        }
    }
    return max;
}

int findMin(int data[], int n){
    int min = data[0];
    for(int i = 1; i < n; i++){
        if(min > data[i]){
            min = data[i];
            minindex = i;
        }
    }
    return min;
}
