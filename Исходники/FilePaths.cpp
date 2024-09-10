void GetFilePath(char* dest, int maxLength, const char* pFileName)
{


    //jni wtf
    // Acquire a pointer to the current JavaVM
    JavaVM * jVM = Playtomic::CPlaytomicAndroid::GetJavaVM();
    if(jVM == NULL)
    {
        return;
    }

    JNIEnv* env = 0;

    int status = jVM->GetEnv((void **)&env, JNI_VERSION_1_6);
    bool dettachProcess = false;
    if(status < 0)
    {
        dettachProcess = true;
        status = jVM->AttachCurrentThread(&env, NULL);
        if(status < 0)
        {
            return;
        }
    }
    jclass cls_env = env->FindClass("android/os/Environment");
    jmethodID mid_getExtStorage = env->GetStaticMethodID(cls_env, "getExternalStorageDirectory",  "()Ljava/io/File;");
    jobject obj_File = env->CallStaticObjectMethod(cls_env, mid_getExtStorage);

    jclass file = env->FindClass("java/io/File");
    jmethodID mid_getPath = env->GetMethodID(file, "getPath", "()Ljava/lang/String;");

    jstring obj_Path = (jstring)(env->CallObjectMethod(obj_File, mid_getPath));

    const char* path = env->GetStringUTFChars(obj_Path, NULL);

    std::string fullPath(path);
    env->ReleaseStringUTFChars(obj_Path, path);
    fullPath +=  "/";
    fullPath += pFileName;

    if(fullPath.length() > maxLength)
    {
        return;
    }

    strcpy( dest, fullPath.c_str());


    if(dettachProcess)
    {
        jVM->DetachCurrentThread();
    }
}