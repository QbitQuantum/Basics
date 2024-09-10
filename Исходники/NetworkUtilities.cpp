static bool inetAddressToSockaddr(JNIEnv* env, jobject inetAddress, int port, sockaddr_storage& ss, socklen_t& sa_len, bool map) {
    memset(&ss, 0, sizeof(ss));
    sa_len = 0;

    if (inetAddress == NULL) {
        jniThrowNullPointerException(env, NULL);
        return false;
    }

    // Get the address family.
    static jfieldID familyFid = env->GetFieldID(JniConstants::inetAddressClass, "family", "I");
    ss.ss_family = env->GetIntField(inetAddress, familyFid);
    if (ss.ss_family == AF_UNSPEC) {
        sa_len = sizeof(ss.ss_family);
        return true; // Job done!
    }

    // Check this is an address family we support.
    if (ss.ss_family != AF_INET && ss.ss_family != AF_INET6 && ss.ss_family != AF_UNIX) {
        jniThrowExceptionFmt(env, "java/lang/IllegalArgumentException",
                "inetAddressToSockaddr bad family: %i", ss.ss_family);
        return false;
    }

    // Get the byte array that stores the IP address bytes in the InetAddress.
    static jfieldID bytesFid = env->GetFieldID(JniConstants::inetAddressClass, "ipaddress", "[B");
    ScopedLocalRef<jbyteArray> addressBytes(env, reinterpret_cast<jbyteArray>(env->GetObjectField(inetAddress, bytesFid)));
    if (addressBytes.get() == NULL) {
        jniThrowNullPointerException(env, NULL);
        return false;
    }

    // Handle the AF_UNIX special case.
    if (ss.ss_family == AF_UNIX) {
        sockaddr_un& sun = reinterpret_cast<sockaddr_un&>(ss);

        size_t path_length = env->GetArrayLength(addressBytes.get());
        if (path_length >= sizeof(sun.sun_path)) {
            jniThrowExceptionFmt(env, "java/lang/IllegalArgumentException",
                                 "inetAddressToSockaddr path too long for AF_UNIX: %i", path_length);
            return false;
        }

        // Copy the bytes...
        jbyte* dst = reinterpret_cast<jbyte*>(&sun.sun_path);
        memset(dst, 0, sizeof(sun.sun_path));
        env->GetByteArrayRegion(addressBytes.get(), 0, path_length, dst);
        sa_len = sizeof(sun.sun_path);
        return true;
    }

    // TODO: bionic's getnameinfo(3) seems to want its length parameter to be exactly
    // sizeof(sockaddr_in) for an IPv4 address and sizeof (sockaddr_in6) for an
    // IPv6 address. Fix getnameinfo so it accepts sizeof(sockaddr_storage), and
    // then unconditionally set sa_len to sizeof(sockaddr_storage) instead of having
    // to deal with this case by case.

    // We use AF_INET6 sockets, so we want an IPv6 address (which may be a IPv4-mapped address).
    sockaddr_in6& sin6 = reinterpret_cast<sockaddr_in6&>(ss);
    sin6.sin6_port = htons(port);
    if (ss.ss_family == AF_INET6) {
        // IPv6 address. Copy the bytes...
        jbyte* dst = reinterpret_cast<jbyte*>(&sin6.sin6_addr.s6_addr);
        env->GetByteArrayRegion(addressBytes.get(), 0, 16, dst);
        // ...and set the scope id...
        static jfieldID scopeFid = env->GetFieldID(JniConstants::inet6AddressClass, "scope_id", "I");
        sin6.sin6_scope_id = env->GetIntField(inetAddress, scopeFid);
        sa_len = sizeof(sockaddr_in6);
        return true;
    }

    // Deal with Inet4Address instances.
    if (map) {
        // We should represent this Inet4Address as an IPv4-mapped IPv6 sockaddr_in6.
        // Change the family...
        sin6.sin6_family = AF_INET6;
        // Copy the bytes...
        jbyte* dst = reinterpret_cast<jbyte*>(&sin6.sin6_addr.s6_addr[12]);
        env->GetByteArrayRegion(addressBytes.get(), 0, 4, dst);
        // INADDR_ANY and in6addr_any are both all-zeros...
        if (!IN6_IS_ADDR_UNSPECIFIED(&sin6.sin6_addr)) {
            // ...but all other IPv4-mapped addresses are ::ffff:a.b.c.d, so insert the ffff...
            memset(&(sin6.sin6_addr.s6_addr[10]), 0xff, 2);
        }
        sa_len = sizeof(sockaddr_in6);
    } else {
        // We should represent this Inet4Address as an IPv4 sockaddr_in.
        sockaddr_in& sin = reinterpret_cast<sockaddr_in&>(ss);
        sin.sin_port = htons(port);
        jbyte* dst = reinterpret_cast<jbyte*>(&sin.sin_addr.s_addr);
        env->GetByteArrayRegion(addressBytes.get(), 0, 4, dst);
        sa_len = sizeof(sockaddr_in);
    }
    return true;
}