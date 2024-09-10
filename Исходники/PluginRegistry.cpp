void PluginInfo::releaseFactory(std::string key_string)
{
	if(!loaded) return;

	--num_references;
	if(num_references<=0)
	{
		freeLibrary();
	}
}