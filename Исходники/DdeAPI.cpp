JNIEXPORT jint JNICALL Java_com_google_code_jdde_ddeml_DdeAPI_GetLastError
  (JNIEnv *env, jclass cls, jint idInst)
{
	return DdeGetLastError(idInst);
}