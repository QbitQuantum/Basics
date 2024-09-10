int FMOD_Main()
{
    FMOD::System        *system           = 0;
    FMOD_RESULT          result;
    unsigned int         version;
    void                *extradriverdata  = 0;
    unsigned int         pluginhandle;
    InspectorState       state            = PLUGIN_SELECTOR;
    PluginSelectorState  pluginselector   = { 0 };
    ParameterViewerState parameterviewer  = { 0 };

    Common_Init(&extradriverdata);

    /*
        Create a System object and initialize
    */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
    }

    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
    ERRCHECK(result);

    result = system->getNumPlugins(FMOD_PLUGINTYPE_DSP, &pluginselector.numplugins);
    ERRCHECK(result);

    pluginselector.system = system;

    do
    {
        Common_Update();

        if (state == PLUGIN_SELECTOR)
        {
            state = pluginSelectorDo(&pluginselector);

            if (state == PARAMETER_VIEWER)
            {
                result = pluginselector.system->getPluginHandle(FMOD_PLUGINTYPE_DSP, pluginselector.cursor, &pluginhandle);
                ERRCHECK(result);

                result = pluginselector.system->createDSPByPlugin(pluginhandle, &parameterviewer.dsp);
                ERRCHECK(result);

                FMOD_RESULT result = parameterviewer.dsp->getNumParameters(&parameterviewer.numparams);
                ERRCHECK(result);

                parameterviewer.scroll = 0;
            }
        }
        else if (state == PARAMETER_VIEWER)
        {
            state = parameterViewerDo(&parameterviewer);

            if (state == PLUGIN_SELECTOR)
            {
                result = parameterviewer.dsp->release();
                ERRCHECK(result);

                parameterviewer.dsp = 0;
            }
        }

        result = system->update();
        ERRCHECK(result);

        Common_Sleep(INTERFACE_UPDATETIME - 1);
    } while (!Common_BtnPress(BTN_QUIT));

    if (parameterviewer.dsp)
    {
        result = parameterviewer.dsp->release();
        ERRCHECK(result);
    }

    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    Common_Close();

    return 0;
}