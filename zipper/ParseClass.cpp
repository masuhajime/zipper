#include "ParseClass.h"
#include <vector>
#include <unordered_map>
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
    
    bool ParseClass::getObjectId(const std::string objectId, const ccHttpRequestCallback &callback) {
        auto url = string("https://api.parse.com/1/classes/") + class_name + "/" + objectId;
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
    
    zipper::ParseObject ParseClass::getParseObjectFromHttpResponse(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response) {
        if (!response->isSucceed()) {
            throw 1;// ここひどいのでなんとかする
        }
        std::vector<char> *buffer = response->getResponseData();
        std::string json_body = std::string(buffer->begin(), buffer->end());
        
        //CCLOG("%s", json_body.c_str());
        
        picojson::value v;
        std::string err = picojson::parse(v, json_body);
        if (!err.empty()) {
            //std:cerr << err << std::endl;
            throw 1;// ここひどいのでなんとかする
        }
        
        // TODO: 404 not found の時にエラーを出す
        // 200: {"createdAt":"2015-01-03T12:10:01.320Z","name":"user_name","objectId":"G4zrJcNRs8","score":100,"updatedAt":"2015-01-08T09:50:36.141Z"}
        // 404: {"code":101,"error":"object not found for get"}
        
        picojson::object& obj = v.get<picojson::object>();
        zipper::ParseObject parse_object;
        for (picojson::object::iterator it=obj.begin(); it != obj.end(); it++) {
            if ((*it).second.is<double>()) {
                parse_object.set((*it).first, cocos2d::Value((*it).second.get<double>()));
            } else if ((*it).second.is<std::string>()) {
                parse_object.set((*it).first, cocos2d::Value((*it).second.get<std::string>()));
            } else if ((*it).second.is<bool>()) {
                parse_object.set((*it).first, cocos2d::Value((*it).second.get<bool>()));
            }
        }
        
        return parse_object;
    }
    
    std::vector<ParseObject> ParseClass::getParseObjectsFromHttpResponse(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response) {
        
        if (!response->isSucceed()) {
            throw 1;// ここひどいのでなんとかする
        }
        std::vector<char> *buffer = response->getResponseData();
        std::string json_body = std::string(buffer->begin(), buffer->end());
        
        //CCLOG("%s", json_body.c_str());
        
        picojson::value v;
        std::string err = picojson::parse(v, json_body);
        if (!err.empty()) {
            //std:cerr << err << std::endl;
            throw 1;// ここひどいのでなんとかする
        }
        
        // TODO: 404 not found の時にエラーを出す
        // 200: {"createdAt":"2015-01-03T12:10:01.320Z","name":"user_name","objectId":"G4zrJcNRs8","score":100,"updatedAt":"2015-01-08T09:50:36.141Z"}
        // 404: {"code":101,"error":"object not found for get"}
        
        std::vector<zipper::ParseObject> parse_objects;
        picojson::object& objects = v.get<picojson::object>();
        picojson::array& array = objects["results"].get<picojson::array>();
        
        for (picojson::array::iterator it_result = array.begin(); it_result != array.end(); it_result++)
        {
            zipper::ParseObject parse_object;
            picojson::object& object = it_result->get<picojson::object>();
            for (picojson::object::iterator it = object.begin(); it != object.end(); it++) {
                if ((*it).second.is<double>()) {
                    parse_object.set((*it).first, cocos2d::Value((*it).second.get<double>()));
                } else if ((*it).second.is<std::string>()) {
                    parse_object.set((*it).first, cocos2d::Value((*it).second.get<std::string>()));
                } else if ((*it).second.is<bool>()) {
                    parse_object.set((*it).first, cocos2d::Value((*it).second.get<bool>()));
                }
            }
            parse_objects.push_back(parse_object);
        }
        
        return parse_objects;
    }
    
    bool ParseClass::postData(const std::string objectId, const char* buffer) {
        auto url = string("https://api.parse.com/1/classes/") + class_name;
        auto request = new HttpRequest();
        request->setUrl(url.c_str());
        request->setHeaders(getParseHeader(true));
        request->setRequestType(HttpRequest::Type::POST);
        HttpClient::getInstance()->send(request);
        //httpRequest->setResponseCallback();
        // TODO: これを外から利用する
        // picojson::object json
        // picojson::value val(json);
        // const char* buffer = val.serialize().c_str();
        request->setRequestData(buffer, strlen(buffer));
        
        return true;
    }
    
} // namespace zipper