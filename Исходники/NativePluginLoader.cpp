void NativePluginLoader::specificUnloadPlugin ( Plugin& plugin )
{
    QString pluginPath = plugin.pluginPath();
    LOG4CXX_DEBUG(logger, "specificUnloadPlugin: " +
                  pluginPath.toStdString());

    try { 
        NativePlugin& nativePlg = dynamic_cast<NativePlugin&>( plugin );
        if ( ! pluginMap.contains( &nativePlg ) ) {
            LOG4CXX_WARN(logger, "plugin doesn't exist: " +
                          pluginPath.toStdString());            
            return;
        }

        DynaLoader* dynaLoader = pluginMap[&nativePlg];
        pluginMap.remove( &nativePlg );
        try { 
            PluginInstanceFiniCall pluginInstanceFiniCall =
                (PluginInstanceFiniCall) dynaLoader->getProcAddress(
                                                   PLUGIN_INSTANCE_FINI_CALL );
            pluginInstanceFiniCall();
        }
        catch ( DynaLoader::AddressException& e ) {
            LOG4CXX_WARN(logger, "plugin can't be correctly unloaded: " + 
                         pluginPath.toStdString() + ", can't find address: "+
                         e.message().toStdString() );
        }       

        delete dynaLoader;

        LOG4CXX_INFO(logger, "plugin unloaded: " +  pluginPath.toStdString());
    }
    catch ( std::exception& ) {
        // Cast exception
        LOG4CXX_WARN(logger, "plugin can't be correctly unloaded: " + 
                     pluginPath.toStdString() + 
                     ", is not a child of base plugin class");
    }
    catch ( ... ) {
        LOG4CXX_ERROR(logger, "plugin can't be loaded: " + 
                      pluginPath.toStdString() + ", unknown exception");
    }
}