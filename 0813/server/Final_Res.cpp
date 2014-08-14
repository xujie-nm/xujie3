#include "Final_Res.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <echo/Exception.h>
using namespace std;

Final_Res::Final_Res(const string &filename)
    :query_(filename)
{
    timer.setTimer(3, 3);
    timer.setTimerCallback(bind(&Final_Res::write_cache, this));
    timer.startTimerThread();
    cache_.read_file("cache.txt");
}

int Final_Res::getLenOfUTF8(unsigned char c)
{
    int cnt = 0;
    while(c & (1 << (7 - cnt)))
        ++cnt;
    return cnt;
}

void Final_Res::parseUTF8String(const string &s, vector<uint32_t> &vec)
{
    vec.clear();
    for(string::size_type ix = 0; ix != s.size(); ++ix)
    {
        int len = getLenOfUTF8(s[ix]);
        uint32_t t = (unsigned char)s[ix];
        if(len > 1)
        {
            --len;

            while(len--)
            {
                t = (t << 8) + (unsigned char)s[++ix];
            }
        }
        vec.push_back(t);
    }
}

int Final_Res::edit_distance_uint_32(const vector<uint32_t> &w1,
        const vector<uint32_t> &w2)
{
    
    int n = w1.size();
    int m = w2.size();
    int num[n + 1][m + 1];
    memset(num, 0x00, (n + 1)*(m + 1)*sizeof(int));
    for (int i = 0; i <= n; i++) 
    {
        num[i][0] = i;    
    }

    for (int j = 0; j <= m; j++) 
    {
        num[0][j] = j;    
    }

    for (int i = 1; i <= n; i++) 
    {
        for (int j = 1; j <= m; j++) 
        {
            if(w1[i - 1] == w2[j - 1]) 
            {
                num[i][j] = num[i - 1][j - 1];
            }
            else
            {
                int a1 = num[i][j - 1];
                int a2 = num[i - 1][j];
                int a3 = num[i - 1][j - 1];
                num[i][j] = Min(a1, a2, a3) + 1;
            }
        }    
    }
/*
    for (int i = 0; i <= n; i++) 
    {
        for (int j = 0; j <= m; j++) 
        {
            cout << num[i][j] << " ";    
        }
        cout << endl;
    }
*/

    return num[n][m];
}

int Final_Res::LCS(const string &a, const string &b)
{
    vector<uint32_t> w1, w2;
    parseUTF8String(a, w1);
    parseUTF8String(b, w2);
    return edit_distance_uint_32(w1, w2);
}

int Final_Res::Min(int a, int b, int c)
{
    int ret = (a < b) ? a : b;
    ret = (ret < c) ? ret : c;
}

string Final_Res::runLCS(const string &word)
{
    res_.clear();
    cout << word << endl;
    string ff = cache_.read_cache(word);

    if( ff.size() != 0)
    {
        return ff;
    }
    else
    {
        wordMap_ = query_.get_word_map();

        map<string, set<LineNo> >::iterator ix;
        ix = wordMap_.find(word);
    
        if(ix == wordMap_.end())
        {
            for(map<string, set<LineNo> >::iterator it = wordMap_.begin(); it != wordMap_.end(); ++it)
            {
                if(int ll = LCS(it->first, word) < 3) 
                {
                 //   cout << word << "  " << it->first << "  " << ll << endl;
                    res_.insert(make_pair(it->first, make_pair(it->second.size(), ll)));
                }
            }

            if(res_.empty())
                return string("search failed");
        
            string final =find();
            
            string test = final;
            cout << test << endl;
            //test
            //final = query_.runQuery(final);
            //test
            //final += string("\n") + string("the search word: ") + test + string("\n");
            final +=string("\n");
            cache_.insert_new(word, final);
            return final;
        }
        else
        {
            //test
            //string res = query_.runQuery(word);
            //test
            string word1 = word + "\n";
            cache_.insert_new(word, word1);
            return  word  + "\n";
        }
    }
}

string Final_Res::find()
{
   string final; 
   int ll = 3;
        for(map<string, pair<int, int > >::iterator it = res_.begin(); it != res_.end(); ++it)
        {
            if(it->second.second < ll)
            {
                ll = it->second.second;
            }
        }

   int freq = 0;
        for(map<string, pair<int, int> >::iterator it = res_.begin(); it != res_.end(); ++it)
        {
            if(it->second.second == ll && it->second.first > freq ) 
            {
                freq = it->second.first;
                final += it->first + "-";
            }
        }

        return final;
}


void Final_Res::write_cache()
{
    cache_.write_file("cache.txt");
}
