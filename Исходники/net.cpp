    void init_net()
    {
        WSADATA wsa_data;
        WSAStartup(MAKEWORD(2, 2), &wsa_data);
#ifdef HTTP_USE_OPENSSL
        detail::init_openssl();
#else
        detail::sspi = InitSecurityInterfaceW();
#endif
    }