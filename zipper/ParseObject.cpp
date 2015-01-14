#include "ParseClass.h"
#include <vector>
#include <iostream>
#include "network/HttpClient.h"

using namespace std;

USING_NS_CC;
using namespace cocos2d::network;

namespace zipper
{
    
    ParseClass::ParseClass(const std::string class_name, const std::string application_id, const std::string rest_api_key)
    :class_name(class_name), application_id(application_id), rest_api_key(rest_api_key) {
    }
    
    vector<std::string> ParseClass::getParseHeader(bool withdata) {
        vector<string> h;
        auto header_application_id = string("X-Parse-Application-Id: ") + application_id;
        auto header_rest_api_key   = string("X-Parse-REST-API-Key: ") + rest_api_key;
        h.push_back(header_application_id.c_str());
        h.push_back(header_rest_api_key.c_str());
        if (withdata) {
            h.push_back("Content-Type: application/json");
        }
        return h;
    }
    
    bool ParseClass::getScoreObjectId(const std::string objectId) {
        
        // 200: {"createdAt":"2015-01-03T12:10:01.320Z","name":"user_name","objectId":"G4zrJcNRs8","score":100,"updatedAt":"2015-01-08T09:50:36.141Z"}
        // 404: {"code":101,"error":"object not found for get"}
        return true;
    }
    
    bool ParseClass::postData(const std::string objectId, const char* buffer) {
        auto r = new HttpRequest();
        auto url = string("https://api.parse.com/1/classes/") + class_name;
        r->setUrl(url.c_str());
        r->setHeaders(getParseHeader(true));
        r->setRequestType(HttpRequest::Type::POST);
        // TODO: これを外から利用する
        // picojson::object json
        // picojson::value val(json);
        // const char* buffer = val.serialize().c_str();
        r->setRequestData(buffer, strlen(buffer));
        
        return true;
    }
    
} // namespace zipper