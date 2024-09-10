void
NegotiatorPluginManager::Update(const ClassAd &ad)
{
	NegotiatorPlugin *plugin;
	SimpleList<NegotiatorPlugin *> plugins = getPlugins();
	plugins.Rewind();
	while (plugins.Next(plugin)) {
		plugin->update(ad);
	}
}