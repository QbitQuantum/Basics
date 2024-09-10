CConnectionInfoBase::EConnectionType CConnectionInfoAndroid::GetConnectionType()
{
    
// Acquire a pointer to the current JavaVM
    JavaVM * jVM = CPlaytomicAndroid::GetJavaVM();
    if(jVM == NULL)
    {

        return e_disconnected;
    }
    jobject activity = CPlaytomicAndroid::GetActivity();
    
    JNIEnv* env = 0;
    
  	int status = jVM->GetEnv((void **)&env, JNI_VERSION_1_6);
    bool dettachProcess = false;
    if(status < 0)
    {
        dettachProcess = true;
	    status = jVM->AttachCurrentThread(&env, NULL);
	    if(status < 0)
	    {
                LOGI("invalid env");
	        return e_disconnected;
	    }
    }

    jclass cls_context = env->FindClass("android/content/Context");
	jmethodID sys_service = env->GetMethodID(cls_context, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    
	jfieldID fid = env->GetStaticFieldID(cls_context, "CONNECTIVITY_SERVICE",
                                         "Ljava/lang/String;");
    
	jstring systemstr = (jstring)env->GetStaticObjectField(cls_context, fid);

	jobject obj_connectManager = env->CallObjectMethod(activity, sys_service,systemstr);
    jclass cls_env = env->GetObjectClass(obj_connectManager);
	jmethodID mid_getExtStorage = env->GetMethodID(cls_env, "getActiveNetworkInfo", "()Landroid/net/NetworkInfo;");
	jobject obj_netInfo = env->CallObjectMethod(obj_connectManager, mid_getExtStorage);
    int type = -1;
    if( obj_netInfo)
    {
        jclass cls_netInfo = env->GetObjectClass(obj_netInfo);
        jmethodID mid_getType = env->GetMethodID(cls_netInfo, "getType",  "()I");
        type = env->CallIntMethod(obj_netInfo, mid_getType);

    }
    LOGI("type : %d", type);
    switch (type)
    {
        case e_wifi:
            return e_wifi;
            break;
        case e_mobile:
            return e_mobile;
            break;
    }
    return e_disconnected;
}