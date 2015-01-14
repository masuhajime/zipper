#ifndef ZIPPER_PARSECLASS_H
#define ZIPPER_PARSECLASS_H

#include <string>
#include <vector>
#include <map>
#include "cocos2d.h"
#include "picojson.h"

namespace zipper
{
    /**
     * 一見、Classという命名は抽象的すぎるのでは？と思うかもしれないが、ParseではClassというデータ構造のようだ
     */
    class ParseClass
    {
    private:
        std::string application_id;
        std::string rest_api_key;
        std::string class_name;
    public:
        ParseClass(const std::string class_name, const std::string application_id, const std::string rest_api_key);
        std::vector<std::map<std::string, std::string>> postData(const std::string objectId, const char* buffer);
        bool getScoreObjectId(const std::string objectId);
    private:
        std::vector<std::string> getParseHeader(bool withdata = true);
    };
    

} // namespace zipper

#endif /* ZIPPER_PARSECLASS_H */
