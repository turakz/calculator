#ifndef _CALCULATOR
#define _CALCULATOR

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>

using namespace std;

//terminators and token representations
const string prompt = "[calculator]: ";
const string result = "= ";
const char digit = '1';
const char eval = '\n';
const char quit = '$';
const char negative = '-';

class Token{

    private:
        char kind;
        double value;

    public:
        Token()
            :kind('\r'), value(0){}
        Token(char c)
            :kind(c), value(0){}
        Token(char c, double v)
            :kind(c), value(v){}

        //getters
        char getKind(){
            return kind;
        }

        double getValue(){
            return value;
        }

        //setters
        void setKind(char c){
            kind = c;
        }

        void setValue(double v){
            value = v;
        }

};

class Token_stream : protected Token {

    private:
        bool full;
        Token buffer;

    public:
        Token_stream()
           :full(false), buffer(0){} 
        
        //getters
        Token get();

        //setters
        void setBuffer(Token t){
            //copy t to token buffer
            buffer = t;
            //set buffer flag
            full = true;
        }

        void setBufferFlag(bool state){
            full = state;
        }
        //helpers
        void putback(Token t);
        void ignore(char c);
        bool isFull(){
            return full;
        }



};

class Calculator : public Token_stream {

    public:
        
        Calculator();

        Token t;

        //parsing and computation
        double term();
        double expr();
        double stmt();


};

#endif //end of classes

