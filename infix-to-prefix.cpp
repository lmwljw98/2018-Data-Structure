#include <iostream>
#include <cstring>
#include <string>

using namespace std;

// Stack
const int Stack_Size = 100;

class Stack {
    private:
        char stack[Stack_Size]; int top;
    public:
        Stack() {
                top = -1;
        }
        void push(int val) {
            if(!isFull())
                stack[++top] = val;
            else
                cout << "Stack is full" << endl;
        }
        char pop() {
            if(!isEmpty())
                return stack[top--];
            else
                cout << "Stack is empty" << endl;
        }
        bool isEmpty() {
                return top == -1;
        }
        bool isFull() {
                return top == Stack_Size - 1;
        }
        char checkTop(){
            if(!isEmpty())
                return stack[top];
            else
                return -1;
        }
        };
int main(){
    Stack s1;
    Stack s2;
    char input[11] = "";
    string postfix = "";
    int i = 0;
    char temp;
    cin >> input;
    cout << input << endl;
    while(input[i] != '\0'){
        if(input[i] == '('){
            s1.push(input[i]);
        }
        else if(input[i] == ')'){
            while(s1.checkTop() != '('){
                temp = s1.pop();
                cout << temp;
                postfix += temp;
            }
            s1.pop();
        }
        else if(input[i] == '+' || input[i] == '-'){
            if(s1.checkTop() != '*' && s1.checkTop() != '/'){
                s1.push(input[i]);
            }
            else{
                temp = s1.pop();
                cout << temp;
                s1.push(input[i]);
                postfix += temp;
            }
        }
        else if(input[i] == '*' || input[i] == '/'){
            if(s1.checkTop() == '+' || s1.checkTop() == '-'){
                temp = s1.pop();
                cout << temp;
                s1.push(input[i]);
                postfix += temp;
            }
            else{
                s1.push(input[i]);
            }
        }
        else if(input[i] == '$'){
            while(!s1.isEmpty()){
                temp = s1.pop();
                cout << temp;
                postfix += temp;
            }
        }
        else{
            temp = input[i];
            cout << temp;
            postfix += temp;
        }
        i++;
    }
    cout << endl;
    int op1; int op2;
    int s[10];
    int idx = 0;
    for(int j = 0; j <= postfix.size(); j++){
        if(postfix[j] == '+' || postfix[j] == '-' || postfix[j] == '*' || postfix[j] == '/') {
             op2 = s[idx--];
             op1 = s[idx--];
             if(postfix[j] == '+'){
                 s[idx++] = (op1 + op2);
             }
             if(postfix[j] == '-'){
                 s[idx++] = (op1 - op2);
             }
             if(postfix[j] == '*'){
                 s[idx++] = (op1 * op2);
             }
             if(postfix[j] == '/'){
                 s[idx++] = (op1 / op2);
             }
        }
        else{
            s[idx++] = postfix[j];
        }
    }
    cout << s[idx] << endl;

}
