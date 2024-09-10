	JNIEXPORT jboolean JNICALL OS_NATIVE(_1getMenuBarOrItemBounds)(JNIEnv *env, jclass that, JHANDLE jshell, jint jitemIndex, jintArray jbounds) {
		HWND hwnd = (HWND)unwrap_pointer(env, jshell);
		MENUBARINFO info;
		info.cbSize = sizeof(MENUBARINFO);
		if (GetMenuBarInfo(hwnd, OBJID_MENU, jitemIndex, &info)) {
			// prepare buffer
			jsize boundsSize = env->GetArrayLength(jbounds);
			jint *bounds = new jint [boundsSize * sizeof(jint)];
			*(bounds + 0) = info.rcBar.left;
			*(bounds + 1) = info.rcBar.right;
			*(bounds + 2) = info.rcBar.top;
			*(bounds + 3) = info.rcBar.bottom;
			// copy dimensions into java array
			env->SetIntArrayRegion(jbounds, 0, boundsSize, bounds);
			delete []bounds;
			return JNI_TRUE;
		}
		return JNI_FALSE;
	}