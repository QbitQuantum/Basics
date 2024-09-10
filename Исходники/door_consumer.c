int CDECL_CALL main(void)
{
    alljoyn_busattachment bus;
    alljoyn_observer obs;
    alljoyn_observerlistener listener;
    alljoyn_interfacedescription intf;
    alljoyn_interfacedescription_member member;
    QCC_BOOL done;
    const char* intfname = INTF_NAME;

    if (alljoyn_init() != ER_OK) {
        return 1;
    }
#ifdef ROUTER
    if (alljoyn_routerinit() != ER_OK) {
        alljoyn_shutdown();
        return 1;
    }
#endif

    bus = alljoyn_busattachment_create("door_consumer_c", QCC_TRUE);
    setup_busattachment(bus);

    obs = alljoyn_observer_create(bus, &intfname, 1);
    listener_ctx.observer = obs;
    listener_ctx.bus = bus;
    listener = alljoyn_observerlistener_create(&listener_cbs, &listener_ctx);
    alljoyn_observer_registerlistener(obs, listener, QCC_TRUE);

    intf = alljoyn_busattachment_getinterface(bus, INTF_NAME);
    alljoyn_interfacedescription_getmember(intf, "PersonPassedThrough", &member);
    alljoyn_busattachment_registersignalhandler(bus, person_passed_through, member, NULL);

    done = QCC_FALSE;
    while (!done) {
        char input[200];
        char* str;

        printf("> "); fflush(stdout);
        str = fgets(input, sizeof(input), stdin);
        if (str == NULL) {
            break;
        }
        str = strchr(input, '\n');
        if (str) {
            *str = '\0';
        }
        done = !parse(bus, obs, input);
    }

    // Cleanup
    alljoyn_observer_destroy(obs);
    alljoyn_observerlistener_destroy(listener);

    /* Deallocate bus */
    if (bus) {
        alljoyn_busattachment deleteMe = bus;
        bus = NULL;
        alljoyn_busattachment_destroy(deleteMe);
    }

#ifdef ROUTER
    alljoyn_routershutdown();
#endif
    alljoyn_shutdown();
    return 0;
}