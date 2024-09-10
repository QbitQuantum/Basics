// --------------------------------------------------------------------------
// This function frees this dll, allowing the operating system to remove
// the code from memory and releasing the reference to the dll on disk. 
// After this call this dll can not be used any more.
//
// THIS FUNCTION DOES NOT RETURN !!!
// --------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_com_izforge_izpack_util_os_ShellLink_FreeLibrary (JNIEnv *env, 
                                                                              jobject obj,
                                                                              jstring name)
{
  // convert the name from Java string type
  const char *libraryName = (env)->GetStringUTFChars (name, 0);

  // get a module handle 
  HMODULE handle = GetModuleHandle (libraryName);

  // release the string object
  (env)->ReleaseStringUTFChars (name, libraryName);
  
  // now we are rady to free the library
  FreeLibraryAndExitThread (handle, 0);
}