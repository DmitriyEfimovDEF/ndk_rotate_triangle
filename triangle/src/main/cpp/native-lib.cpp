#include <jni.h>
#include <cstring>
#include <cinttypes>
#include <pthread.h>
#include <jni.h>
#include <cassert>
#include <android/log.h>
#include "Triangle.hpp"
//#include "Triangle.cpp"

static Triangle triangle;
static const char* kTAG = "~~~~~ triangle-jniCallback";

#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))

typedef struct set_context {
    JavaVM *javaVM;
    jclass triangleClz;
    jobject triangleObj;
    jclass surfaceFragmentClz;
    jobject surfaceFragmentObj;
    pthread_mutex_t lock;
    int done;
} SetContext;
SetContext g_ctx;


extern "C"
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv* env;
    memset(&g_ctx, 0, sizeof(g_ctx));
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    };
    jclass clz = (env)->FindClass("com/example/triangle/Triangle");
    g_ctx.triangleClz = static_cast<jclass>((env)->NewGlobalRef(clz)); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    jmethodID triangleCtor = (env)->GetMethodID(g_ctx.triangleClz,
                                                 "<init>", "()V");
    jobject handler = (env)->NewObject(g_ctx.triangleClz,
                                        triangleCtor);
    g_ctx.triangleObj = (env)->NewGlobalRef( handler);

    g_ctx.done = 0;
    g_ctx.surfaceFragmentObj = NULL;
    return JNI_VERSION_1_6;
}

void   setRadValue(JNIEnv *env,
                   jobject instance,
                   jmethodID func,
                   const char* msg) {
    jstring javaMsg = (env)->NewStringUTF( msg);
    (env)->CallVoidMethod(instance, func, javaMsg);
    (env)->DeleteLocalRef(javaMsg);
}

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
        jfloat rad) {

    jclass clazz = pEnv->FindClass("com/example/triangle/Triangle");
    jmethodID methodId = pEnv->GetMethodID(clazz, "onRadSet", "(F)V");
    pEnv->CallVoidMethod(pThis, methodId, rad);
}