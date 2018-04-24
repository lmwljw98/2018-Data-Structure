#include <iostream>

using namespace std;

int fibo(int n){
    if (n == 0 || n == 1){
        return n;
    }
    else{
        return fibo(n-2) + fibo(n-1);
    }
}

int main(int argc, char const *argv[]) {
    int n = 0;
    cin >> n;

    cout << fibo(n);

    return 0;
}
// 0 1 1 2 3 5 8 13 21 34
