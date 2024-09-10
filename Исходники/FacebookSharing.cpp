void FacebookSharing::facebookShare(const std::string& text, const ShareCallback& callback)
{
    int status;
    JNIEnv* env;
    JavaVM* gJavaVM = w2f2::AndroidNDKUtils::getJavaVM();
    bool isAttached = false;

    status = gJavaVM->GetEnv((void**)&env, JNI_VERSION_1_4);
    if(status < 0)
    {
        __android_log_print(ANDROID_LOG_ERROR, "cocos2dx PiratesVSNinjas",
            "(PIRATES) Failed to get JNI environment, assuming native thread");
        status = gJavaVM->AttachCurrentThread(&env, NULL);
        if (status < 0)
        {
            __android_log_print(ANDROID_LOG_ERROR, "cocos2dx PiratesVSNinjas",
                "(PIRATES) facebookShare: failed to attach current thread");
            return;
        }
        isAttached = true;
    }

    jclass activity_class = env->GetObjectClass(g_activity);
    if (!activity_class )
    {
        __android_log_print(ANDROID_LOG_ERROR, "cocos2dx PiratesVSNinjas",
            "(PIRATES) facebookShare: failed to get class reference");
        if (isAttached)
            gJavaVM->DetachCurrentThread();
        return;
    }

    jmethodID method = env->GetMethodID(activity_class, "facebookShare", "(Ljava/lang/String;)V");
    if (!method)
    {
        __android_log_print(ANDROID_LOG_ERROR, "cocos2dx PiratesVSNinjas",
            "(PIRATES) facebookShare: failed to get method ID");
        if (isAttached)
            gJavaVM->DetachCurrentThread();
        return;
    }

    jstring j_text = env->NewStringUTF(text.c_str());


    shareCallback_ = callback;
    env->CallVoidMethod(g_activity, method, j_text);

    // ShareCallback share_callback = callback;
	// 
	// d_->facebookSharing_.description = [NSString stringWithUTF8String:text.c_str()];
	// [d_->facebookSharing_ shareWithCompletion:^(BOOL published, NSError *error) {
	// 	
	// 	share_callback.call(published ? true : false, d_->parseError(error));
	// 	
	// }];
}