JNIEXPORT jlong
JNICALL Java_us_temerity_pipeline_NativeFileSys_freeDiskSpaceNative
(
 JNIEnv *env, 
 jclass cls, 
 jstring jpath  /* IN: the file/directory used to determine the file system */ 
)
{
  /* exception initialization */ 
  char msg[2048];
  jclass IOException = env->FindClass("java/io/IOException");
  if(IOException == 0) {
    errno = EINVAL;
    perror("NativeFileSys.freeDiskSpaceNative(), unable to lookup \"java/lang/IOException\"");
    return -1;
  }

  /* repackage the arguments */ 
  const char* path = env->GetStringUTFChars(jpath, 0);
  if((path == NULL) || (strlen(path) == 0)) {
    env->ThrowNew(IOException,"empty path argument");
    return -1;
  }

  /* lookup the free disk space */ 
  {
    DWORD sectPerClust, bytesPerSect, freeClust, totalClust;

    if(!GetDiskFreeSpaceA(path, &sectPerClust, &bytesPerSect, &freeClust, &totalClust)) {
      sprintf(msg, "cannot determine free disk space for (%s)", path); 
      env->ReleaseStringUTFChars(jpath, path);
      env->ThrowNew(IOException, msg); 
      return -1; 
    }

    env->ReleaseStringUTFChars(jpath, path);
    return ((jlong) freeClust)  * ((jlong) sectPerClust) * ((jlong) bytesPerSect);
  }
}