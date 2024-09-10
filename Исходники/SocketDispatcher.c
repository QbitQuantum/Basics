JNIEXPORT void JNICALL
Java_sun_nio_ch_SocketDispatcher_preClose0(JNIEnv *env, jclass clazz,
        jobject fdo)
{
    jint fd = fdval(env, fdo);
    struct linger l;
    int len = sizeof(l);
    if (getsockopt(fd, SOL_SOCKET, SO_LINGER, (char *)&l, &len) == 0) {
        if (l.l_onoff == 0) {
            WSASendDisconnect(fd, NULL);
        }
    }
}