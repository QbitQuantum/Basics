static void GetPluginNames()
{
    char csSystemDir[_MAX_PATH];
    GetSystemDirectoryA(csSystemDir, sizeof(csSystemDir) - 50);

    // E.g. "C:\WINDOWS\System32\beidcardplugins\"
    std::string csPluginsDir = csSystemDir + std::string("\\") +
                               EIDMW_PLUGINS_DIR + std::string("\\");
    std::string strSearchFor = csPluginsDir + std::string("*.dll");
    const char *csSearchFor = strSearchFor.c_str();

    struct _finddata_t c_file;
    intptr_t hFile = _findfirst(csSearchFor, &c_file);
    if (hFile != -1)
    {
        int iFindRes;
        do
        {
            // On Windows, card plugins are linked to the CAL.
            // So emulation plugins need to be used with the emulation CAL,
            // and 'normal' plugins need to be used with the 'normal' CAL.
#ifdef CAL_EMULATION
            if (strstr(c_file.name, "Emulation") != NULL)
                AddPluginName(c_file.name, csPluginsDir + c_file.name);
#else
            if (strstr(c_file.name, "Emulation") == NULL)
                AddPluginName(c_file.name, csPluginsDir + c_file.name);
#endif
            iFindRes = _findnext(hFile, &c_file);
        }
        while (iFindRes == 0);

        _findclose(hFile);
    }

    m_bPluginNamesOK = true;
}