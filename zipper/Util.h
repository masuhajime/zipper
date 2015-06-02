#pragma once

#include "zipper/ParseClass.h"

namespace zipper
{
    class Util
    {
    public:
        static bool isStatus20X(long statusCode);
        static zipper::ParseObject parseToParseObject(const std::string &buffer);
        static zipper::ParseObjects parseToParseObjects(const std::string &buffer);
        
        static bool parseJson(picojson::value &out, const std::string &s);
    };
    
} // namespace zipper

