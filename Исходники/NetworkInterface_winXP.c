/*
 * return an array of IP_ADAPTER_ADDRESSES containing one element
 * for each adapter on the system. Returned in *adapters.
 * Buffer is malloc'd and must be freed (unless error returned)
 */
static int getAdapters (JNIEnv *env, IP_ADAPTER_ADDRESSES **adapters) {
    DWORD ret, flags;
    IP_ADAPTER_ADDRESSES *adapterInfo;
    ULONG len;
    char *error_msg_buf = NULL;
    size_t error_msg_buf_size =
            strlen("IP Helper Library GetAdaptersAddresses function failed"
                   " with error == ") + 10;
    int _ret = 0;


    adapterInfo = (IP_ADAPTER_ADDRESSES *)malloc (bufsize);
    if (adapterInfo == NULL) {
        JNU_ThrowByName(env, "java/lang/OutOfMemoryError",
            "Native heap allocation failure");
        return -1;
    }

    len = bufsize;
    flags = GAA_FLAG_SKIP_DNS_SERVER;
    flags |= GAA_FLAG_SKIP_MULTICAST;
    flags |= GAA_FLAG_INCLUDE_PREFIX;
    ret = GetAdaptersAddresses(AF_UNSPEC, flags, NULL, adapterInfo, &len);

    if (ret == ERROR_BUFFER_OVERFLOW) {
        IP_ADAPTER_ADDRESSES * newAdapterInfo = NULL;
        if (len  < (ULONG_MAX - bufsize)) {
            len = len + bufsize;
        }
        newAdapterInfo =
            (IP_ADAPTER_ADDRESSES *) realloc (adapterInfo, len);
        if (newAdapterInfo == NULL) {
            free(adapterInfo);
            JNU_ThrowByName(env, "java/lang/OutOfMemoryError",
                "Native heap allocation failure");
            return -1;
        }

        adapterInfo = newAdapterInfo;

        ret = GetAdaptersAddresses(AF_UNSPEC, flags, NULL, adapterInfo, &len);
    }

    if (ret != ERROR_SUCCESS) {
        free (adapterInfo);
        if (ret == ERROR_INSUFFICIENT_BUFFER) {
            JNU_ThrowByName(env, "java/lang/Error",
                "IP Helper Library GetAdaptersAddresses function failed "
                "with ERROR_INSUFFICIENT_BUFFER");
        } else if (ret == ERROR_ADDRESS_NOT_ASSOCIATED ) {
            JNU_ThrowByName(env, "java/lang/Error",
                "IP Helper Library GetAdaptersAddresses function failed "
                "with ERROR_ADDRESS_NOT_ASSOCIATED");
        } else {
            error_msg_buf = (char *)malloc(error_msg_buf_size);
            if (error_msg_buf != NULL) {
                memset(error_msg_buf, 0, error_msg_buf_size);
                _ret = _snprintf_s(error_msg_buf, error_msg_buf_size,
                    _TRUNCATE, "IP Helper Library GetAdaptersAddresses "
                                "function failed with error == %d", ret);
                if (_ret != -1) {
                    JNU_ThrowByName(env, "java/lang/Error", error_msg_buf);
                } else {
                    JNU_ThrowByName(env, "java/lang/Error",
                        "IP Helper Library GetAdaptersAddresses function failure");
                }
            } else {
                JNU_ThrowByName(env, "java/lang/Error",
                    "IP Helper Library GetAdaptersAddresses function failed");
            }
        }
        return -1;
    }
    *adapters = adapterInfo;
    return ERROR_SUCCESS;
}