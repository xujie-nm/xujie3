#include <iostream>
#include <string>
#include <vector>
#include "Final_Res.h"
using namespace std;

int main(int argc, const char *argv[])
{
    Final_Res final("in.txt") ;

    string word;
    
    cout << "please input a word:" << endl;
    
    while(cin >> word)
    {
        string res = final.runLCS(word);
        cout << res << endl;
        cout << "please input a word:" << endl;
    }
    return 0;
}
