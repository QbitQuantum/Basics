JNIEXPORT jobject JNICALL OS_NATIVE(_1makeShot)
(JNIEnv *env, jclass jclazz, jobject jwnd)
{
	WebWindow* wnd = getWebWindow(env, jwnd);
	HBITMAP hBmp = printWindow(wnd->getWebViewWindowHandle());
	return wrap_pointer(env, hBmp);
}