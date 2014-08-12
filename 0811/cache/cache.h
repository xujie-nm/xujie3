#ifndef CACHE_H_
#define CACHE_H_

#include <map>
#include <list>
#include <fstream>

class Cache
{
    public:
        void insert_new(const std::string &key, const std::string &value);
        void delete_old();
        void write_file(const std::string &filename);
        void read_file(const std::string &filename);

        std::string read_cache(const std::string &key);

    private:
        std::map<std::string, std::pair<std::string, std::list<std::string>::iterator> > cache_;
        std::list<std::string> key_;
};

#endif  /*CACHE_H_*/
