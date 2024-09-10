JNIEXPORT void JNICALL Java_org_berkelium_java_impl_WindowImpl_resize(JNIEnv* env, jobject self, jint w, jint h)
{
	Berkelium_Java_Env jEnv(env);
	getWindow(self)->resize(w, h);
}