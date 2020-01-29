#include <algorithm>
#include <iostream>
#include <string>
#include <stack>
#include <iomanip>

enum Type{
    Integer = 0,
    Operator = 1
};

struct Node{
    Type type;
    std::string val;
    Node* left = nullptr;
    Node* right = nullptr;
};

Node* buildTree(std::string::reverse_iterator begin, std::string::reverse_iterator end) {
    if(end>= begin){
        std::string::reverse_iterator it = std::find(begin, end,'-');
        if(it == end) {
            std::string::reverse_iterator it = std::find(begin, end,'+');
            if(it == end) {
                std::string::reverse_iterator it = std::find(begin, end,'*');
                if(it == end) {
                    std::string::reverse_iterator it = std::find(begin, end,'/');
                    if(it == end) {
                        std::cout << "Hello\n";
                        Node* temp = new Node;
                        std::string tempString = std::string(begin, end);
                        std::reverse(tempString.begin(), tempString.end());
                        temp->val = tempString;
                        temp->type = Integer;
                        //std::cout << tempString << "\n";
                        return temp;
                    }
                }
            }
        }
        Node* temp = new Node;
        std::cout << *it << "\n";
        temp->val = *it;
        temp->type = Operator;
        temp->left = buildTree(begin, it - 1);
        temp->right = buildTree(it+1, end);

        return temp;
    }
    return nullptr;
}

void del(Node* root){
    if(root->left) del(root->left);
    if(root->right) del(root->right);
    delete root;
}

void print(Node* root, int indent = 0) {
    if(root != NULL){
                std::cout << (root->type == Operator ? "OP: " : "INT: ") << root->val << "\n";

        if(root->left) print(root->left, indent + 4);
        if(root->right) print(root->right, indent + 4);
        if(indent) {
            std::cout << std::setw(indent) << " ";
        }

    }
}


int main(int argc, char *argv[]){
    if(argc <= 1) {
        return 0;
    }
    std::string a = argv[1];
    

    Node* root = buildTree(a.rbegin(),a.rend());
    std::cout << a << "\n";

    print(root);

    del(root);


    
    

    return 0;
}