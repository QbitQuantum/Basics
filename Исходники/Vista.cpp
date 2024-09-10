JNIEXPORT void JNICALL Java_com_yifanlu_Josh_Josh_SETCONSOLEHISTORYINFO
  (JNIEnv *env, jclass jcls, jint bufferSize, jint numberOfBuffers, jint flags)
{
	CONSOLE_HISTORY_INFO info;
	info.cbSize = sizeof(CONSOLE_HISTORY_INFO);
	info.HistoryBufferSize = bufferSize;
	info.NumberOfHistoryBuffers = numberOfBuffers;
	info.dwFlags = flags;

	SetConsoleHistoryInfo(&info);
}