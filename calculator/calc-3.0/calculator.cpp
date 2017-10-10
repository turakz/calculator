#include "calculator.h"

//Token_stream class implementation
Token Token_stream::get(){
    
    //do we have a token in stream already?
    if (isFull()){
        //remove it
        setBufferFlag(false);
        return buffer;
    }
    //otherwise read token
    else{

        char c = getchar();
        //cout << "  c= " << c << " ";
        
        switch(c){
        
        //char is a kind of digit
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case '.':
            {
                //put back char and read in as double
                cin.putback(c);
                double val;
                cin >> val;
                return Token(digit, val);
            }

        //char is an operator or terminator, let it represent itself
        case '+': case '-': case '*': case '/': case '!': 
        case '(': case ')': case '[': case ']': case ';':
        case eval: case quit:
            return Token(c);

        default:
            cin.putback(c);
            cout << "Token_Stream::get() -- bad character, case does not exist for: " << c << "\n";
            exit(-1);
        }
    }

}

void Token_stream::putback(Token t){
    
    //is buffer full already?
    if (isFull()){
        cerr << "Token_stream::putback(Token t): buffer full, exiting program\n";
        exit(-1);
    }

    //update buffer
    setBuffer(t);

}

void Token_stream::ignore(char c){

    if (isFull() && c == buffer.getKind()){
        setBufferFlag(false);
        return;
    }

    setBufferFlag(false);

    char ch;
    while(cin >> ch){
        if (ch == c){
            return;
        }
    }

}

//Calculator class implementation
Calculator::Calculator(){/*...*/}

double Calculator::term(){

    t = get();
    switch(t.getKind()){
    
    case '[':
        {
            double num = stmt();
            t = get();
            if (t.getKind() != ']'){
                cerr << "error: bad syntax - missing closing ']'\n";
                exit(-1);
            }
            return num;
        }

    case '(':
        {
            double num = stmt();
            t = get();
            if (t.getKind() != ')'){
                cerr << "error: bad syntax - missing closing ')'\n";
                exit(-1);
            }
            return num; 
        }


    case digit:
        return t.getValue();

    case quit:
        cout << prompt << "goodbye!\n";
        exit(0);

    case negative:
        return -term();

    case positive:
        return term();

    default:
        cerr << "error: bad syntax, digit or operator expected\n";
    }

}

double Calculator::expr(){

    double result = term();
    t = get();
    while(true){
    
        switch(t.getKind()){
        
        case '*':
            result *= term();
            t = get();
            break;

        case '/':
            {
                //read ahead and look for 0 in divisor
                double num = term();
                if (num == 0) {
                    cerr << "error: bad syntax - division by 0\n";
                }
                result /= num;
                t = get();
                break;
            }

        default:
            putback(t);
            return result;
        }
    
    }

}

double Calculator::stmt(){

    double result = expr();
    t = get();
    while(true){
    
        switch(t.getKind()){
    
        case '+':
            result += expr();
            t = get();
            break;

        case '-':
            result -= expr();
            t = get();
            break;

        default:
            putback(t);
            return result;
    
        }
    
    }

}
