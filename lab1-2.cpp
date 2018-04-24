#include <iostream>

using namespace std;

int sum(int n, int m){
    while (n > 0){
        cout << "n = " << n-- << ", m = " << m++ << endl;
    }
    cout << "n = " << n << ", m = " << m << endl;
    return m;
}

int main(int argc, char const *argv[]) {
    /* code */
    int n, m = 0;

    cin >> n >> m;
    cout << endl << "sum = " << sum(n, m);
    return 0;
}
