#include "zipper/Util.h"

#include "picojson.h"

#include <iostream>
#include <sstream>
#include <ctime>
#include <iostream>

#include "cocos2d.h"
USING_NS_CC;

namespace zipper
{
    bool Util::isStatus20X(long statusCode)
    {
        return 2 == (statusCode / 100);
    }
    
    std::string Util::urlencode(const std::string& string)
    {
        std::ostringstream os;
        for (int i = 0; i < string.size(); i++) {
            char c = string[i];
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
                (c >= '0' && c <= '9') ||
                c == '-' || c == '_' || c == '.' || c == '~') {
                os << c;
            } else {
                char s[4];
                snprintf(s, sizeof(s), "%%%02x", c & 0xff);
                os << s;
            }
        }
        return os.str();
    }
    
    std::string Util::toUTC(long timestamp)
    {
        char buf[80];
        strftime(buf, sizeof buf, "%FT%TZ", gmtime(&timestamp));
        //strftime(buf, sizeof buf, "Now it's %I:%M%p", gmtime(&now));
        std::string str(buf);
        return str;
    }
}
