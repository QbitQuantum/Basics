//-----------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL Java_com_softwarrior_libtorrent_LibTorrent_AbortSession
	(JNIEnv *, jobject)
{
	jboolean result = JNI_FALSE;
	try {
		if(gSessionState)
			gSession.abort();
	} catch(...){
		LOG_ERR("Exception: failed to abort session");
		gSessionState=false;
	}
	if(!gSessionState) LOG_ERR("LibTorrent.AbortSession SessionState==false");
	gSessionState==true ? result=JNI_TRUE : result=JNI_FALSE;
	return result;
}