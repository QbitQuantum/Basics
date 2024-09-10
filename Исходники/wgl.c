JNIEXPORT jboolean JNICALL WGL_NATIVE(wglSwapLayerBuffers)
	(JNIEnv *env, jclass that, jintLong arg0, jint arg1)
{
	jboolean rc = 0;
	WGL_NATIVE_ENTER(env, that, wglSwapLayerBuffers_FUNC);
	rc = (jboolean)wglSwapLayerBuffers((HDC)arg0, arg1);
	WGL_NATIVE_EXIT(env, that, wglSwapLayerBuffers_FUNC);
	return rc;
}