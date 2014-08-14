#include "cache.h"
#include <unistd.h>
#include <stdlib.h>

using namespace std;

void Cache::insert_new(const string &key, const string &value)
{
    if(cache_.size() == 10)
        delete_old();
    if(cache_.find(key) != cache_.end())
    {
        for(list<string>::iterator it = key_.begin(); it != key_.end(); ++it)
        {
            if(*it == key)
            {
                key_.erase(it);
                key_.push_back(key);
                break;
            }
        }
    }
    else
    {
        key_.push_back(key);
        list<string>::iterator it = key_.end();
        --it;
        cache_.insert(make_pair(key, make_pair(value, it)));
    }
}

void Cache::delete_old()
{
    list<string>::iterator itkey = key_.begin();
    string key = *itkey;
    key_.erase(itkey);

    for(map<string, pair<string, list<string>::iterator> >::iterator it = cache_.begin(); 
            it != cache_.end(); ++it)
    {
        if(it->first == key)
        {
            cache_.erase(it);
            break;
        }
    }
}

void Cache::write_file(const string &filename)
{
    ofstream fos;
    fos.open(filename.c_str());

    if(!fos)
        exit(EXIT_FAILURE);

    for(list<string>::iterator it = key_.begin(); 
            it != key_.end(); ++it)
    {
        map<string, pair<string, list<string>::iterator> >::iterator its;
        its = cache_.find(*it);
        fos << its->first << " " << its->second.first << endl;
    }
   
    //fclose(fos);
}

void Cache::read_file(const string &filename)
{
    ifstream fis;
    fis.open(filename.c_str());

    if(!fis)
        exit(EXIT_FAILURE);

    string key;
    string value;

    while(fis >> key >> value)
    {
        insert_new(key, value);
    }
    //fclose(fin);
}

string Cache::read_cache(const string &key)
{
    map<string, pair<string, list<string>::iterator> >::iterator it = cache_.find(key) ;
    if(it == cache_.end())
        return string("");
    else
        return it->first + " " + it->second.first;
}
