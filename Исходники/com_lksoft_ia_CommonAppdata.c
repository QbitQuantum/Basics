/*
 * Class:     com_lksoft_ia_CommonAppdata
 * Method:    getCommonAppdataDir
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_lksoft_ia_CommonAppdata_getCommonAppdataDir
  (JNIEnv *env, jclass c) {

	WCHAR path[MAX_PATH];
	if(SHGetFolderPathW(NULL, CSIDL_COMMON_APPDATA, NULL, 0, path) == S_OK) {
		return (*env)->NewString(env, (jchar *)path, wcslen(path));
	} else {
		return NULL;
	}
}