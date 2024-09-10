bool PluginInfo::pluginSignInfoIsEqual(const PluginInfo& pluginInfo)
{
	return pluginName    == pluginInfo.getName() &&
	       pluginAuthor  == pluginInfo.getAuthor() &&
	       pluginVersion == pluginInfo.getVersion();
}