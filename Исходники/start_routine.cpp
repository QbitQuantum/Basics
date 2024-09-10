void* start_routine(void *args)
{
	ALOGI(">>>>>>>>>>>>>I am in, I am a bad boy!!!!<<<<<<<<<<<<<<");

	JNIEnv *jnienv = NULL;
	JavaVM *javavm = NULL;
	bool should_detach = false;
	char *apk_path = NULL;

	javavm = AndroidRuntime::getJavaVM();
	if(javavm != NULL){

		javavm->GetEnv((void **)&jnienv, JNI_VERSION_1_4);

		if(jnienv == NULL){
			should_detach = true;
			javavm->AttachCurrentThread(&jnienv, NULL);
		}

		if(jnienv != NULL){

			apk_path = find_apk_path();
			if(!apk_path){
				ALOGE("Could found't apk_path");
				goto bails;
			}

			const char *dexout_dir = "/data/data/com.tencent.mm/dexout";

			int state = 0;

			if (access(dexout_dir, R_OK | W_OK | X_OK) != 0) {
				int state = mkdir(dexout_dir, S_IRWXU);
				if (state) {
					ALOGE("Could create dexout dir");
					goto bails;
				}
			}

			state = load_dex(jnienv, apk_path, dexout_dir, "com.android.testplugin.Entry", "invoke");
			if(state != 0){
				ALOGE("Load dex error!!");
				goto bails;
			}
		}
	}

bails:
	if(apk_path){
		free(apk_path);
		apk_path = NULL;
	}

	if(javavm && jnienv && should_detach){
		javavm->DetachCurrentThread();
		jnienv = NULL;
		javavm = NULL;
	}
	return NULL;
}