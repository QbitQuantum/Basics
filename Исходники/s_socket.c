static void ssl_sock_cleanup(void)
{
    if (wsa_init_done) {
        wsa_init_done = 0;
#  ifndef OPENSSL_SYS_WINCE
        WSACancelBlockingCall();
#  endif
        WSACleanup();
    }
}