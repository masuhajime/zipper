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
    
    cocos2d::Value* ParseObject::get(const std::string& key) {
        return &(data.find(key)->second);
    }
    
    void ParseObject::set(const std::string& key, cocos2d::Value value) {
        data.insert(unordered_map<string, Value>::value_type(key, value));
    }
    
} // namespace zipper
