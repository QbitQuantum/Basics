JNIEXPORT jint JNICALL
Java_sun_nio_ch_DatagramDispatcher_read0(JNIEnv *env, jclass clazz, jobject fdo,
                                      jlong address, jint len)
{
    /* set up */
    int i = 0;
    DWORD read = 0;
    DWORD flags = 0;
    jint fd = fdval(env, fdo);
    WSABUF buf;

    /* destination buffer and size */
    buf.buf = (char *)address;
    buf.len = (u_long)len;

    /* read into the buffers */
    i = WSARecv((SOCKET)fd, /* Socket */
            &buf,           /* pointers to the buffers */
            (DWORD)1,       /* number of buffers to process */
            &read,          /* receives number of bytes read */
            &flags,         /* no flags */
            0,              /* no overlapped sockets */
            0);             /* no completion routine */

    if (i == SOCKET_ERROR) {
        int theErr = (jint)WSAGetLastError();
        if (theErr == WSAEWOULDBLOCK) {
            return IOS_UNAVAILABLE;
        }
        if (theErr == WSAECONNRESET) {
            purgeOutstandingICMP(env, clazz, fd);
            JNU_ThrowByName(env, JNU_JAVANETPKG "PortUnreachableException", 0);
            return IOS_THROWN;
        }
        JNU_ThrowIOExceptionWithLastError(env, "Write failed");
        return IOS_THROWN;
    }

    return convertReturnVal(env, (jint)read, JNI_TRUE);
}