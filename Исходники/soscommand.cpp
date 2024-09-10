    void
    LoadSos(LLDBServices *services)
    {
        if (m_sosHandle == NULL)
        {
            if (g_coreclrDirectory == NULL)
            {
                const char *coreclrModule = MAKEDLLNAME_A("coreclr");
                const char *directory = services->GetModuleDirectory(coreclrModule);
                if (directory != NULL)
                {
                    std::string path(directory);
                    path.append("/");
                    g_coreclrDirectory = strdup(path.c_str());
                }
                else
                {
                    services->Output(DEBUG_OUTPUT_WARNING, "The %s module is not loaded yet in the target process\n", coreclrModule);
                }
            }

            if (g_coreclrDirectory != NULL)
            {
                // Load the DAC module first explicitly because SOS and DBI
                // have implicit references to the DAC's PAL.
                LoadModule(services, MAKEDLLNAME_A("mscordaccore"));

                m_sosHandle = LoadModule(services, MAKEDLLNAME_A("sos"));
            }
        }
    }