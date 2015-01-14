#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "zipper/Ranking.h"
#include <jni.h>
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"

namespace zipper {

namespace helper {
namespace ranking {

    const char* const CLASS_NAME = "zipper/Ranking";

    
    void callStaticVoidMethodWithString(const char* name, const char* c_string)
    {
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, name, "(Ljava/lang/String;)V")) {
            jstring j_string = t.env->NewStringUTF(c_string);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, j_string);
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(j_string);
        }
    }
    
    
    void callStaticVoidMethodWithStringAndString(const char* name, const char* c_string, const char* c_string2)
    {
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, name, "(Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring j_string = t.env->NewStringUTF(c_string);
            jstring j_string2 = t.env->NewStringUTF(c_string2);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, j_string, j_string2);
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(j_string);
            t.env->DeleteLocalRef(j_string2);
        }
    }
    
} /* helper */
} /* ranking */
    
    /*
    void Ranking::tweet(const char* tweet) {
        amoamo::helper::twitter::callStaticVoidMethodWithString("tweet", tweet);
    }
     */

}/* zipper */

#endif
