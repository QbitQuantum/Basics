JNIEXPORT jint JNICALL Java_org_lwjgl_system_windows_Mmsystem_njoyGetPos(JNIEnv *__env, jclass clazz, jint joyID, jlong jiAddress) {
	LPJOYINFO ji = (LPJOYINFO)(intptr_t)jiAddress;
	UNUSED_PARAMS(__env, clazz)
	return (jint)joyGetPos(joyID, ji);
}