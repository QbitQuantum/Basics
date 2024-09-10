	static JNIEnv *getJavaEnv()
	{
		JavaVM *jvm = __state->activity->vm;
		JNIEnv *java_env = NULL;
		jvm->GetEnv((void **)&java_env, JNI_VERSION_1_6);
		jint res = jvm->AttachCurrentThread(&java_env, NULL);
		if (res == JNI_ERR) {
			GP_ERROR("Failed to retrieve JVM environment when entering message pump.");
		}
		GP_ASSERT(java_env);
		return java_env;
	}