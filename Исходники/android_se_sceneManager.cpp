static jboolean se_loadPixelsData(JNIEnv *env, jobject obj, jstring savePath, jstring imageKey, jint w, jint h) {
    const char* imageKey8 = env->GetStringUTFChars(imageKey, 0);
    const char* savePath8 = env->GetStringUTFChars(savePath, 0);
    SE_ImageDataID imageDataid(imageKey8);
    SE_ResourceManager *resourceManager = SE_Application::getInstance()->getResourceManager();
    SE_ImageData* imgd = resourceManager->getImageData(imageDataid);
    if (!imgd) {
        char* data = NULL;
        int len = 0;
        SE_IO::readFileAll(savePath8, data, len);
        if(len != 0) {
            int power2Width = w;
            int power2Height = h;
            int pixelFormat = SE_ImageData::RGBA;
            if(!SE_Util::isPower2(w))
            {
                power2Width = SE_Util::higherPower2(w);
            }
            if(!SE_Util::isPower2(h))
            {
                power2Height = SE_Util::higherPower2(h);
            }
            imgd = new SE_ImageData;
            imgd->setWidth(power2Width);
            imgd->setHeight(power2Height);
            imgd->setBytesPerRow(power2Width * 4);
            imgd->setPixelFormat(pixelFormat);
            imgd->setData(data);
            imgd->setCompressType(SE_ImageData::RAW);
            imgd->setName(imageDataid.getStr());
            //imgd->setPreWidth(w);
            //imgd->setPreHeight(h);
            resourceManager->insertPathImageData(imageDataid.getStr(), imgd); 
            resourceManager->setIdPath(imageDataid.getStr(),imageDataid.getStr());            
        }
    }
    env->ReleaseStringUTFChars(imageKey, imageKey8);
    env->ReleaseStringUTFChars(savePath, savePath8);
    if (!imgd)
    {
         return false;
    }
    return true;
}