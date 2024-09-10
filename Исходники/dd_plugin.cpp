static int loadPlugin(void* libraryFile, const char* fileName, const char* pluginPath, void* param)
{
    Library* plugin;
    PluginHandle* handle;
    void (*initializer)(void);
    filename_t name;
    pluginid_t plugId;

    DENG_UNUSED(libraryFile); // this is not C++...
    DENG_UNUSED(param);

    DENG_ASSERT(fileName && fileName[0]);
    DENG_ASSERT(pluginPath && pluginPath[0]);

    if(strcasestr("/bin/audio_", pluginPath))
    {
        // Do not touch audio plugins at this point.
        return true;
    }

    plugin = Library_New(pluginPath);
    if(!plugin)
    {
        Con_Message("  loadPlugin: Did not load \"%s\" (%s).", pluginPath, Library_LastError());
        return 0; // Continue iteration.
    }

    if(!strcmp(Library_Type(plugin), "deng-plugin/audio"))
    {
        // Audio plugins will be loaded later, on demand.
        Library_Delete(plugin);
        return 0;
    }

    initializer = de::function_cast<void (*)()>(Library_Symbol(plugin, "DP_Initialize"));
    if(!initializer)
    {
        DEBUG_Message(("  loadPlugin: \"%s\" does not export entrypoint DP_Initialize, ignoring.\n", pluginPath));

        // Clearly not a Doomsday plugin.
        Library_Delete(plugin);
        return 0; // Continue iteration.
    }

    // Assign a handle and ID to the plugin.
    handle = findFirstUnusedPluginHandle();
    plugId = handle - hInstPlug + 1;
    if(!handle)
    {
        DEBUG_Message(("  loadPlugin: Failed acquiring new handle for \"%s\", ignoring.\n", pluginPath));

        Library_Delete(plugin);
        return 0; // Continue iteration.
    }

    // This seems to be a Doomsday plugin.
    _splitpath(pluginPath, NULL, NULL, name, NULL);
    Con_Message("  (id:%i) %s", plugId, name);

    *handle = plugin;

    DD_SetActivePluginId(plugId);
    initializer();
    DD_SetActivePluginId(0);

    return 0; // Continue iteration.
}