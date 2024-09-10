void
CollectorPluginManager::Shutdown()
{
	CollectorPlugin *plugin;
	SimpleList<CollectorPlugin *> plugins = getPlugins();
	plugins.Rewind();
	while (plugins.Next(plugin)) {
		plugin->shutdown();
	}
}