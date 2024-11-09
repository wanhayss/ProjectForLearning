#include <iostream>

int main(){
    char op;
    double a;
    double b;
    double c;

    std::cout<<"Enter the math operation (+, -, *, /): ";
    std::cin>>op;
        
    switch(op){

        case '+':
            std::cout<<"Enter first number: ";
            std::cin>>a;
            std::cout<<"Enter second number: ";
            std::cin>>b;
            c = a + b;
            std::cout<<"Result: "<< c;
            break;
        case '-':
            std::cout<<"Enter first number: ";
            std::cin>>a;
            std::cout<<"Enter second number: ";
            std::cin>>b;
            c = a - b;
            std::cout<<"Result: "<< c;
            break;
        case '*':
            std::cout<<"Enter first number: ";
            std::cin>>a;
            std::cout<<"Enter second number: ";
            std::cin>>b;
            c = a * b;
            std::cout<<"Result: "<< c;
            break;
        case '/':
            std::cout<<"Enter first number: ";
            std::cin>>a;
            std::cout<<"Enter second number: ";
            std::cin>>b;
            c = a / b;
            std::cout<<"Result: "<< c;
            break;
        default:
            std::cout<<"please only Enter (+, -, *, /)";
    }
    return 0;
}