static void se_setViewImage2(JNIEnv* env, jobject clazz, jstring viewgroupName,jstring viewName, jobject jbitmap)
{
    const char* viewgroupname = env->GetStringUTFChars(viewgroupName, 0);
    const char* viewname = env->GetStringUTFChars(viewName, 0);
#ifdef NDK
    AndroidBitmapInfo bitmapInfo;
    int ret;
    void* pixels;
    if((ret = AndroidBitmap_getInfo(env, jbitmap, &bitmapInfo)) < 0)
    {
        LOGE("AndroidBitmap_getInfo() failed ! error = %d", ret);
        return;
    }
    if(bitmapInfo.format != ANDROID_BITMAP_FORMAT_RGB_565 && bitmapInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888)
    {
        LOGE("Bitmap format is not supported\n");
        return;
    }
    if((ret = AndroidBitmap_lockPixels(env, jbitmap, &pixels)) < 0)
    {
        LOGE("AndroidBitmap_lockPixels() failed ! error = %d", ret);
        return;
    }
    int pixelSize = 0;
    switch(bitmapInfo.format)
    {
        case ANDROID_BITMAP_FORMAT_RGB_565:
            pixelSize = 2;
            break;
        case ANDROID_BITMAP_FORMAT_RGBA_8888:
            pixelSize = 4;
            break;
        default:
            break;
    }
    int bytesPerRow = pixelSize * bitmapInfo.width;
    if(bytesPerRow != bitmapInfo.stride)
    {
        LOGE("bytes per row is not align with original image");
        return;
    }

    SE_ImageData* newImage = new SE_ImageData;
    newImage->setWidth(bitmapInfo.width);
    newImage->setHeight(bitmapInfo.height);
    switch(bitmapInfo.format)
    {
        case ANDROID_BITMAP_FORMAT_RGB_565:
            newImage->setPixelFormat(SE_ImageData::RGB_565);
            break;
        case ANDROID_BITMAP_FORMAT_RGBA_8888:
            newImage->setPixelFormat(SE_ImageData::RGBA);
            break;
        default:
            break;
    }
    int width = newImage->getWidth();
    int height = newImage->getHeight();
    unsigned char* src = (unsigned char*) pixels;
    unsigned char* dst = new unsigned char[width * height * pixelSize];
    for(int y = height - 1 ; y >= 0 ; y--)
    {
        unsigned char* srcData = src + y * width * pixelSize;
        unsigned char* dstData = dst + (height - 1 - y) * width * pixelSize;
        memcpy(dstData, srcData, width * pixelSize);
    }   
    newImage->setBytesPerRow(bytesPerRow);
    newImage->setData((char*)dst);
    newImage->setCompressType(SE_ImageData::RAW);
    SE_UIManager* uiManager = SE_Application::getInstance()->getUIManager();
    if(uiManager)
    {
	uiManager->SetViewImage(viewgroupname,viewname, newImage);
    }
    AndroidBitmap_unlockPixels(env, jbitmap);
#else
    SkBitmap* nativeBitmap = (SkBitmap*)env->GetIntField(jbitmap, nativeBitmapID);
    SkBitmap* bitmap = new  SkBitmap(*nativeBitmap);
    SE_ImageData*  newImgd = SE_ImageCodec::load(bitmap);
    SE_ImageCodec::resizeImageData(newImgd);

    LOGD("bitmap .config() %d",bitmap->config());
    LOGD("bitmap newImgd->getPixelFormat() %d",newImgd->getPixelFormat()); 
    SE_UIManager* uiManager = SE_Application::getInstance()->getUIManager();
    if(uiManager)
    {
	uiManager->SetViewImage(viewgroupname,viewname, newImgd);
    }
#endif

}