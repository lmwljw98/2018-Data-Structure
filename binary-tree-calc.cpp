#include <iostream>
#include <ctype.h>

using namespace std;
char prec[4][2] = { '*', 2, '/', 2, '+', 1, '-', 1 };

template <typename T>
class Tree;

template <typename T>
class TreeNode {
    friend class Tree<T>;
private:
    T data;
    int prio;
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode(T data = 0, TreeNode* left = 0, TreeNode* right = 0, int prio = 4) {
        this->data = data;
        this->left = left;
        this->right = right;
        this->prio = prio;
    }
};

template <typename T>
class Tree {
private:
    TreeNode<T>* root;
    TreeNode<T>* head;
public:
    Tree() {
        root = 0;
        head = 0;
    }

    void buildTree(const char* input) {
        int i = 0;
        while(input[i] != '\0'){
            TreeNode<T>* temp = new TreeNode<T>(input[i]);
            for(int j = 0; j < 4; j++){
                if(temp->data == prec[j][0])
                    temp->prio = prec[j][1];
            }
            if(temp->prio == 4)
                add_operand(temp);
            else
                add_operator(temp);
            i++;
        }
    }

    void add_operand(TreeNode<T>* temp) {
        if(head == 0){
            head = temp;
            return;
        }
        TreeNode<T>* p = head;
        while(p->right != 0){
            p = p->right;
        }
        p->right = temp;
    }

    void add_operator(TreeNode<T>* temp) {
        if (head->prio >= temp->prio){
            temp->left = head;
            head = temp;
        }
        else{
            temp->left = head->right;
            head->right = temp;
        }
    }

    int evalTree (TreeNode<T>* p) {
        int value = 0;
        int left = 0;
        int right = 0;
        if(p != 0){
            if(isdigit(p->data)){
                value = p->data - '0';
            }
            else{
                left = evalTree(p->left);
                right = evalTree(p->right);
                switch (p->data){
                    case '+':
                        value = left + right;
                        break;
                    case '-':
                        value = left - right;
                        break;
                    case '*':
                        value = left * right;
                        break;
                    case '/':
                        value = left / right;
                        break;
                }
            }
        }
        return value;
    }

    TreeNode<T>* getRoot() {
        return head;
    }
};

int main() {
    Tree<char> tree;
    char* input = new char[100];
    cin >> input;
    tree.buildTree(input);
    cout << tree.evalTree(tree.getRoot()) << endl;
    delete[] input;
}
