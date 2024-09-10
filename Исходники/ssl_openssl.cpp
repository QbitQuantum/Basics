static bool SSL_library_load(void)
{
    /* Load Library Pointers */
    if (bSslInitDone) return true;

    WaitForSingleObject(g_hSslMutex, INFINITE);

    if (!bSslInitDone) {
        g_hOpenSSLCrypto = LoadLibraryA("libeay32.dll");
        g_hOpenSSL = LoadLibraryA("ssleay32.dll");
        if (g_hOpenSSL && g_hOpenSSLCrypto) {
            // load function pointers
#define LOAD_FN(struc,lib, name) struc.##name = (pfn##name)GetProcAddress(lib, #name);
            LOAD_FN(g_OpenSSL, g_hOpenSSLCrypto, RAND_screen);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_connect);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_free);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_get_error);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_library_init);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_load_error_strings);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_new);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_peek);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_pending);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_read);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_write);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_set_fd);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_shutdown);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_CTX_free);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_CTX_new);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_CTX_ctrl);
            LOAD_FN(g_OpenSSL, g_hOpenSSLCrypto, CRYPTO_set_mem_functions);

            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSLv23_client_method);

            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_get_current_cipher);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_CIPHER_get_name);

            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_get_peer_certificate);
            LOAD_FN(g_OpenSSL, g_hOpenSSL, SSL_get_peer_cert_chain);
            LOAD_FN(g_OpenSSL, g_hOpenSSLCrypto, CRYPTO_free);
            LOAD_FN(g_OpenSSL, g_hOpenSSLCrypto, X509_free);
            LOAD_FN(g_OpenSSL, g_hOpenSSLCrypto, i2d_X509);

            HINSTANCE hCrypt = LoadLibraryA("crypt32.dll");
            if (hCrypt) {
                LOAD_FN(g_Crypt, hCrypt, CertGetCertificateChain);
                LOAD_FN(g_Crypt, hCrypt, CertFreeCertificateChain);
                LOAD_FN(g_Crypt, hCrypt, CertFreeCertificateContext);
                LOAD_FN(g_Crypt, hCrypt, CertVerifyCertificateChainPolicy);
                LOAD_FN(g_Crypt, hCrypt, CertOpenStore);
                LOAD_FN(g_Crypt, hCrypt, CertCloseStore);
                LOAD_FN(g_Crypt, hCrypt, CertAddCertificateContextToStore);
                LOAD_FN(g_Crypt, hCrypt, CertCreateCertificateContext);
            }

            // init OpenSSL
            g_OpenSSL.SSL_library_init();
            g_OpenSSL.SSL_load_error_strings();
            g_OpenSSL.CRYPTO_set_mem_functions(mir_calloc, mir_realloc, mir_free);
            // FIXME check errors

            bSslInitDone = true;
        }
        else {
            SSL_library_unload();
        }
    }

    ReleaseMutex(g_hSslMutex);
    return bSslInitDone;
}