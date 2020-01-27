#include <iostream>
#include <vector>

struct Node {
    std::string val;
    Node* left;
    Node* right;
    Node* parent;
    Node(std::string val): val(val) {}
};


int main(int argc, char *argv[]){
    std::vector<char*> args;

    if(argc >= 2){
        for(int i = 1; i < argc; i++){
            args.push_back(argv[i]);
        }
    }

    for(auto &c : args){
        std::cout << c << "\n";
    }

    return 0;
}