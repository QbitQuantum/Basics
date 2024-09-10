/** Main entry point */
int CDECL_CALL main(void)
{
    QStatus status = ER_OK;
    char* connectArgs = "unix:abstract=alljoyn";
    alljoyn_interfacedescription testIntf = NULL;
    alljoyn_busobject_callbacks busObjCbs = {
        NULL,
        NULL,
        &busobject_object_registered,
        NULL
    };
    alljoyn_busobject testObj = NULL;
    alljoyn_interfacedescription exampleIntf;
    alljoyn_interfacedescription_member cat_member;
    QCC_BOOL foundMember = QCC_FALSE;
    alljoyn_busobject_methodentry methodEntries[] = {
        { &cat_member, cat_method },
    };
    alljoyn_sessionportlistener_callbacks spl_cbs = {
        accept_session_joiner,
        NULL
    };
    alljoyn_sessionopts opts = NULL;

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
    g_msgBus = alljoyn_busattachment_create("myApp", QCC_TRUE);

    if (g_msgBus != NULL) {
        /* Add org.alljoyn.Bus.method_sample interface */
        status = alljoyn_busattachment_createinterface(g_msgBus, INTERFACE_NAME, &testIntf);
        if (status == ER_OK) {
            alljoyn_interfacedescription_addmember(testIntf, ALLJOYN_MESSAGE_METHOD_CALL, "cat", "ss",  "s", "inStr1,inStr2,outStr", 0);
            alljoyn_interfacedescription_activate(testIntf);
            printf("Interface Created.\n");
        } else {
            printf("Failed to create interface 'org.alljoyn.Bus.method_sample'\n");
        }

        /* Register a bus listener */
        if (ER_OK == status) {
            /* Create a bus listener */
            alljoyn_buslistener_callbacks callbacks = {
                NULL,
                NULL,
                NULL,
                NULL,
                &name_owner_changed,
                NULL,
                NULL,
                NULL
            };
            g_busListener = alljoyn_buslistener_create(&callbacks, NULL);
            alljoyn_busattachment_registerbuslistener(g_msgBus, g_busListener);
        }

        /* Set up bus object */
        testObj = alljoyn_busobject_create(OBJECT_PATH, QCC_FALSE, &busObjCbs, NULL);
        exampleIntf = alljoyn_busattachment_getinterface(g_msgBus, INTERFACE_NAME);
        assert(exampleIntf);
        alljoyn_busobject_addinterface(testObj, exampleIntf);

        foundMember = alljoyn_interfacedescription_getmember(exampleIntf, "cat", &cat_member);
        assert(foundMember == QCC_TRUE);
        if (!foundMember) {
            printf("Failed to get cat member of interface\n");
        }

        status = alljoyn_busobject_addmethodhandlers(testObj, methodEntries, sizeof(methodEntries) / sizeof(methodEntries[0]));
        if (ER_OK != status) {
            printf("Failed to register method handlers for BasicSampleObject\n");
        }

        /* Start the msg bus */
        status = alljoyn_busattachment_start(g_msgBus);
        if (ER_OK == status) {
            printf("alljoyn_busattachment started.\n");
            /* Register  local objects and connect to the daemon */
            status = alljoyn_busattachment_registerbusobject(g_msgBus, testObj);

            /* Create the client-side endpoint */
            if (ER_OK == status) {
                status = alljoyn_busattachment_connect(g_msgBus, connectArgs);
                if (ER_OK != status) {
                    printf("alljoyn_busattachment_connect(\"%s\") failed\n", (connectArgs) ? connectArgs : "NULL");
                } else {
                    printf("alljoyn_busattachment connected to \"%s\"\n", alljoyn_busattachment_getconnectspec(g_msgBus));
                }
            }
        } else {
            printf("alljoyn_busattachment_start failed\n");
        }

        /*
         * Advertise this service on the bus
         * There are three steps to advertising this service on the bus
         * 1) Request a well-known name that will be used by the client to discover
         *    this service
         * 2) Create a session
         * 3) Advertise the well-known name
         */
        /* Request name */
        if (ER_OK == status) {
            uint32_t flags = DBUS_NAME_FLAG_REPLACE_EXISTING | DBUS_NAME_FLAG_DO_NOT_QUEUE;
            QStatus status = alljoyn_busattachment_requestname(g_msgBus, OBJECT_NAME, flags);
            if (ER_OK != status) {
                printf("alljoyn_busattachment_requestname(%s) failed (status=%s)\n", OBJECT_NAME, QCC_StatusText(status));
            }
        }

        /* Create session port listener */
        s_sessionPortListener = alljoyn_sessionportlistener_create(&spl_cbs, NULL);

        /* Create session */
        opts = alljoyn_sessionopts_create(ALLJOYN_TRAFFIC_TYPE_MESSAGES, QCC_FALSE, ALLJOYN_PROXIMITY_ANY, ALLJOYN_TRANSPORT_ANY);
        if (ER_OK == status) {
            alljoyn_sessionport sp = SERVICE_PORT;
            status = alljoyn_busattachment_bindsessionport(g_msgBus, &sp, opts, s_sessionPortListener);
            if (ER_OK != status) {
                printf("alljoyn_busattachment_bindsessionport failed (%s)\n", QCC_StatusText(status));
            }
        }

        /* Advertise name */
        if (ER_OK == status) {
            status = alljoyn_busattachment_advertisename(g_msgBus, OBJECT_NAME, alljoyn_sessionopts_get_transports(opts));
            if (status != ER_OK) {
                printf("Failed to advertise name %s (%s)\n", OBJECT_NAME, QCC_StatusText(status));
            }
        }

        if (ER_OK == status) {
            while (g_interrupt == QCC_FALSE) {
    #ifdef _WIN32
                Sleep(100);
    #else
                usleep(100 * 1000);
    #endif
            }
        }
    }
    /* Deallocate sessionopts */
    if (opts) {
        alljoyn_sessionopts_destroy(opts);
    }
    /* Deallocate bus */
    if (g_msgBus) {
        alljoyn_busattachment deleteMe = g_msgBus;
        g_msgBus = NULL;
        alljoyn_busattachment_destroy(deleteMe);
    }

    /* Deallocate bus listener */
    if (g_busListener) {
        alljoyn_buslistener_destroy(g_busListener);
    }

    /* Deallocate session port listener */
    if (s_sessionPortListener) {
        alljoyn_sessionportlistener_destroy(s_sessionPortListener);
    }

    /* Deallocate the bus object */
    if (testObj) {
        alljoyn_busobject_destroy(testObj);
    }

#ifdef ROUTER
    alljoyn_routershutdown();
#endif
    alljoyn_shutdown();
    return (int) status;
}