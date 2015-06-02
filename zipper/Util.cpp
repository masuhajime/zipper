#include "zipper/Util.h"

#include "picojson.h"

namespace zipper
{
    bool Util::isStatus20X(long statusCode)
    {
        return 2 == (statusCode / 100);
    }
    
    zipper::ParseObject Util::parseToParseObject(const std::string &buffer)
    {
        
    }
    
    zipper::ParseObjects Util::parseToParseObjects(const std::string &buffer)
    {
        picojson::value v;
        if (parseJson(v, buffer)) {
            
        }
    }
    
    bool Util::parseJson(picojson::value &parsed, const std::string &s)
    {
        std::string err = picojson::parse(parsed, s);
        return !err.empty();
    }
}
