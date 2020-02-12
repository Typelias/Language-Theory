#include <iostream>
#include <vector>
#include <iostream>
enum token{
    plus,
    integer,
    end_of_program
};

token t;
char lexeme;

std::string program{"99+1001+1"};

std::string::iterator consume = program.begin();



struct op{
    std::vector<op*> children;

    virtual int eval() = 0;

    void add_child(op* o){
        children.push_back(o);
    }
};
struct op_digit: op{
    op_digit(char c): value(c-'0'){
    }
    int eval(){
        return value;
    }
    int value;
};
struct op_int:op{

    op_int(){
    }
    int value;
    int eval() override{
        int result = 0;
        for(auto digit_ops : children){
            result = digit_ops->eval() + 10*result;
        }

        return result;
    }
};
struct op_add:op{
    int eval() override{
        int result = 0;
        for(auto int_ops : children){
            result = int_ops->eval() + result;
        }
        return result;
    }
};

struct op_program:op
{
    int eval() override {
        int result = 0;
        for(auto add_op : children) {
            
            result = add_op->eval() + result;
        }

        return result;
    }
};



void lex(){
    if(consume == program.end()) {
        t = end_of_program;
        return;
    }
    lexeme = *consume++;
    switch (lexeme)
    {
    case '+':
        t= plus;    
        break;
    default:
        t = integer;
        break;
    }
}


op_int* parse_integer(){
    lex();
    auto token = t;
    if(token != integer){
        return nullptr;
    }

    auto op = new op_int;
    op->add_child(new op_digit(lexeme));

    lex();
    while (t == integer) {
        op->add_child(new op_digit(lexeme));
        lex();
    }    

    return op;
}

op_add* parse_add(){
    auto int1 = parse_integer();
    auto token = t;
    if(token == end_of_program) {
        auto op = new op_add();
        op->add_child(int1);
        return op;
    }
    if(token != plus) return nullptr;

    auto int2 = parse_integer();
    auto op = new op_add();
    op->add_child(int1);
    op->add_child(int2);
    return op;
}

op_program* parse_program() {
    auto add1 = parse_add();
    auto token = t;
    if(token == end_of_program) {
        auto op = new op_program();
        op->add_child(add1);
        return op;
    }
    std::cout << token << "\n";
    if(token != plus) return nullptr;
    auto add2 = parse_add();
    auto op = new op_program;
    op->add_child(add1);
    op->add_child(add2);
    return op;
}


int main(){
    auto op = parse_program();
    std::cout << op->eval() << "\n";

}