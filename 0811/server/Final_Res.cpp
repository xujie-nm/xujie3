#include "Final_Res.h"
#include <iostream>
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

int Final_Res::LCS(const string &tword, const string &word_)
{
    int n = word_.size();
    int m = tword.size();
    int num[n + 1][m + 1];
    
    for (int i = 0; i <= n; i++) 
    {
        num[i][0] = 100;    
    }

    for (int j = 0; j <= m; j++) 
    {
        num[0][j] = 100;    
    }
    num[0][0] = 0;

    for (int i = 1; i <= n; i++) 
    {
        for (int j = 1; j <= m; j++) 
        {
            if(word_[i - 1] == tword[j - 1]) 
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


    return num[n][m];
}

int Final_Res::Min(int a1, int a2, int a3)
{
    if(a1 < a2)
    {
        if(a1 < a3)
            return a1;
        else
            return a3;
    }
    else
    {
        if(a2 < a3)
            return a2;
        else
            return a3;
    }
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
                    res_.insert(make_pair(it->first, make_pair(it->second.size(), ll)));
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
