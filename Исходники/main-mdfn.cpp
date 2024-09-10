EXPORT m64p_error CALL videoPluginStartup(m64p_dynlib_handle CoreLibHandle, void *Context,
                                   void (*DebugCallback)(void *, int, const char *))
{
    char logMsg[530];
    Logger::getSingleton().initialize(DebugCallback, Context);
    Logger::getSingleton().printMsg("PluginStartup");

    //Read configuration
    if (g_config.initialize())
    {
        g_config.load();
        g_graphicsPlugin.setConfig(g_config.getConfig());
    }

    return M64ERR_SUCCESS;
}