#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <ctime>
#include <string>
using namespace std;

class TimeUtils {
    public:
        static string getCurrentTime() {
            time_t now = time(nullptr);
            char* dt = ctime(&now);
            string s(dt);
            if(!s.empty() && s.back() == '\n') {    
                s.pop_back();
            }
            return s;
        }
};

#endif