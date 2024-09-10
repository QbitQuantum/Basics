int adb_main(int is_daemon, int server_port)
{
#if !ADB_HOST
    int port;
    char value[PROPERTY_VALUE_MAX];

    umask(000);
#endif

    atexit(adb_cleanup);
#ifdef HAVE_WIN32_PROC
    SetConsoleCtrlHandler( ctrlc_handler, TRUE );
#elif defined(HAVE_FORKEXEC)
    // No SIGCHLD. Let the service subproc handle its children.
    signal(SIGPIPE, SIG_IGN);
#endif

    init_transport_registration();

#if ADB_HOST
    HOST = 1;

#ifdef WORKAROUND_BUG6558362
    if(is_daemon) adb_set_affinity();
#endif
    usb_vendors_init();
    usb_init();
    local_init(DEFAULT_ADB_LOCAL_TRANSPORT_PORT);
    adb_auth_init();

    char local_name[30];
    build_local_name(local_name, sizeof(local_name), server_port);
    if(install_listener(local_name, "*smartsocket*", NULL, 0)) {
        exit(1);
    }
#else
    property_get("ro.adb.secure", value, "0");
    auth_enabled = !strcmp(value, "1");
    if (auth_enabled)
        adb_auth_init();

    // Our external storage path may be different than apps, since
    // we aren't able to bind mount after dropping root.
    const char* adb_external_storage = getenv("ADB_EXTERNAL_STORAGE");
    if (NULL != adb_external_storage) {
        setenv("EXTERNAL_STORAGE", adb_external_storage, 1);
    } else {
        D("Warning: ADB_EXTERNAL_STORAGE is not set.  Leaving EXTERNAL_STORAGE"
          " unchanged.\n");
    }

    /* don't listen on a port (default 5037) if running in secure mode */
    /* don't run as root if we are running in secure mode */
    if (should_drop_privileges()) {
        drop_capabilities_bounding_set_if_needed();

        /* add extra groups:
        ** AID_ADB to access the USB driver
        ** AID_LOG to read system logs (adb logcat)
        ** AID_INPUT to diagnose input issues (getevent)
        ** AID_INET to diagnose network issues (netcfg, ping)
        ** AID_GRAPHICS to access the frame buffer
        ** AID_NET_BT and AID_NET_BT_ADMIN to diagnose bluetooth (hcidump)
        ** AID_SDCARD_R to allow reading from the SD card
        ** AID_SDCARD_RW to allow writing to the SD card
        ** AID_NET_BW_STATS to read out qtaguid statistics
        */
        gid_t groups[] = { AID_ADB, AID_LOG, AID_INPUT, AID_INET, AID_GRAPHICS,
                           AID_NET_BT, AID_NET_BT_ADMIN, AID_SDCARD_R, AID_SDCARD_RW,
                           AID_NET_BW_STATS };
        if (setgroups(sizeof(groups)/sizeof(groups[0]), groups) != 0) {
            exit(1);
        }

        /* then switch user and group to "shell" */
        if (setgid(AID_SHELL) != 0) {
            exit(1);
        }
        if (setuid(AID_SHELL) != 0) {
            exit(1);
        }

        D("Local port disabled\n");
    } else {
        char local_name[30];
        build_local_name(local_name, sizeof(local_name), server_port);
        if(install_listener(local_name, "*smartsocket*", NULL, 0)) {
            exit(1);
        }
    }

    int usb = 0;
    if (access(USB_ADB_PATH, F_OK) == 0 || access(USB_FFS_ADB_EP0, F_OK) == 0) {
        // listen on USB
        usb_init();
        usb = 1;
    }

    // If one of these properties is set, also listen on that port
    // If one of the properties isn't set and we couldn't listen on usb,
    // listen on the default port.
    property_get("service.adb.tcp.port", value, "");
    if (!value[0]) {
        property_get("persist.adb.tcp.port", value, "");
    }
    if (sscanf(value, "%d", &port) == 1 && port > 0) {
        printf("using port=%d\n", port);
        // listen on TCP port specified by service.adb.tcp.port property
        local_init(port);
    } else if (!usb) {
        // listen on default port
        local_init(DEFAULT_ADB_LOCAL_TRANSPORT_PORT);
    }

    D("adb_main(): pre init_jdwp()\n");
    init_jdwp();
    D("adb_main(): post init_jdwp()\n");
#endif

    if (is_daemon)
    {
        // inform our parent that we are up and running.
#ifdef HAVE_WIN32_PROC
        DWORD  count;
        WriteFile( GetStdHandle( STD_OUTPUT_HANDLE ), "OK\n", 3, &count, NULL );
#elif defined(HAVE_FORKEXEC)
        fprintf(stderr, "OK\n");
#endif
        start_logging();
    }
    D("Event loop starting\n");

    fdevent_loop();

    usb_cleanup();

    return 0;
}