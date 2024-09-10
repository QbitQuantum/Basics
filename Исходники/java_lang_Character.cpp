//static jint Character_digitImpl(JNIEnv*, jclass, jint codePoint, jint radix) {
JNIEXPORT jint JNICALL
Java_java_lang_Character_digitImpl(JNIEnv*, jclass, jint codePoint, jint radix) {
    return u_digit(codePoint, radix);
}