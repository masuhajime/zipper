#ifndef ZIPPER_PARSECLASS_H
#define ZIPPER_PARSECLASS_H

#include <string>
#include <vector>
#include <unordered_map>
#include "cocos2d.h"
#include "picojson.h"
#include "network/HttpClient.h"

#include "ParseObject.h"

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
        
        static void parseJson(picojson::value &out, const std::string &s);
        static void parseObject(ParseObject &parse_object, picojson::object &object);
    public:
        ParseClass(const std::string class_name, const std::string application_id, const std::string rest_api_key);
        bool update(const std::string objectId, const char* buffer, const cocos2d::network::ccHttpRequestCallback &callback);
        bool create(const char* buffer, const cocos2d::network::ccHttpRequestCallback &callback);
        bool getObjectId(const std::string objectId, const cocos2d::network::ccHttpRequestCallback &callback);
        bool getRanking(std::string sort_by, int limit, const cocos2d::network::ccHttpRequestCallback &callback);
        
        // callback
        static ParseObject getParseObjectFromHttpResponse(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
        static std::vector<ParseObject> getParseObjectsFromHttpResponse(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
    private:
        std::vector<std::string> getParseHeader(bool withdata = true);
    };
    
    class notfound_error : public std::runtime_error
    {
    public:
        notfound_error() : std::runtime_error(""){}
    };
    

} // namespace zipper

#endif /* ZIPPER_PARSECLASS_H */
