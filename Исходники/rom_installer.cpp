int rom_installer_main(int argc, char *argv[])
{
    if (unshare(CLONE_NEWNS) < 0) {
        fprintf(stderr, "unshare() failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    if (mount("", "/", "", MS_PRIVATE | MS_REC, "") < 0) {
        fprintf(stderr, "Failed to set private mount propagation: %s\n",
                strerror(errno));
        return false;
    }

    // Make stdout unbuffered
    setvbuf(stdout, nullptr, _IONBF, 0);

    std::string rom_id;
    std::string zip_file;

    int opt;

    static struct option long_options[] = {
        {"romid", required_argument, 0, 'r'},
        {"help",  no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    int long_index = 0;

    while ((opt = getopt_long(argc, argv, "r:h", long_options, &long_index)) != -1) {
        switch (opt) {
        case 'r':
            rom_id = optarg;
            break;

        case 'h':
            rom_installer_usage(false);
            return EXIT_SUCCESS;

        default:
            rom_installer_usage(true);
            return EXIT_FAILURE;
        }
    }

    if (argc - optind != 1) {
        rom_installer_usage(true);
        return EXIT_FAILURE;
    }

    zip_file = argv[optind];

    if (rom_id.empty()) {
        fprintf(stderr, "-r/--romid must be specified\n");
        return EXIT_FAILURE;
    }

    if (zip_file.empty()) {
        fprintf(stderr, "Invalid zip file path\n");
        return EXIT_FAILURE;
    }


    // Make sure install type is valid
    if (!Roms::is_valid(rom_id)) {
        fprintf(stderr, "Invalid ROM ID: %s\n", rom_id.c_str());
        return EXIT_FAILURE;
    }

    auto rom = Roms::get_current_rom();
    if (!rom) {
        fprintf(stderr, "Could not determine current ROM\n");
        return EXIT_FAILURE;
    }

    if (rom->id == rom_id) {
        fprintf(stderr, "Can't install over current ROM (%s)\n",
                rom_id.c_str());
        return EXIT_FAILURE;
    }


    if (geteuid() != 0) {
        fprintf(stderr, "rom-installer must be run as root\n");
        return EXIT_FAILURE;
    }

    if (mount("", "/", "", MS_REMOUNT, "") < 0) {
        fprintf(stderr, "Failed to remount / as writable\n");
        return EXIT_FAILURE;
    }


    // We do not need to patch the SELinux policy or switch to mb_exec because
    // the daemon will guarantee that we run in that context. We'll just warn if
    // this happens to not be the case (eg. debugging via command line).

    std::string context;
    if (util::selinux_get_process_attr(
            0, util::SELinuxAttr::CURRENT, &context)
            && context != MB_EXEC_CONTEXT) {
        fprintf(stderr, "WARNING: Not running under %s context\n",
                MB_EXEC_CONTEXT);
    }


    autoclose::file fp(autoclose::fopen(MULTIBOOT_LOG_INSTALLER, "wb"));
    if (!fp) {
        fprintf(stderr, "Failed to open %s: %s\n",
                MULTIBOOT_LOG_INSTALLER, strerror(errno));
        return EXIT_FAILURE;
    }

    fix_multiboot_permissions();

    // Close stdin
#if !DEBUG_LEAVE_STDIN_OPEN
    int fd = open("/dev/null", O_RDONLY);
    if (fd >= 0) {
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
#endif

    // mbtool logging
    log::log_set_logger(std::make_shared<log::StdioLogger>(fp.get(), false));

    // Start installing!
    RomInstaller ri(zip_file, rom_id, fp.get());
    return ri.start_installation() ? EXIT_SUCCESS : EXIT_FAILURE;
}