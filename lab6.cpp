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

    void visit(TreeNode<T>* current) {
        cout << current->data << " ";
    }

    // 전위 순회
    void preorder(TreeNode<T>* current) {
        if (current != 0) {
            visit(current);
            preorder(current->left);
            preorder(current->right);
        }
    }

    // 중위 순회
    void inorder(TreeNode<T>* current) {
        if (current != 0) {
            inorder(current->left);
            visit(current);
            inorder(current->right);
        }
    }

    // 후위 순회
    void postorder(TreeNode<T>* current) {
        if (current != 0) {
            postorder(current->left);
            postorder(current->right);
            visit(current);
        }
    }

    TreeNode<T>* getRoot() {
        return head;
    }
};

int main() {
    Tree<char> tree;
    char* input = new char[100];
    input = "8+9-2*3";
    tree.buildTree(input);

    cout << "inorder : ";
    tree.inorder(tree.getRoot()); cout << endl;
    cout << "postorder : ";
    tree.postorder(tree.getRoot()); cout << endl;
    cout << "preorder : ";
    tree.preorder(tree.getRoot()); cout << endl;
    cout << "output : " << tree.evalTree(tree.getRoot()) << endl;

    delete[] input;
    cout << endl;

    Tree<char> tree2;
    char* input2 = new char[100];
    input2 = "a+b*c-d";
    tree2.buildTree(input2);

    cout << "inorder : ";
    tree2.inorder(tree2.getRoot()); cout << endl;
    cout << "postorder : ";
    tree2.postorder(tree2.getRoot()); cout << endl;
    cout << "preorder : ";
    tree2.preorder(tree2.getRoot()); cout << endl;

    delete[] input2;
}
