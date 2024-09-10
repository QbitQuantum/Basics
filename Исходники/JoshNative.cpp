JNIEXPORT void JNICALL Java_JoshNative__1SetJavaConsoleTitle (JNIEnv* env, jclass, jstring title)
{
	const char *nativeString = (*env).GetStringUTFChars(title, 0);
#ifdef _WIN32
	SetConsoleTitleA(nativeString); // I don't like LPCWSTR. Yuck!
#elif __APPLE__
	char str[256];
	strcat(str, "sh title.sh ");
	strcat(str, nativeString);
#endif
}