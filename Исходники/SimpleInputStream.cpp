JNIEXPORT jboolean JNICALL Java_mjava_io_SimpleInputStream_hasnextLine (JNIEnv * env, jobject obj)
{
	setlocale(LC_ALL, "Chinese-simplified"); // <clocale>

	wchar_t ch = getwchar();
	if(ch == WEOF) return 0; // 不要用EOF
	//if(ch == L'E') return 0; // 测试：读到E开头的字符串就退出

	ungetwc(ch, stdin);
	return 1;
}