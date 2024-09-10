CIMIPlugin*
CIMIPluginManager::createPlugin(std::string filename,
                                TPluginTypeEnum pluginType)
{
    std::stringstream error;
    clearLastError();

    switch (pluginType) {
    case CIMI_PLUGIN_PYTHON:
        return new CIMIPythonPlugin(filename);
    case CIMI_PLUGIN_UNKNOWN:
    default:
        error << "Cannot detect type for " << filename;
        setLastError(error.str());
        return NULL;
    }
}