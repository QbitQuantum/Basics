static jboolean isBoundaryImpl(JNIEnv*, jclass, jint address, jint offset) {
    return ubrk_isBoundary(breakIterator(address), offset);
}