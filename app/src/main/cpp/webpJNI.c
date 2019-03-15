#include <stdlib.h>
#include <android/bitmap.h>
#include <webp/demux.h>
#include <math.h>
#include <malloc.h>
#include "jni.h"
#include "webp/types.h"
#include "webp/decode.h"

jlong JNICALL Java_com_example_webp_AnimatedWebpDrawable_WebPAnimDecoder(JNIEnv *jenv, jclass jcls, jbyteArray bytes, jlong size) {
    jlong jresult = 0 ;
    WebPData* data = (WebPData *) malloc(sizeof(WebPData));
    data->bytes = (*jenv)->GetByteArrayElements(jenv, bytes, NULL);
    data->size = size;

    (void)jenv;
    (void)jcls;

    WebPAnimDecoderOptions *dec_options = (WebPAnimDecoderOptions *) malloc(sizeof(WebPAnimDecoderOptions));
    WebPAnimDecoderOptionsInit(dec_options);

    // Tune 'dec_options' as needed.

    WebPAnimDecoder* dec = WebPAnimDecoderNew(data, dec_options);
    jresult = (jlong) dec;
    return jresult;
}

jint JNICALL Java_com_example_webp_AnimatedWebpDrawable_WebPAnimInfoGetCanvasWidth(JNIEnv *jenv, jclass jcls, jlong decLong) {
    jint jresult = 0 ;
    WebPAnimDecoder* dec = (WebPAnimDecoder*) decLong;
    WebPAnimInfo info;
    int result;

    (void)jenv;
    (void)jcls;
    result = WebPAnimDecoderGetInfo(dec, &info);
    (void)result;

    result = info.canvas_width;
    jresult = (jint)result;
    return jresult;
}

jint JNICALL Java_com_example_webp_AnimatedWebpDrawable_WebPAnimInfoGetCanvasHeight(JNIEnv *jenv, jclass jcls, jlong decLong) {
    jint jresult = 0 ;
    WebPAnimDecoder* dec = (WebPAnimDecoder*) decLong;
    WebPAnimInfo info;
    int result;

    (void)jenv;
    (void)jcls;
    result = WebPAnimDecoderGetInfo(dec, &info);
    (void)result;

    result = info.canvas_height;
    jresult = (jint)result;
    return jresult;
}

jint JNICALL Java_com_example_webp_AnimatedWebpDrawable_WebPAnimDecoderGetNextBitmap(JNIEnv *jenv, jclass jcls, jlong decLong, jobject bitmap) {
    jint jresult = 0 ;
    WebPAnimDecoder* dec = (WebPAnimDecoder*) decLong;
    uint8_t* pixels;
    int result;
    int timestamp;
    uint8_t* buffer = NULL;
    AndroidBitmapInfo info;

    (void)jenv;
    (void)jcls;

    AndroidBitmap_getInfo(jenv, bitmap, &info);
    result = AndroidBitmap_lockPixels(jenv, bitmap, &pixels);
    if (result < 0) { return jresult; }

    result = WebPAnimDecoderGetNext(dec, &buffer, &timestamp);
    memcpy(pixels,buffer,info.height*info.width*sizeof(u_int32_t));

    AndroidBitmap_unlockPixels(jenv, bitmap);

    jresult = (jint)result;
    return jresult;
}

jboolean JNICALL Java_com_example_webp_AnimatedWebpDrawable_WebPAnimDecoderHasMoreFrames(JNIEnv *jenv, jclass jcls, jlong decLong) {
    jboolean jresult = 0;
    WebPAnimDecoder* dec = (WebPAnimDecoder*) decLong;
    int result;

    (void)jenv;
    (void)jcls;
    result = WebPAnimDecoderHasMoreFrames(dec);
    jresult = (jboolean) result;
    return jresult;
}

void JNICALL Java_com_example_webp_AnimatedWebpDrawable_WebPAnimDecoderReset(JNIEnv *jenv, jclass jcls, jlong decLong) {
    WebPAnimDecoder* dec = (WebPAnimDecoder*) decLong;
    (void)jenv;
    (void)jcls;
    WebPAnimDecoderReset(dec);
}
