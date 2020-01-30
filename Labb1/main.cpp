#include <algorithm>
#include <iostream>
#include <string>
#include <stack>
#include <iomanip>
#include <vector>

enum Type{
    Integer = 0,
    Operator = 1
};

struct Token {
    Type type;
    int val;
    Token(Type type, int val): type(type), val(val){}
};

struct Node{
    Token token;
    Node* left = nullptr;
    Node* right = nullptr;
};
bool isOperator(char in){
    return (in == '+') || (in == '-') || (in == '*') || (in == '/');
}

std::vector<Token> makeTokens(std::string input) {
    std::vector<Token> ret;

    std::string temp = "";

    for(auto &c : input){
        if(isOperator(c)) {
            std::cout << temp << "\n";
            ret.push_back(Token(Integer,std::stoi(temp)));
            std::cout << c << "\n";
            ret.push_back(Token(Operator, c));
            temp = "";
        } else {
            temp += c;
        }
    }
    if(temp != ""){
        ret.push_back(Token(Integer,std::stoi(temp)));
        std::cout << temp << "\n";
    }
    
}



int main(int argc, char *argv[]){
    if (argc < 1) {
        return 0;
    }   
    auto handledData = makeTokens(argv[1]);
    


    return 0;
}