void BIO_sock_cleanup(void)
	{
#ifdef OPENSSL_SYS_WINDOWS
	if (wsa_init_done)
		{
		wsa_init_done=0;
#ifndef OPENSSL_SYS_WINCE
		WSACancelBlockingCall();
#endif
		WSACleanup();
		}
#elif defined(OPENSSL_SYS_NETWARE) && !defined(NETWARE_BSDSOCK)
   if (wsa_init_done)
        {
        wsa_init_done=0;
        WSACleanup();
		}
#endif
	}