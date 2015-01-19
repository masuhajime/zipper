#ifndef ZIPPER_PARSECLASS_H
#define ZIPPER_PARSECLASS_H

#include <string>
#include <vector>
#include <unordered_map>
#include "cocos2d.h"
#include "picojson.h"
#include "network/HttpClient.h"

namespace zipper
{
    /**
     * 一見、Classという命名は抽象的すぎるのでは？と思うかもしれないが、Parse.comではClassというデータ構造のようだ
     */
    class ParseClass
    {
    private:
        std::string application_id;
        std::string rest_api_key;
        std::string class_name;
    public:
        // std::vector<std::unordered_map<std::string, cocos2d::Value>>
        ParseClass(const std::string class_name, const std::string application_id, const std::string rest_api_key);
        bool postData(const std::string objectId, const char* buffer);
        bool getScoreObjectId(const std::string objectId, const cocos2d::network::ccHttpRequestCallback &callback);
        
        // cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse*
        static std::unordered_map<std::string, cocos2d::Value> getObjectFromHttpResponse(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
    private:
        std::vector<std::string> getParseHeader(bool withdata = true);
    };
    

} // namespace zipper

#endif /* ZIPPER_PARSECLASS_H */
