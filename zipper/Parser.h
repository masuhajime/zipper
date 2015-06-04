#pragma once

#include "zipper/ParseClass.h"

namespace zipper
{
    class Parser
    {
    public:
        static zipper::ParseObject parseToParseObject(const std::string &buffer);
        static std::vector<ParseObject> parseToParseObjects(const std::string &buffer);
        
        static bool parseJson(picojson::value &out, const std::string &s);
        static void parseObject(ParseObject &parse_object, picojson::object &object);
    };
    
    class invalid_format_error : public std::runtime_error
    {
    public:
        invalid_format_error() : std::runtime_error(""){}
    };
    
    class invalid_object_format_error : public invalid_format_error
    {
    public:
        invalid_object_format_error() : invalid_format_error(){}
    };
    
    class invalid_json_format_error : public invalid_format_error
    {
    public:
        invalid_json_format_error() : invalid_format_error(){}
    };
    
} // namespace zipper
