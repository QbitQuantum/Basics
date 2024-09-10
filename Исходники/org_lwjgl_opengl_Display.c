JNIEXPORT void JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nDestroyWindow(JNIEnv *env, jclass clazz, jlong display, jlong window_ptr) {
	Display *disp = (Display *)(intptr_t)display;
	Window window = (Window)window_ptr;
	destroyWindow(env, disp, window);
}