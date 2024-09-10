JNIEXPORT jint JNICALL Java_com_iteye_weimingtom_wce_clipboard_ClipboardJNI_setClipboardViewer
  (JNIEnv *env, jclass cls, jint hWndNewViewer)
{
	HWND ret = 0; 
	ret = SetClipboardViewer((HANDLE)hWndNewViewer);
#if 0
	if (ret == NULL) 
	{
		ErrorExit("SetClipboardViewer");
	}
#endif
	return (jint)ret; 
}