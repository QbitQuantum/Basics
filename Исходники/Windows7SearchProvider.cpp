void InvokeCallback(JNIEnv *env, jobject obj, jobject callback, std::wstring filename)
{
	jstring j_filename = env->NewString((const jchar *)filename.c_str(), filename.length());

	jclass fileClass = env->FindClass("java/io/File");
	jmethodID fileConstructor = env->GetMethodID(fileClass, "<init>", "(Ljava/lang/String;)V");
	jobject fileObj = env->NewObject(fileClass, fileConstructor, j_filename);

	jclass resultClass = env->FindClass("org/eclipse/mylyn/sandbox/search/ui/SearchResult");
	jmethodID resultConstructor = env->GetMethodID(resultClass, "<init>", "(Ljava/io/File;)V");
	jobject resultObj = env->NewObject(resultClass, resultConstructor, fileObj);

	jclass jc = env->GetObjectClass(callback);
	jmethodID mid = env->GetMethodID(jc, "searchResult","(Lorg/eclipse/mylyn/sandbox/search/ui/SearchResult;)V");
	env->CallObjectMethod(callback, mid, resultObj);
}