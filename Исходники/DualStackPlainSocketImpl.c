/*
 * Class:     java_net_DualStackPlainSocketImpl
 * Method:    listen0
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_java_net_DualStackPlainSocketImpl_listen0
  (JNIEnv *env, jclass clazz, jint fd, jint backlog) {
    if (listen(fd, backlog) == SOCKET_ERROR) {
        NET_ThrowNew(env, WSAGetLastError(), "listen failed");
    }
}