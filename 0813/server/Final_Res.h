#ifndef FINAL_RES_H_
#define FINAL_RES_H_

#include "TextQuery.h"
#include "cache.h"
#include <echo/TimerThread.h>
#include <stdint.h>

class Final_Res
{
    public:
        typedef TextQuery::LineNo LineNo;

        Final_Res(){};
        Final_Res(const std::string &filename);
        std::string runLCS(const std::string &word);

        void write_cache();

        std::string find();

        int LCS(const std::string &a, const std::string &b);
        int Min(int a, int b, int c);
        void parseUTF8String(const std::string &s, std::vector<uint32_t> &vec);
        int edit_distance_uint_32(const std::vector<uint32_t> &w1,
                const std::vector<uint32_t> &w2);
        int getLenOfUTF8(unsigned char c);

    private:
        TextQuery query_;
        TimerThread timer;

        std::map<std::string, std::pair<int, int> > res_;
        std::map<std::string, std::set<LineNo> > wordMap_;
        Cache cache_;
};

#endif  /*FINAL_RES_H_*/
