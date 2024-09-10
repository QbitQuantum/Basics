static jchar getMirror(JNIEnv* env, jobject obj, jchar c)
{   
    return u_charMirror(c);
}