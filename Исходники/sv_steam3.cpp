/* <ed99c> ../engine/sv_steam3.cpp:827 */
void CSteam3Client::InitClient()
{
    if (m_bLoggedOn)
        return;

    m_bLoggedOn = true;
    _unlink("steam_appid.txt");
    if (!getenv("SteamAppId"))
    {
        int nAppID = GetGameAppID();
        if (nAppID > 0)
        {
            FILE* f = fopen("steam_appid.txt", "w+");
            if (f)
            {
                fprintf(f, "%d\n", nAppID);
                fclose(f);
            }
        }
    }

    if (!SteamAPI_Init())
        Sys_Error("Failed to initalize authentication interface. Exiting...\n");

    m_bLogOnResult = false;
}