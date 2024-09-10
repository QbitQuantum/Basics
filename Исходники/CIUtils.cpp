JNIEXPORT jint JNICALL Java_org_trafodion_ci_WCIUtils_getConsoleMode
   (JNIEnv *env, jobject ob)
{
   DWORD mode;
   HANDLE hConsole = GetStdHandle (STD_INPUT_HANDLE);

   if (hConsole == INVALID_HANDLE_VALUE)
      return -1;

   if (!GetConsoleMode (hConsole, &mode))
      return -1;

   // CloseHandle (hConsole);
   //printf ("JNI get mode=%d\n", mode);

   return mode;
}