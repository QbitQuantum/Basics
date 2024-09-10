/*
 * Class:     sun_net_dns_ResolverConfgurationImpl
 * Method:    notifyAddrChange0
 * Signature: ()I
 */
JNIEXPORT jint JNICALL
Java_sun_net_dns_ResolverConfigurationImpl_notifyAddrChange0(JNIEnv *env, jclass cls)
{
    OVERLAPPED ol;
    HANDLE h;
    DWORD rc, xfer;

    ol.hEvent = (HANDLE)0;
    rc = NotifyAddrChange(&h, &ol);
    if (rc == ERROR_IO_PENDING) {
        rc = GetOverlappedResult(h, &ol, &xfer, TRUE);
        if (rc != 0) {
            return 0;   /* address changed */
        }
    }

    /* error */
    return -1;
}