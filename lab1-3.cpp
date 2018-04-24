#include <iostream>

using namespace std;

int sum(int n){
    if(n == 1){
        cout << n << " = ";
        return n;
    }
    else{
        cout << n << "+";
        return n + sum(n - 1);
    }
}

int main(int argc, char const *argv[]) {
    /* code */
    int n = 0;

    cin >> n;
    cout << sum(n);
    return 0;
}
