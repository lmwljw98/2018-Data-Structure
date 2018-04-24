#include <iostream>

using namespace std;

int sum(int n, int m){
    if(n == 0){
        cout << "add(" << n << "," << m << ")";
        return m;
    }
    else{
        cout << "add(" << n << "," << m << ")" << endl;
        return sum(n-1, m+1);
    }
}

int main(int argc, char const *argv[]) {
    /* code */
    int n, m = 0;

    cin >> n >> m;
    cout << endl << "sum = " << sum(n, m);
    return 0;
}
