int main(int argc, char *argv[])
{
    static const WCHAR svcctl_started_event[] = SVCCTL_STARTED_EVENT;
    DWORD err;

    g_hStartedEvent = CreateEventW(NULL, TRUE, FALSE, svcctl_started_event);
    load_registry_parameters();
    err = scmdatabase_create(&active_database);
    if (err != ERROR_SUCCESS)
        return err;
    if ((err = scmdatabase_load_services(active_database)) != ERROR_SUCCESS)
        return err;
    if ((err = RPC_Init()) == ERROR_SUCCESS)
    {
        scmdatabase_autostart_services(active_database);
        events_loop();
        scmdatabase_wait_terminate(active_database);
    }
    scmdatabase_destroy(active_database);
    if (env)
        DestroyEnvironmentBlock(env);

    WINE_TRACE("services.exe exited with code %d\n", err);
    return err;
}