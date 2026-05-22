
#ifndef __utf8_hpp
#define __utf8_hpp

#include <string_view>

class utf8
{
    public:
        static bool check_string (std::string_view str, long len = -1);
};

#endif /* __utf8_hpp */