package com.example.webp;

import android.content.res.AssetFileDescriptor;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.ColorFilter;
import android.graphics.PixelFormat;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.drawable.Drawable;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.AttributeSet;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;

import java.io.IOException;
import java.io.InputStream;

import static android.graphics.Bitmap.Config.ARGB_8888;

public class AnimatedWebpDrawable extends Drawable {
    private long mDecoder = 0;
    private Bitmap mBitmap = null;
    private RectF mDst = new RectF();
    private Rect mSrc = new Rect();
    private byte[] mData;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("webp-jni-lib");
    }

    @Override
    public void inflate(@NonNull Resources r, @NonNull XmlPullParser parser, @NonNull AttributeSet attrs, @Nullable Resources.Theme theme) throws XmlPullParserException, IOException {
        int src = ~0;
        super.inflate(r, parser, attrs, theme);
        for(int i=0; i<attrs.getAttributeCount(); i++) {
            if(attrs.getAttributeName(i).equals("src")) src = attrs.getAttributeResourceValue(i, ~0);
        }
        if(src < 0) {
            throw new XmlPullParserException("<AnimatedWebpDrawable> requires a valid 'src' attribute");
        }

        AssetFileDescriptor fd = r.openRawResourceFd(src);
        mData = new byte[(int)fd.getLength()];
        fd.close();

        InputStream inputStream = r.openRawResource(src);
        long count = inputStream.read(mData);

        mDecoder = WebPAnimDecoder(mData, count);
        int w = WebPAnimInfoGetCanvasWidth(mDecoder);
        int h = WebPAnimInfoGetCanvasHeight(mDecoder);
        if(w < 1) w = 1;
        if(h < 1) h = 1;
        mBitmap = Bitmap.createBitmap(w, h, ARGB_8888);
    }

    @Override
    public void draw(@NonNull Canvas canvas) {
        if(mBitmap == null) return;

        WebPAnimDecoderGetNextBitmap(mDecoder, mBitmap);
        mDst.set(0,0, getBounds().width(), getBounds().height());
        mSrc.set(0,0, mBitmap.getWidth(), mBitmap.getHeight());
        canvas.drawBitmap(mBitmap, mSrc, mDst, null);

        if(WebPAnimDecoderHasMoreFrames(mDecoder)==false) {
            WebPAnimDecoderReset(mDecoder);
        }
        invalidateSelf();
    }

    @Override
    public void setAlpha(int arg0) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void setColorFilter(@Nullable ColorFilter arg0) { throw new UnsupportedOperationException(); }

    @Override
    public int getOpacity() {
        return PixelFormat.TRANSLUCENT;
    }


    static native long WebPAnimDecoder(byte[] bytes, long size);
    static native int  WebPAnimInfoGetCanvasWidth(long dec);
    static native int  WebPAnimInfoGetCanvasHeight(long dec);
    static native int  WebPAnimDecoderGetNextBitmap(long dec, Bitmap bitmap);
    static native boolean  WebPAnimDecoderHasMoreFrames(long dec);
    static native void WebPAnimDecoderReset(long dec);
}
