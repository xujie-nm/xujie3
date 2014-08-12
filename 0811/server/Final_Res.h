#ifndef FINAL_RES_H_
#define FINAL_RES_H_

#include "TextQuery.h"
#include "cache.h"
#include <echo/TimerThread.h>

class Final_Res
{
    public:
        typedef TextQuery::LineNo LineNo;

        Final_Res(){};
        Final_Res(const std::string &filename);
        std::string runLCS(const std::string &word);

        void write_cache();

        std::string find();

        int LCS(const std::string &tword, const std::string &word_);
        int Min(int a1, int a2, int a3);

    private:
        TextQuery query_;
        TimerThread timer;

        std::map<std::string, std::pair<int, int> > res_;
        std::map<std::string, std::set<LineNo> > wordMap_;
        Cache cache_;
};

#endif  /*FINAL_RES_H_*/
