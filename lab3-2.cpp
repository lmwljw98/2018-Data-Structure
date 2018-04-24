#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int Stack_Size = 20;

class Stack {
    private:
        char stack[Stack_Size]; int top;
    public:
        Stack() {
                top = -1;
        }
        void push(int val) {
                stack[++top] = val;
        }
        char pop() {
                return stack[top--];
        }
        int isEmpty() {
                return top == -1;
        }
        int isFull() {
                return top == Stack_Size - 1;
        }
        };


int main()
{
        Stack s1;
        ifstream in;
        in.open("lab3-2.txt");
        char buffer[80];
        while(in.getline(buffer, 80)){
            int i = 0;
            // cout << buffer << endl;
            if(strlen(buffer) % 2 == 0){
                for(; i < strlen(buffer)/2; i++)
                    s1.push(buffer[i]);
            }
            else{
                for(; i < strlen(buffer)/2; i++)
                    s1.push(buffer[i]);
                i++;
            }
            while(buffer[i] != '\0'){
                if(buffer[i] != s1.pop()){
                    cout << "error" << endl;
                    break;
                }
                i++;
            }
            if(buffer[i] == '\0'){
                cout << "PALINDROME" << endl;
            }
        }
}
