#include <iostream>
#include <string>
#include <vector>
#include "cache.h"
using namespace std;

int main(int argc, const char *argv[])
{
    //string key;
    //string value;
    Cache ca;
    
    //cout << "please input key&value : " << endl;
    //while(cin >> key >> value)
    //{
    //    cout << "please input key&value : " << endl;
    //ca.insert_new(key, value);
    
    //}
    /*
    ca.insert_new("1", "2");
    ca.insert_new("2", "3");
    ca.insert_new("3", "4");
    ca.insert_new("4", "5");
    ca.insert_new("5", "6");
    ca.insert_new("6", "7");
    ca.insert_new("7", "8");
    ca.insert_new("8", "9");
    ca.insert_new("9", "0");
    ca.insert_new("0", "1");
    ca.insert_new("11", "1");
    ca.insert_new("22", "2");
    ca.insert_new("33", "3");
    ca.insert_new("44", "4");
    ca.insert_new("55", "5");
    */
    //}
    //
//    cout << "please input a filename: " << endl;
//    string filename;
//    cin >> filename;
    ca.read_file("cache.txt");
    ca.write_file("cache.txt");

    //string result;
    //cout << "please input a key:" << endl;
    //while(cin >> result)
    //{
    //    result = ca.read_cache(result);
    //    cout << result << endl;
    //    cout << "please input a key:" << endl;
    //}
    return 0;
}
