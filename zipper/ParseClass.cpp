#include "ParseClass.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include "network/HttpClient.h"
#include "zipper/Util.h"

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
        auto header_application_id = string("X-Parse-Application-Id:") + application_id;
        auto header_rest_api_key   = string("X-Parse-REST-API-Key:") + rest_api_key;
        h.push_back(header_application_id.c_str());
        h.push_back(header_rest_api_key.c_str());
        if (withdata) {
            h.push_back("Content-Type:application/json");
        }
        return h;
    }
    
    bool ParseClass::getObjectId(const std::string objectId, const ccHttpRequestCallback &callback) {
        auto url = string("https://api.parse.com/1/classes/") + class_name + "/" + objectId;
        //auto url = string("http://httpbin.org/delay/15");
        auto request = new HttpRequest();
        request->setUrl(url.c_str());
        request->setHeaders(getParseHeader(false));
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback(callback);
        auto client = HttpClient::getInstance();
        client->enableCookies("");
        client->setTimeoutForConnect(10);
        client->setTimeoutForRead(10);
        client->send(request);
        request->release();
        return true;
    }
    
    bool ParseClass::getRanking(std::string sort_by, int limit, const cocos2d::network::ccHttpRequestCallback &callback) {
        auto url = string("https://api.parse.com/1/classes/MarutaRecord?limit=") + std::to_string(limit) + "&order=" + sort_by;
        auto request = new HttpRequest();
        request->setUrl(url.c_str());
        request->setHeaders(getParseHeader(false));
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback(callback);
        auto client = HttpClient::getInstance();
        client->enableCookies(NULL);
        client->send(request);
        return true;
    }
    
    void ParseClass::parseJson(picojson::value &out, const std::string &s)
    {
        std::string err = picojson::parse(out, s);
        if (!err.empty()) {
            throw 1;
            // TODO:
            // throw new unexpected_response;
        }
    }
    
    void ParseClass::parseObject(ParseObject &parse_object, picojson::object &object)
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
    
    zipper::ParseObject ParseClass::getParseObjectFromHttpResponse(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response) {
        if (404 == response->getResponseCode()) {
            throw notfound_error();
        }
        if (!response->isSucceed()) {
            throw 1;// ここひどいのでなんとかする
        }
        std::vector<char> *buffer = response->getResponseData();
        std::string json_body = std::string(buffer->begin(), buffer->end());
        
        //CCLOG("%d:%s", (int)response->getResponseCode(), json_body.c_str());
        
        return zipper::Parser::parseToParseObject(json_body);
    }
    
    zipper::ParseObjects ParseClass::getParseObjectsFromHttpResponse(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response) {
        if (404 == response->getResponseCode()) {
            throw notfound_error();
        }
        if (!response->isSucceed()) {
            throw 1;// ここひどいのでなんとかする
        }
        std::vector<char> *buffer = response->getResponseData();
        std::string json_body = std::string(buffer->begin(), buffer->end());
        
        return zipper::Parser::parseToParseObjects(json_body);
    }
    
    /**
     * return string
     * {"createdAt":"2015-03-22T06:03:08.905Z","objectId":"8vAojmyYom"}
     */
    bool ParseClass::create(const char* buffer, const ccHttpRequestCallback &callback) {
        auto url = string("https://api.parse.com/1/classes/") + class_name;
        auto request = new HttpRequest();
        request->setUrl(url.c_str());
        request->setHeaders(getParseHeader(false));
        request->setRequestType(HttpRequest::Type::POST);
        request->setRequestData(buffer, strlen(buffer));
        request->setResponseCallback(callback);
        auto client = HttpClient::getInstance();
        client->enableCookies("");
        client->setTimeoutForConnect(10);
        client->setTimeoutForRead(10);
        client->send(request);
        request->release();
        return true;
    }
    
    /**
     * 
     */
    bool ParseClass::update(const std::string objectId, const char* buffer, const cocos2d::network::ccHttpRequestCallback &callback) {
        auto url = string("https://api.parse.com/1/classes/") + class_name + "/" + objectId;
        auto request = new HttpRequest();
        request->setUrl(url.c_str());
        request->setHeaders(getParseHeader(true));
        request->setRequestType(HttpRequest::Type::PUT);
        request->setResponseCallback(callback);
        request->setRequestData(buffer, strlen(buffer));
        
        auto client = HttpClient::getInstance();
        client->enableCookies("");
        client->setTimeoutForConnect(10);
        client->setTimeoutForRead(10);
        client->send(request);
        request->release();
        
        return true;
    }
    
    void ParseClass::getObjects(const std::string &where, const std::string &orderby, const std::string &limit,
                                const std::function<void(zipper::ParseObjects)> callbackSucceed,
                                const std::function<void(zipper::ParseClass::ERROR_REASON reason)> callbackFailed)
    {
        std::string requestData = "?";
        requestData += "where=" + Util::urlencode(where);
        requestData += "&order=" + orderby;
        requestData += "&limit=" + limit;
        
        auto url = string("https://api.parse.com/1/classes/") + class_name + requestData;
        auto request = new HttpRequest();
        request->setUrl(url.c_str());
        request->setHeaders(getParseHeader(true));
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback([=](HttpClient* client, HttpResponse* response){
            if (!zipper::Util::isStatus20X(response->getResponseCode())) {
                callbackFailed(ERROR_REASON::UNEXPECTED_RESPONSE);
                return;
            }
            std::vector<char> *buffer = response->getResponseData();
            auto jsonBody = std::string(buffer->begin(), buffer->end());
            auto parseObjects = zipper::Parser::parseToParseObjects(jsonBody);
            callbackSucceed(parseObjects);
        });
        
        // TODO: これurlencodeしてくれんの？
        request->setRequestData(requestData.c_str(), strlen(requestData.c_str()));
        
        auto client = HttpClient::getInstance();
        client->enableCookies("");
        client->setTimeoutForConnect(10);
        client->setTimeoutForRead(10);
        client->send(request);
        request->release();
    }
    
} // namespace zipper