JNIEXPORT jint JNICALL Java_com_yifanlu_Josh_Josh_GETNUMBEROFCONSOLEMOUSEBUTTONS
  (JNIEnv *env, jclass jcls)
{
	DWORD numEvents;
	GetNumberOfConsoleMouseButtons(&numEvents);
	return numEvents;
}