int
main(int argc, char **argv) {

    if (argc == 2 && strcmp(argv[1], "adbd") == 0) {
        adb_main();
        return 0;
    }

    // Recovery needs to install world-readable files, so clear umask
    // set by init
    umask(0);

    if (strcmp(basename(argv[0]), "recovery") != 0)
    {
        if (strstr(argv[0], "minizip") != NULL)
            return minizip_main(argc, argv);
        if (strstr(argv[0], "dedupe") != NULL)
            return dedupe_main(argc, argv);
        if (strstr(argv[0], "flash_image") != NULL)
            return flash_image_main(argc, argv);
        if (strstr(argv[0], "volume") != NULL)
            return volume_main(argc, argv);
        if (strstr(argv[0], "edify") != NULL)
            return edify_main(argc, argv);
        if (strstr(argv[0], "dump_image") != NULL)
            return dump_image_main(argc, argv);
        if (strstr(argv[0], "erase_image") != NULL)
            return erase_image_main(argc, argv);
        if (strstr(argv[0], "mkyaffs2image") != NULL)
             return mkyaffs2image_main(argc, argv);
        if (strstr(argv[0], "make_ext4fs") != NULL)
            return make_ext4fs_main(argc, argv);
        if (strstr(argv[0], "unyaffs") != NULL)
            return unyaffs_main(argc, argv);
        if (strstr(argv[0], "nandroid"))
            return nandroid_main(argc, argv);
        if (strstr(argv[0], "bu") == argv[0] + strlen(argv[0]) - 2)
            return bu_main(argc, argv);
        if (strstr(argv[0], "reboot"))
            return reboot_main(argc, argv);
#ifdef BOARD_RECOVERY_HANDLES_MOUNT
        if (strstr(argv[0], "mount") && argc == 2 && !strstr(argv[0], "umount"))
        {
            load_volume_table();
            return ensure_path_mounted(argv[1]);
        }
#endif
        if (strstr(argv[0], "poweroff")){
            return reboot_main(argc, argv);
        }
        if (strstr(argv[0], "setprop"))
            return setprop_main(argc, argv);
        if (strstr(argv[0], "getprop"))
            return getprop_main(argc, argv);
        return busybox_driver(argc, argv);
    }
    __system("/sbin/postrecoveryboot.sh");

    int is_user_initiated_recovery = 0;
    time_t start = time(NULL);

    // If these fail, there's not really anywhere to complain...
    freopen(TEMPORARY_LOG_FILE, "a", stdout); setbuf(stdout, NULL);
    freopen(TEMPORARY_LOG_FILE, "a", stderr); setbuf(stderr, NULL);
    printf("Starting recovery on %s", ctime(&start));

    device_ui_init(&ui_parameters);
    ui_init();
    ui_print(EXPAND(RECOVERY_VERSION)"\n");
    load_volume_table();
    process_volumes();
    LOGI("Processing arguments.\n");
    get_args(&argc, &argv);

    int previous_runs = 0;
    const char *send_intent = NULL;
    const char *update_package = NULL;
    int wipe_data = 0, wipe_cache = 0;
    int sideload = 0;
    int headless = 0;

    LOGI("Checking arguments.\n");
    int arg;
    while ((arg = getopt_long(argc, argv, "", OPTIONS, NULL)) != -1) {
        switch (arg) {
        case 'p': previous_runs = atoi(optarg); break;
        case 's': send_intent = optarg; break;
        case 'u': update_package = optarg; break;
        case 'w': 
#ifndef BOARD_RECOVERY_ALWAYS_WIPES
        wipe_data = wipe_cache = 1;
#endif
        break;
        case 'h':
            ui_set_background(BACKGROUND_ICON_CID);
            ui_show_text(0);
            headless = 1;
            break;
        case 'c': wipe_cache = 1; break;
        case 't': ui_show_text(1); break;
        case 'l': sideload = 1; break;
        case '?':
            LOGE("Invalid command argument\n");
            continue;
        }
    }

    struct selinux_opt seopts[] = {
      { SELABEL_OPT_PATH, "/file_contexts" }
    };

    sehandle = selabel_open(SELABEL_CTX_FILE, seopts, 1);

    if (!sehandle) {
        fprintf(stderr, "Warning: No file_contexts\n");
        // ui_print("Warning:  No file_contexts\n");
    }

    LOGI("device_recovery_start()\n");
    device_recovery_start();

    printf("Command:");
    for (arg = 0; arg < argc; arg++) {
        printf(" \"%s\"", argv[arg]);
    }
    printf("\n");

    if (update_package) {
        // For backwards compatibility on the cache partition only, if
        // we're given an old 'root' path "CACHE:foo", change it to
        // "/cache/foo".
        if (strncmp(update_package, "CACHE:", 6) == 0) {
            int len = strlen(update_package) + 10;
            char* modified_path = malloc(len);
            strlcpy(modified_path, "/cache/", len);
            strlcat(modified_path, update_package+6, len);
            printf("(replacing path \"%s\" with \"%s\")\n",
                   update_package, modified_path);
            update_package = modified_path;
        }
    }
    printf("\n");

    property_list(print_property, NULL);
    printf("\n");

    int status = INSTALL_SUCCESS;

    if (update_package != NULL) {
        status = install_package(update_package);
        if (status != INSTALL_SUCCESS) ui_print("Installation aborted.\n");
    } else if (wipe_data) {
        if (device_wipe_data()) status = INSTALL_ERROR;
        ignore_data_media_workaround(1);
        if (erase_volume("/data")) status = INSTALL_ERROR;
        ignore_data_media_workaround(0);
        if (has_datadata() && erase_volume("/datadata")) status = INSTALL_ERROR;
        if (wipe_cache && erase_volume("/cache")) status = INSTALL_ERROR;
        if (status != INSTALL_SUCCESS) ui_print("Data wipe failed.\n");
    } else if (wipe_cache) {
        if (wipe_cache && erase_volume("/cache")) status = INSTALL_ERROR;
        if (status != INSTALL_SUCCESS) ui_print("Cache wipe failed.\n");
    } else if (sideload) {
        signature_check_enabled = 0;
        if (!headless)
          ui_set_show_text(1);
        if (0 == apply_from_adb()) {
            status = INSTALL_SUCCESS;
            ui_set_show_text(0);
        }
    } else {
        LOGI("Checking for extendedcommand...\n");
        status = INSTALL_ERROR;  // No command specified
        // we are starting up in user initiated recovery here
        // let's set up some default options
        signature_check_enabled = 0;
        script_assert_enabled = 0;
        is_user_initiated_recovery = 1;
        if (!headless) {
          ui_set_show_text(1);
          ui_set_background(BACKGROUND_ICON_CLOCKWORK);
        }
        
        if (extendedcommand_file_exists()) {
            LOGI("Running extendedcommand...\n");
            int ret;
            if (0 == (ret = run_and_remove_extendedcommand())) {
                status = INSTALL_SUCCESS;
                ui_set_show_text(0);
            }
            else {
                handle_failure(ret);
            }
        } else {
            LOGI("Skipping execution of extendedcommand, file not found...\n");
        }
    }

    setup_adbd();

    if (headless) {
      headless_wait();
    }
    if (status != INSTALL_SUCCESS && !is_user_initiated_recovery) {
        ui_set_show_text(1);
        ui_set_background(BACKGROUND_ICON_ERROR);
    }
    else if (status != INSTALL_SUCCESS || ui_text_visible()) {
        prompt_and_wait();
    }

    verify_root_and_recovery();

    // If there is a radio image pending, reboot now to install it.
    maybe_install_firmware_update(send_intent);

    // Otherwise, get ready to boot the main system...
    finish_recovery(send_intent);

    sync();
    if(!poweroff) {
        ui_print("Rebooting...\n");
        android_reboot(ANDROID_RB_RESTART, 0, 0);
    }
    else {
        ui_print("Shutting down...\n");
        android_reboot(ANDROID_RB_POWEROFF, 0, 0);
    }
    return EXIT_SUCCESS;
}