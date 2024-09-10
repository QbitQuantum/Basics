//@CalledByNative IBitmap
AutoPtr<IInterface> CppBrowserViewRendererHelper::CreateBitmap(
    /* [in] */ Int32 width,
    /* [in] */ Int32 height,
    /* [in] */ ICanvas* canvas)
{
    if (canvas != NULL) {
        // When drawing into a Canvas, there is a maximum size imposed
        // on Bitmaps that can be drawn. Respect that limit.
        Int32 w, h;
        canvas->GetMaximumBitmapWidth(&w);
        canvas->GetMaximumBitmapHeight(&h);
        width = Elastos::Core::Math::Min(width, w);
        height = Elastos::Core::Math::Min(height, h);
    }

    AutoPtr<IBitmap> bitmap;
    // try {
        AutoPtr<IBitmapHelper> helper;
        CBitmapHelper::AcquireSingleton((IBitmapHelper**)&helper);
        ECode ecode = helper->CreateBitmap(width, height, BitmapConfig_ARGB_8888, (IBitmap**)&bitmap);
    // } catch (OutOfMemoryError e) {
    //     android.util.Log.w(LOGTAG, "Error allocating bitmap");
    // }
        if (FAILED(ecode))
            Logger::W(LOGTAG, "Error allocation bitmap");

    return bitmap;
}