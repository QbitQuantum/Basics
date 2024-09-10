    bool openrct2_initialise()
    {
#ifndef DISABLE_NETWORK
        gHashCTX = EVP_MD_CTX_create();
        Guard::Assert(gHashCTX != nullptr, "EVP_MD_CTX_create failed");
#endif // DISABLE_NETWORK

        crash_init();

        // Sets up the environment OpenRCT2 is running in, e.g. directory paths
        OpenRCT2::_env = OpenRCT2::SetupEnvironment();
        if (OpenRCT2::_env == nullptr)
        {
            return false;
        }

        if (!rct2_interop_setup_segment())
        {
            log_fatal("Unable to load RCT2 data sector");
            return false;
        }

        if (gConfigGeneral.last_run_version != nullptr && String::Equals(gConfigGeneral.last_run_version, OPENRCT2_VERSION))
        {
            gOpenRCT2ShowChangelog = false;
        }
        else
        {
            gOpenRCT2ShowChangelog = true;
            gConfigGeneral.last_run_version = String::Duplicate(OPENRCT2_VERSION);
            config_save_default();
        }

        // TODO add configuration option to allow multiple instances
        // if (!gOpenRCT2Headless && !platform_lock_single_instance()) {
        // 	log_fatal("OpenRCT2 is already running.");
        // 	return false;
        // }

        IObjectRepository * objRepo = CreateObjectRepository(OpenRCT2::_env);
        ITrackDesignRepository * tdRepo = CreateTrackDesignRepository(OpenRCT2::_env);
        IScenarioRepository * scenarioRepo = CreateScenarioRepository(OpenRCT2::_env);

        if (!language_open(gConfigGeneral.language))
        {
            log_error("Failed to open configured language...");
            if (!language_open(LANGUAGE_ENGLISH_UK))
            {
                log_fatal("Failed to open fallback language...");
                return false;
            }
        }

        // TODO Ideally we want to delay this until we show the title so that we can
        //      still open the game window and draw a progress screen for the creation
        //      of the object cache.
        objRepo->LoadOrConstruct();

        // TODO Like objects, this can take a while if there are a lot of track designs
        //      its also really something really we might want to do in the background
        //      as its not required until the player wants to place a new ride.
        tdRepo->Scan();

        scenarioRepo->Scan();
        TitleSequenceManager::Scan();

        if (!gOpenRCT2Headless)
        {
            audio_init();
            audio_populate_devices();
        }

        http_init();
        theme_manager_initialise();

        rct2_interop_setup_hooks();

        if (!rct2_init())
        {
            return false;
        }

        chat_init();

        rct2_copy_original_user_files_over();
        return true;
    }