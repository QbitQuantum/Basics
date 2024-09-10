OPStatus InputPlugin::unloadPlugin()
{
    if (OP_ERROR == freeLibrary(_libHandle))
    {
        LOG_FATAL(RSPPlugin) << "Error unloading plugin";
        return OP_ERROR;
    }

    memset(&_pluginInfo, 0, sizeof(_pluginInfo));
    Config = nullptr;
    ControllerCommand = nullptr;
    GetKeys = nullptr;
    ReadController = nullptr;
    CloseLib = nullptr;
    RomOpen = nullptr;
    RomClosed = nullptr;

    return OP_OK;
}