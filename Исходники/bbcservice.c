QStatus AJ_CALL request_credentials_async(const void* context, alljoyn_authlistener listener, const char* authMechanism,
                                          const char* authPeer, uint16_t authCount, const char* userId,
                                          uint16_t credMask, void* authContext)
{
    char guid[100];
    size_t size_of_guid = 100;
    alljoyn_credentials creds;
    QStatus status = ER_OK;

    creds = alljoyn_credentials_create();

    printf("RequestCredentials for authenticating %s using mechanism %s\n", authPeer, authMechanism);

    /* Random delay TODO*/

    alljoyn_busattachment_getpeerguid(g_msgBus, authPeer, guid, &size_of_guid);
    printf("Peer guid %s   %zu\n", guid, size_of_guid);

    if (g_keyExpiration != 0xFFFFFFFF) {
        alljoyn_busattachment_setkeyexpiration(g_msgBus, guid, g_keyExpiration);
    }

    if (strcmp(authMechanism, "ALLJOYN_PIN_KEYX") == 0) {
        if (credMask & ALLJOYN_CRED_PASSWORD) {
            alljoyn_credentials_setpassword(creds, "ABCDEFGH");
            printf("AuthListener returning fixed pin \"%s\" for %s\n", alljoyn_credentials_getpassword(creds), authMechanism);
        }

        status = alljoyn_authlistener_requestcredentialsresponse(listener, authContext, QCC_TRUE, creds);
        alljoyn_credentials_destroy(creds);
        return status;
    }

    if (strcmp(authMechanism, "ALLJOYN_SRP_KEYX") == 0) {
        if (credMask & ALLJOYN_CRED_PASSWORD) {
            if (authCount == 1) {
                alljoyn_credentials_setpassword(creds, "yyyyyy");
            } else {
                alljoyn_credentials_setpassword(creds, "123456");
            }
            printf("AuthListener returning fixed pin \"%s\" for %s\n", alljoyn_credentials_getpassword(creds), authMechanism);
        }
        status =  alljoyn_authlistener_requestcredentialsresponse(listener, authContext, QCC_TRUE, creds);
        alljoyn_credentials_destroy(creds);
        return status;
    }

    if (strcmp(authMechanism, "ALLJOYN_RSA_KEYX") == 0) {
        if (credMask & ALLJOYN_CRED_CERT_CHAIN) {
            alljoyn_credentials_setcertchain(creds, x509certChain);
        }
        if (credMask & ALLJOYN_CRED_PRIVATE_KEY) {
            alljoyn_credentials_setprivatekey(creds, privKey);
        }
        if (credMask & ALLJOYN_CRED_PASSWORD) {
            if (authCount == 2) {
                alljoyn_credentials_setpassword(creds, "12345X");
            }
            if (authCount == 3) {
                alljoyn_credentials_setpassword(creds, "123456");
            }
        }
        status = alljoyn_authlistener_requestcredentialsresponse(listener, authContext, QCC_TRUE, creds);
        alljoyn_credentials_destroy(creds);
        return status;
    }

    if (strcmp(authMechanism, "ALLJOYN_SRP_LOGON") == 0) {
        if (!userId) {
            status = alljoyn_authlistener_requestcredentialsresponse(listener, authContext, QCC_FALSE, creds);
            alljoyn_credentials_destroy(creds);
            return status;
        }
        printf("Attempting to logon user %s\n", userId);
        if (strcmp(userId, "happy") == 0) {
            if (credMask & ALLJOYN_CRED_PASSWORD) {
                alljoyn_credentials_setpassword(creds, "123456");
                status = alljoyn_authlistener_requestcredentialsresponse(listener, authContext, QCC_TRUE, creds);
                alljoyn_credentials_destroy(creds);
                return status;
            }
        }
        if (strcmp(userId, "sneezy") == 0) {
            if (credMask & ALLJOYN_CRED_PASSWORD) {
                alljoyn_credentials_setpassword(creds, "123456");
                status = alljoyn_authlistener_requestcredentialsresponse(listener, authContext, QCC_TRUE, creds);
                alljoyn_credentials_destroy(creds);
                return status;
            }
        }
        /*
         * Allow 3 logon attempts.
         */
        if (authCount <= 3) {
            status = alljoyn_authlistener_requestcredentialsresponse(listener, authContext, QCC_TRUE, creds);
            alljoyn_credentials_destroy(creds);
            return status;
        }
    }

    status = alljoyn_authlistener_requestcredentialsresponse(listener, authContext, QCC_FALSE, creds);
    alljoyn_credentials_destroy(creds);
    return status;

}