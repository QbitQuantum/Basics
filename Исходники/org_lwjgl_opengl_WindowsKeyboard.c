JNIEXPORT jint JNICALL Java_org_lwjgl_opengl_WindowsKeyboard_ToUnicode(JNIEnv *env, jclass unused, jint wVirtKey, jint wScanCode, jobject lpKeyState_obj, jobject pwszBuff_obj, jint cchBuff, jint flags) {
	const PBYTE lpKeyState = (*env)->GetDirectBufferAddress(env, lpKeyState_obj);
	LPWSTR pwszBuff = (*env)->GetDirectBufferAddress(env, pwszBuff_obj);
	return ToUnicode(wVirtKey, wScanCode, lpKeyState, pwszBuff, cchBuff, flags);
}