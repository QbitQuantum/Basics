int main(int argc, char **argv)
{
    swss::Logger::getInstance().setMinPrio(swss::Logger::SWSS_DEBUG);

    SWSS_LOG_ENTER();

    auto options = handleCmdLine(argc, argv);

    handleProfileMap(options.profileMapFile);

    swss::DBConnector *db = new swss::DBConnector(ASIC_DB, "localhost", 6379, 0);
    swss::DBConnector *dbNtf = new swss::DBConnector(ASIC_DB, "localhost", 6379, 0);

    g_redisClient = new swss::RedisClient(db);

    updateLogLevel();

    swss::ConsumerTable *asicState = new swss::ConsumerTable(db, "ASIC_STATE");
    swss::NotificationConsumer *notifySyncdQuery = new swss::NotificationConsumer(db, "NOTIFYSYNCDREQUERY");
    swss::NotificationConsumer *restartQuery = new swss::NotificationConsumer(db, "RESTARTQUERY");

    // at the end we cant use producer consumer concept since
    // if one proces will restart there may be something in the queue
    // also "remove" from response queue will also trigger another "response"
    getRequest = new swss::ConsumerTable(db, "GETREQUEST");
    getResponse  = new swss::ProducerTable(db, "GETRESPONSE");
    notifications = new swss::NotificationProducer(dbNtf, "NOTIFICATIONS");
    notifySyncdResponse = new swss::NotificationProducer(db, "NOTIFYSYNCDRESPONSE");

#ifdef MLNXSAI
    /* This file is included in Mellanox SAI package. */
    std::string mlnx_config_file = "/usr/share/sai_2700.xml";
    gProfileMap[SAI_KEY_INIT_CONFIG_FILE] = mlnx_config_file;
#endif /* MLNX_SAI */

    g_veryFirstRun = isVeryFirstRun();

    if (options.warmStart)
    {
        const char *warmBootReadFile = profile_get_value(0, SAI_KEY_WARM_BOOT_READ_FILE);

        SWSS_LOG_NOTICE("using warmBootReadFile: '%s'", warmBootReadFile);

        if (warmBootReadFile == NULL || access(warmBootReadFile, F_OK) == -1)
        {
            SWSS_LOG_WARN("user requested warmStart but warmBootReadFile is not specified or not accesible, forcing cold start");

            options.warmStart = false;
        }
    }

    if (options.warmStart && g_veryFirstRun)
    {
        SWSS_LOG_WARN("warm start requested, but this is very first syncd start, forcing cold start");

        // we force cold start since if it's first run then redis db is not complete
        // so redis asic view will not reflect warm boot asic state, if this happen
        // then orch agent needs to be restarted as well to repopulate asic view
        options.warmStart = false;
    }

//    gProfileMap[SAI_KEY_WARM_BOOT] = options.warmStart ? "1" : "0";

    sai_api_initialize(0, (service_method_table_t*)&test_services);

    populate_sai_apis();

    initialize_common_api_pointers();

    sai_status_t status = sai_switch_api->initialize_switch(0, "0xb850", "", &switch_notifications);

    if (status != SAI_STATUS_SUCCESS)
    {
        SWSS_LOG_ERROR("fail to sai_initialize_switch: %d", status);
        exit(EXIT_FAILURE);
    }

#ifdef BRCMSAI

    if (options.diagShell)
    {
        SWSS_LOG_NOTICE("starting bcm diag shell thread");

        std::thread bcm_diag_shell_thread = std::thread(sai_diag_shell);
        bcm_diag_shell_thread.detach();
    }

#endif /* BRCMSAI */

    SWSS_LOG_NOTICE("syncd started");

    bool warmRestartHint = false;

    try
    {
        onSyncdStart(options.warmStart);

        if (options.disableCountersThread == false)
        {
            SWSS_LOG_NOTICE("starting counters thread");

            startCountersThread(options.countersThreadIntervalInSeconds);
        }

        SWSS_LOG_NOTICE("syncd listening for events");

        swss::Select s;

        s.addSelectable(getRequest);
        s.addSelectable(asicState);
        s.addSelectable(notifySyncdQuery);
        s.addSelectable(restartQuery);

        while(true)
        {
            swss::Selectable *sel;

            int fd;

            int result = s.select(&sel, &fd);

            if (sel == restartQuery)
            {
                warmRestartHint = handleRestartQuery(*restartQuery);
                break;
            }

            if (sel == notifySyncdQuery)
            {
                notifySyncd(*notifySyncdQuery);
                continue;
            }

            if (result == swss::Select::OBJECT)
            {
                processEvent(*(swss::ConsumerTable*)sel);
            }
        }
    }
    catch(const std::exception &e)
    {
        SWSS_LOG_ERROR("Runtime error: %s", e.what());

        exit(EXIT_FAILURE);
    }

    endCountersThread();

    if (warmRestartHint)
    {
        const char *warmBootWriteFile = profile_get_value(0, SAI_KEY_WARM_BOOT_WRITE_FILE);

        SWSS_LOG_NOTICE("using warmBootWriteFile: '%s'", warmBootWriteFile);

        if (warmBootWriteFile == NULL)
        {
            SWSS_LOG_WARN("user requested warm shutdown but warmBootWriteFile is not specified, forcing cold shutdown");

            warmRestartHint = false;
        }
    }

    sai_switch_api->shutdown_switch(warmRestartHint);

    SWSS_LOG_NOTICE("calling api uninitialize");

    sai_api_uninitialize();

    SWSS_LOG_NOTICE("uninitialize finished");

    return EXIT_SUCCESS;
}