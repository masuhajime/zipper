#include "Parser.h"


namespace zipper
{
    zipper::ParseObject Parser::parseToParseObject(const std::string &buffer)
    {
        picojson::value v;
        if (parseJson(v, buffer)) {
            throw new invalid_json_format_error();
        }
        
        zipper::ParseObject parseObject;
        picojson::object& picoObject = v.get<picojson::object>();
        Parser::parseObject(parseObject, picoObject);
        return parseObject;
    }
    
    zipper::ParseObjects Parser::parseToParseObjects(const std::string &buffer)
    {
        picojson::value v;
        if (parseJson(v, buffer)) {
            throw new invalid_json_format_error();
        }
        
        zipper::ParseObjects parseObjects;
        picojson::object& objects = v.get<picojson::object>();
        picojson::array& array = objects["results"].get<picojson::array>();
        
        for (picojson::array::iterator it_result = array.begin(); it_result != array.end(); it_result++)
        {
            zipper::ParseObject parse_object;
            picojson::object& object = it_result->get<picojson::object>();
            Parser::parseObject(parse_object, object);
            parseObjects.push_back(parse_object);
        }
        return parseObjects;
    }
    
    void Parser::parseObject(ParseObject &parse_object, picojson::object &object)
    {
        for (picojson::object::iterator it=object.begin(); it != object.end(); it++) {
            if ((*it).second.is<double>()) {
                parse_object.set((*it).first, cocos2d::Value((*it).second.get<double>()));
            } else if ((*it).second.is<std::string>()) {
                parse_object.set((*it).first, cocos2d::Value((*it).second.get<std::string>()));
            } else if ((*it).second.is<bool>()) {
                parse_object.set((*it).first, cocos2d::Value((*it).second.get<bool>()));
            }
        }
    }

    bool Parser::parseJson(picojson::value &out, const std::string &s)
    {
        std::string err = picojson::parse(out, s);
        return !err.empty();
    }
}