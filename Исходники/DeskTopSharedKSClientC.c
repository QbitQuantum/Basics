/** Main entry point */
int CDECL_CALL main(void)
{
    QStatus status = ER_OK;
    alljoyn_interfacedescription testIntf = NULL;
    alljoyn_buslistener_callbacks callbacks = {
        NULL,
        NULL,
        &found_advertised_name,
        NULL,
        &name_owner_changed,
        NULL,
        NULL,
        NULL
    };
    unsigned int count = 0;

    if (alljoyn_init() != ER_OK) {
        return 1;
    }
#ifdef ROUTER
    if (alljoyn_routerinit() != ER_OK) {
        alljoyn_shutdown();
        return 1;
    }
#endif

    printf("AllJoyn Library version: %s\n", alljoyn_getversion());
    printf("AllJoyn Library build info: %s\n", alljoyn_getbuildinfo());

    /* Install SIGINT handler */
    signal(SIGINT, SigIntHandler);

    /* Create message bus */
    g_msgBus = alljoyn_busattachment_create("SRPSecurityClientC", QCC_TRUE);

    /* Add org.alljoyn.bus.samples.secure.SecureInterface interface */
    status = alljoyn_busattachment_createinterface_secure(g_msgBus, INTERFACE_NAME, &testIntf, AJ_IFC_SECURITY_REQUIRED);
    if (status == ER_OK) {
        alljoyn_interfacedescription_addmember(testIntf, ALLJOYN_MESSAGE_METHOD_CALL, "Ping", "s",  "s", "inStr1,outStr", 0);
        alljoyn_interfacedescription_activate(testIntf);
    } else {
        printf("Failed to create interface %s\n", INTERFACE_NAME);
    }

    /* Start the msg bus */
    if (ER_OK == status) {
        status = alljoyn_busattachment_start(g_msgBus);
        if (ER_OK != status) {
            printf("alljoyn_busattachment_start failed\n");
        } else {
            printf("alljoyn_busattachment started.\n");
        }
    }

    /*
     * enable security
     * note the location of the keystore file has been specified and the
     * isShared parameter is being set to true. So this keystore file can
     * be used by multiple applications
     */
    if (ER_OK == status) {
        alljoyn_authlistener_callbacks callbacks = {
            request_credentials,
            NULL,
            NULL,
            authentication_complete
        };
        g_authListener = alljoyn_authlistener_create(&callbacks, NULL);

        /*
         * alljoyn_busattachment_enablepeersecurity function is called by
         * applications that want to use authentication and encryption. This
         * function call must be made after alljoyn_busattachment_start and
         * before calling alljoyn_busattachment_connect.
         *
         * In most situations a per-application keystore file is generated.
         * However, this code specifies the location of the keystore file and
         * the isShared parameter is being set to QCC_TRUE. The resulting
         * keystore file can be used by multiple applications.
         */
        status = alljoyn_busattachment_enablepeersecurity(g_msgBus, "ALLJOYN_SRP_KEYX", g_authListener,
                                                          "/.alljoyn_keystore/central.ks", QCC_TRUE);
        if (ER_OK != status) {
            printf("alljoyn_busattachment_enablepeersecurity failed (%s)\n", QCC_StatusText(status));
        } else {
            printf("alljoyn_busattachment_enablepeersecurity Successful\n");
        }
    }

    /* Connect to the bus */
    if (ER_OK == status) {
        status = alljoyn_busattachment_connect(g_msgBus, NULL);
        if (ER_OK != status) {
            printf("alljoyn_busattachment_connect() failed with status: 0x%04x\n", status);
        } else {
            printf("alljoyn_busattachment connected to \"%s\"\n", alljoyn_busattachment_getconnectspec(g_msgBus));
        }
    }

    /* Create a bus listener */
    g_busListener = alljoyn_buslistener_create(&callbacks, NULL);

    /* Register a bus listener in order to get discovery indications */
    if (ER_OK == status) {
        alljoyn_busattachment_registerbuslistener(g_msgBus, g_busListener);
        printf("alljoyn_buslistener Registered.\n");
    }

    /* Begin discovery on the well-known name of the service to be called */
    if (ER_OK == status) {
        status = alljoyn_busattachment_findadvertisedname(g_msgBus, OBJECT_NAME);
        if (status != ER_OK) {
            printf("alljoyn_busattachment_findadvertisedname failed (%s))\n", QCC_StatusText(status));
        }
    }

    /* Wait for join session to complete */
    while (!s_joinComplete && !g_interrupt) {
        if (0 == (count++ % 10)) {
            printf("Waited %u seconds for alljoyn_busattachment_joinsession completion.\n", count / 10);
        }
#ifdef _WIN32
        Sleep(100);
#else
        usleep(100 * 1000);
#endif
    }

    if (status == ER_OK && g_interrupt == QCC_FALSE) {
        alljoyn_message reply;
        alljoyn_msgarg inputs;
        size_t numArgs;

        alljoyn_proxybusobject remoteObj = alljoyn_proxybusobject_create(g_msgBus, OBJECT_NAME, OBJECT_PATH, s_sessionId);
        const alljoyn_interfacedescription alljoynTestIntf = alljoyn_busattachment_getinterface(g_msgBus, INTERFACE_NAME);
        QCC_ASSERT(alljoynTestIntf);
        alljoyn_proxybusobject_addinterface(remoteObj, alljoynTestIntf);

        /*
         * Although AllJoyn will automatically try and establish a secure connection
         * when a method call is made.  It will only allow the user the amount of time
         * specified in the methodcall timeout parameter to enter user input.  For the
         * "Ping" method that is 5 seconds.  This is not a reasonable amount of time
         * for a user to see the security password and enter it.
         *
         * By calling alljoyn_proxybusobject_secureconnection the user will have
         * as much time as they need to to enter the security password to secure
         * the connection.
         */
        status = alljoyn_proxybusobject_secureconnection(remoteObj, QCC_TRUE);
        if (ER_OK == status) {
            reply = alljoyn_message_create(g_msgBus);
            inputs = alljoyn_msgarg_array_create(1);
            numArgs = 1;
            status = alljoyn_msgarg_array_set(inputs, &numArgs, "s", "ClientC says Hello AllJoyn!");

            status = alljoyn_proxybusobject_methodcall(remoteObj, INTERFACE_NAME, "Ping", inputs, 1, reply, 5000, 0);
            if (ER_OK == status) {
                char* ping_str;
                status = alljoyn_msgarg_get(alljoyn_message_getarg(reply, 0), "s", &ping_str);
                printf("%s.%s ( path=%s) returned \"%s\"\n", INTERFACE_NAME, "Ping",
                       OBJECT_PATH, ping_str);
            } else {
                printf("alljoyn_proxybusobject_methodcall on %s.%s failed\n", INTERFACE_NAME, "Ping");
            }
            alljoyn_msgarg_destroy(inputs);
            alljoyn_message_destroy(reply);
        }
        alljoyn_proxybusobject_destroy(remoteObj);
    }

    /* Deallocate bus */
    if (g_msgBus) {
        alljoyn_busattachment deleteMe = g_msgBus;
        g_msgBus = NULL;
        alljoyn_busattachment_destroy(deleteMe);
    }

    /* Deallocate bus listener */
    alljoyn_buslistener_destroy(g_busListener);

    /* Deallocate auth listener */
    alljoyn_authlistener_destroy(g_authListener);

    printf("exiting with status %d (%s)\n", status, QCC_StatusText(status));

#ifdef ROUTER
    alljoyn_routershutdown();
#endif
    alljoyn_shutdown();
    return (int) status;
}