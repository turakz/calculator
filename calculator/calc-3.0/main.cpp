/*
   scaffolding for program taken from Bjarne Stroustrup's Programming: Practices and Principles Using C++
   -modifications, consolidation, and added functionality found within implemented by zachary turak
*/

#include "calculator.h"

int main(){
    
    cout << "simple calculator 3.0 (c) 2017 by zachary turak\n";
    cout << "operations supported: + - / * () []\n";
    cout << "enter an expression to evaluate, or $ (to quit)\n";
    
    Calculator c;
    double num = 0;
    cout << prompt;
    while(cin){
    
        c.t = c.get();

        if (c.t.getKind() == eval){
            cout << result << num << "\n";
            cout << prompt;
            c.t = c.get();
        }

        c.putback(c.t);
        num = c.stmt();

    }
    return 0;
}
