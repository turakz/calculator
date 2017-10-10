#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;


//Token Class
class Token {

public:

    char kind;
    double value;

    Token(char ch)
        :kind(ch), value(0) {
        }
    Token(char ch, double val)
        :kind(ch), value(val) {
        }


};

//Stream class
class Token_stream{

public:

    bool full = false;
    Token buffer;

    Token_stream()
        :full(false), buffer(0) {}

    Token get();
    void putback(Token t);

};


Token Token_stream::get(){

    //do we have a word in stream already?
    if (full){
        //remove it from stream
        full = false;
        return buffer;
    }

    char c;
    cin >> c;
    //cout <<  "\nc= " << c << "\n";

    switch(c){
    
    //char is of kind digit
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
        {
            //read entire digit (will stop when it hits a character)
            cin.putback(c);
            double val;
            cin >> val;
            return Token('d', val); 
        }

    //char is an operator or terminator, let it represent itself
    case '+': case '-': case '*': case '/': case '!': case '(': case ')':
    case '[': case ']': case ';': case '$':
        {
            return Token(c);
        }

    default:
        cout << "Token_stream::get() -- bad character, case for " << c << " does not exist\n";
        exit(-1);
    
    }


}

void Token_stream::putback(Token t){

    if (full){
        cerr << "Token_stream::putback(Token t): buffer full\n";
        exit(-1);
    }

    //copy t to token buffer
    buffer = t;
    //set buffer flag
    full = true;

}

//object for stream access
Token_stream ts;

//grammar functions
double term();
double expr();
double list();

int main(){
    
    cout << "simple calculator 1.0 (c) 2017 by zachary turak\n";
    cout << "operations supported: + - / * () []\n";
    cout << "terminate input with ; (to print result) and $ (to quit)\n";
    //string prompt = ">>";
    //cout << prompt;
    double result = 0;
    while(cin){

        //got input, did we get a terminator?
        Token t = ts.get();
        //cout << "token kind, value= " << t.kind << ", " << t.value << "\n";
        if(t.kind == ';'){
            cout << "= " << result << "\n";
            //cout << prompt;
            t = ts.get();    
        }
        else if(t.kind == '$'){
            cout << "\ndiscarding most recent input\n";
            cin.ignore();
            cout << "\npress enter to exit... ";
            cin.ignore();
            break;
        }
        ts.putback(t);
        result = list();
    
    }

    return 0;
}


double term(){

    Token t = ts.get();

    switch(t.kind){

    case '[':
        {
            double num = list();
            t = ts.get();
            if (t.kind != ']'){
                cerr << "term() - missing closing ']'\n";
                exit(-1);
            }
            return num;
        }

    case '(':
        {
            double num = list();
            t = ts.get();
            if (t.kind != ')'){
                cerr << "term() - missing closing ')'\n";
                exit(-1);
            }
            return num;
        }

    case 'd':
        return t.value;

    case '-':
        return -term();

    case '$':
        return t.value;

    default:
        cerr << "term() - bad t.kind= " << t.kind << ", " << t.value << endl;
        exit(-1);
    }   

}

double expr(){

    double result = term();
    Token t = ts.get();
    while(true){

        switch(t.kind){

        case '*':
            result *= term();
            t = ts.get();
            break;

        case '/':
            {
                //read ahead
                double num = term();
                if (num == 0){
                    cerr << "expr() - division by 0\n";
                    exit(-1);
                }
                result /= num;
                t = ts.get();
                break;
            }

        default:
            ts.putback(t);
            return result;
        }
    }

}

double list(){

    double result = expr();
    Token t = ts.get();
    while(true){

        switch(t.kind){

        case '+':
            result += expr();
            t = ts.get();
            break;

        case '-':
            result -= expr();
            t = ts.get();
            break;

        default:
            ts.putback(t);
            return result;
        }
    }

}
