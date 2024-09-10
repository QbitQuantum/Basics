JNIEXPORT jobject JNICALL Java_com_btr_proxy_search_desktop_win_Win32ProxyUtils_winHttpGetIEProxyConfigForCurrentUser
(JNIEnv *env, jobject source) {

	WINHTTP_CURRENT_USER_IE_PROXY_CONFIG ieProxyInfo;

    // Retrieve the IE proxy configuration.
    BOOL result = WinHttpGetIEProxyConfigForCurrentUser( &ieProxyInfo );
	if (result == FALSE) {
		DWORD errorCode = GetLastError();
		return NULL;
	}

	jboolean autoDetect = ieProxyInfo.fAutoDetect;
	jstring autoConfigUrl = NULL;
	jstring proxy = NULL;
	jstring proxyBypass = NULL;

	if (ieProxyInfo.lpszAutoConfigUrl != NULL) {
		autoConfigUrl = env->NewString((jchar*)ieProxyInfo.lpszAutoConfigUrl, wcslen(ieProxyInfo.lpszAutoConfigUrl));
        GlobalFree( ieProxyInfo.lpszAutoConfigUrl );
    }
    if (ieProxyInfo.lpszProxy != NULL) {
		proxy = env->NewString((jchar*)ieProxyInfo.lpszProxy, wcslen(ieProxyInfo.lpszProxy));
		GlobalFree( ieProxyInfo.lpszProxy );
    }
    if (ieProxyInfo.lpszProxyBypass != NULL) {
		proxyBypass = env->NewString((jchar*)ieProxyInfo.lpszProxyBypass, wcslen(ieProxyInfo.lpszProxyBypass));
		GlobalFree( ieProxyInfo.lpszProxyBypass );
    }

	// Build result container object.
	jclass retValueClass = env->FindClass("com/btr/proxy/search/desktop/win/Win32IESettings");
	if ( retValueClass == NULL ) {
		return NULL;
	}
	
	jmethodID jmid = env->GetMethodID(retValueClass, "<init>", "(ZLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (jmid == NULL) {
		return NULL;
	}

	// Win32IESettings(boolean autoDetect, String autoConfigUrl, String proxy, String proxyBypass)
	jobject retValue = env->NewObject(retValueClass, jmid, autoDetect, autoConfigUrl, proxy, proxyBypass);

	return retValue;
}