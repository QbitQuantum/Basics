void FProjectManager::GetEnabledPlugins(TArray<FString>& OutPluginNames) const
{
	// Get the default list of plugin names
	GetDefaultEnabledPlugins(OutPluginNames, true);

	// Modify that with the list of plugins in the project file
	const FProjectDescriptor *Project = GetCurrentProject();
	if(Project != NULL)
	{
		for(const FPluginReferenceDescriptor& Plugin: Project->Plugins)
		{
			if(Plugin.IsEnabledForPlatform(FPlatformMisc::GetUBTPlatform()))
			{
				OutPluginNames.AddUnique(Plugin.Name);
			}
			else
			{
				OutPluginNames.Remove(Plugin.Name);
			}
		}
	}
}