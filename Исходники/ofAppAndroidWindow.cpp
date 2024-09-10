JNIEnv * ofGetJNIEnv(){
	JNIEnv *env;
	JavaVM * vm = ofGetJavaVMPtr();
	if(!vm){
		ofLog(OF_LOG_ERROR,"couldn't get java vm");
		return NULL;
	}
	if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		ofLog(OF_LOG_ERROR,"Failed to get the environment using GetEnv()");
		return NULL;
	}
	return env;
}