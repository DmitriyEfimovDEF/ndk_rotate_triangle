#include <jni.h>
#include <android/log.h>
#include "Triangle.hpp"

static Triangle triangle;
jclass callbacksClass;
jobject callbacksInstance;

#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, "~~~~~", __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))


extern "C" JNIEXPORT void JNICALL
Java_com_example_triangle_Triangle_draw(
        JNIEnv *env,
        jobject p_this,
        jfloat width,
        jfloat height,
        jfloat scale,
        jfloat angle) {

    triangle.draw(width, height, scale, angle);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_triangle_Triangle_onRadSet(
        JNIEnv *pEnv,
        jobject pThis,
        jobject obj) {

    callbacksInstance = pEnv->NewGlobalRef(obj);
    jclass objClass = pEnv->GetObjectClass(obj);
    if (objClass) {
        callbacksClass = reinterpret_cast<jclass>(pEnv->NewGlobalRef(objClass));
        pEnv->DeleteLocalRef(objClass);
    }

    jmethodID methodId = pEnv->GetMethodID(callbacksClass, "onRadSetCall", "(F)V");
    triangle.setRadCallback(
            [pEnv, methodId](float radian) -> void {
                LOGI("radian is = %f", radian);
                pEnv->CallVoidMethod(callbacksInstance, methodId, (jfloat) radian);
            }
    );
}