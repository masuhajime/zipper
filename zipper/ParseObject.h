#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "cocos2d.h"
#include "picojson.h"

namespace zipper
{
    class ParseObject
    {
    private:
        std::unordered_map<std::string, cocos2d::Value> data;
    public:
        bool has(const std::string& key);
        const cocos2d::Value* get(const std::string& key);
        const int asInt(const std::string& key);
        const double asDouble(const std::string& key);
        const std::string asString(const std::string& key);
        const bool asBool(const std::string& key);
        void set(const std::string& key, cocos2d::Value value);
    };

} // namespace zipper


