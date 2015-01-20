#include "ParseObject.h"
#include "network/HttpClient.h"
#include <unordered_map>

using namespace std;

USING_NS_CC;
using namespace cocos2d::network;

namespace zipper
{
    bool ParseObject::has(const std::string& key) {
        return data.find(key) != data.end();
    }
    
    const cocos2d::Value* ParseObject::get(const std::string& key) {
        return &(data.find(key)->second);
    }
    
    const double ParseObject::asDouble(const std::string& key) {
        return data.find(key)->second.asDouble();
    }
    
    const std::string ParseObject::asString(const std::string& key) {
        return data.find(key)->second.asString();
    }
    
    const bool ParseObject::asBool(const std::string& key) {
        return data.find(key)->second.asBool();
    }
    
    void ParseObject::set(const std::string& key, cocos2d::Value value) {
        data.insert(unordered_map<string, cocos2d::Value>::value_type(key, value));
    }
    
} // namespace zipper
