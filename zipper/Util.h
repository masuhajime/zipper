#pragma once

#include "zipper/ParseClass.h"

namespace zipper
{
    class Util
    {
    public:
        static bool isStatus20X(long statusCode);
        static std::string toUTC(long timestamp);
        static std::string urlencode(const std::string& string);
    };
    
} // namespace zipper

