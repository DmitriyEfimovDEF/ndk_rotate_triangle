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

void queryRuntimeInfo(JNIEnv *env, jobject instance) {
    // Find out which OS we are running on. It does not matter for this app
    // just to demo how to call static functions.
    // Our java JniHelper class id and instance are initialized when this
    // shared lib got loaded, we just directly use them
    //    static function does not need instance, so we just need to feed
    //    class and method id to JNI
//    jmethodID versionFunc = (*env).GetStaticMethodID(
//            g_ctx.triangleClz,
//            "getBuildVersion", "()Ljava/lang/String;");
//    if (!versionFunc) {
//        LOGE("Failed to retrieve getBuildVersion() methodID @ line %d",
//             __LINE__);
//        return;
//    }
//    auto buildVersion = static_cast<jstring>((*env).CallStaticObjectMethod(g_ctx.triangleClz, versionFunc)); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
//    const char *version = (*env).GetStringUTFChars(buildVersion, NULL);
//    if (!version) {
//        LOGE("Unable to get version string @ line %d", __LINE__);
//        return;
//    }
//    LOGI("Android Version - %s", version);
//    (*env).ReleaseStringUTFChars(buildVersion, version);
//
//    // we are called from JNI_OnLoad, so got to release LocalRef to avoid leaking
//    (*env).DeleteLocalRef(buildVersion);
//
//    // Query available memory size from a non-static public function
//    // we need use an instance of JniHelper class to call JNI
//    jmethodID memFunc = (*env).GetMethodID(g_ctx.triangleClz,
//                                            "getRuntimeMemorySize", "()J");
//    if (!memFunc) {
//        LOGE("Failed to retrieve getRuntimeMemorySize() methodID @ line %d",
//             __LINE__);
//        return;
//    }
//    jlong result = (*env).CallLongMethod(instance, memFunc);
//    LOGI("Runtime free memory size: %" PRId64, result);
//    (void)result;  // silence the compiler warning
}

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
//    queryRuntimeInfo(env, g_ctx.triangleObj);

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