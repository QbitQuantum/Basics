void GlobalPreferences_installedApps_remove(const char* appName)
{
	String appNameString = appName;
	for(int i=0; i<installedApps.size(); i++)
	{
		if(appNameString.equals(installedApps.get(i)))
		{
			installedApps.remove(i);
			return;
		}
	}
}