#include <iostream>
#include <fstream>
#include <string>


class Node{
public:
    char data;
    Node *left, *right;
    Node(char data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

class Stack{
public:
    Node *node;
    Stack *next;
    Stack(Node *node){
        this->node = node;
        next = NULL;
    }
};

class ExpTree{
    Stack *root;
public:
    ExpTree(){
        root = NULL;
    }

    void clear(){
        root = NULL;
    }

    void push(Node *p){
        if (root == NULL)
            root = new Stack(p);
        else{
            Stack *n = new Stack(p);
            n->next = root;
            root = n;
        }
    }

    Node *pop(){
        if (root == NULL){
            std::cout<<"Pop ERROR"<<std::endl;
        }
        else{
            Node *p = root->node;
            root = root->next;
            return p;
        }
    }

    Node *peek(){
        return root->node;
    }

    void insert(char value){
        if (isDigit(value)){
            Node *n = new Node(value);
            push(n);
        }
        else if (isOperator(value)){
            Node *n = new Node(value);
            n->left = pop();
            n->right = pop();
            push(n);
        }
    }

    bool isOperator(char character){
        return character == '+' || character == '-' || character == '*' || character == '/';
    }

    int toDigit(char character){
        return character - '0';
    }

    bool isDigit(char character){
        return character >= '0' && character <= '9';
    }

    void create(std::string eqn){
        for (int i = eqn.length() - 1; i >= 0; i--) {
                insert(eqn[i]);

        }
    }

    double evaluate(){
        return evaluate(peek());
    }

    double evaluate(Node *p) {
        if (p->left == NULL && p->right == NULL)
            return toDigit(p->data);
        else {
            double result = 0.0;
            double left = evaluate(p->left);
            double right = evaluate(p->right);
            char o = p->data;
            switch (o) {
                case '+':
                    result = left + right;
                    break;
                case '-':
                    result = left - right;
                    break;
                case '*':
                    result = left * right;
                    break;
                case '/':
                    result = left / right;
                    break;
            }
            return result;
        }
    }

};

std::ifstream fin("C:\\Users\\claus\\CLionProjects\\untitled10\\input.txt");

int main(){
    int i, counter=0;
    std::string exp;
    ExpTree e;
    std::getline(fin,exp);
    for(i=0 ; i<=exp.length() ; i++ ){
        if(exp[i] == '(')
            counter++;
        if(exp[i] == ')')
            counter--;
    }
    if (counter == 0){
        e.create(exp);
        std::cout<<"\n\nResult: "<<e.evaluate()<<std::endl;
        return 0;
    }
    std::cout<<"The number of parentheses is unequal, please check it!";
    fin.close();
    return 0;
}
