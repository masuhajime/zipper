#ifndef ZIPPER_PARSECLASS_H
#define ZIPPER_PARSECLASS_H

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
        cocos2d::Value* get(const std::string& key);
        void set(const std::string& key, cocos2d::Value value);
    };

} // namespace zipper

#endif /* ZIPPER_PARSECLASS_H */
