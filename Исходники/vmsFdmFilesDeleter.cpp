bool vmsFdmFilesDeleter::DeleteBrowserPluginFiles(std::vector <std::auto_ptr <vmsBrowserPluginFileDeleter> >& vFiles)
{
	bool bOK = true;
	vmsWinOsVersion osver;

	std::vector <vmsKnownBrowsers::Browser> vPluginsToDeleteElevated;

	for (size_t i = 0; i < vFiles.size (); i++)
	{
		vFiles [i]->setOnDeleteErrorHandler (onBrowserPluginFileDeleteError);

		if (vFiles [i]->DeleteFileEx ())
			continue;

		
		if (vFiles [i]->getErrorType () == vmsFileDeleter::NotEnoughRights && 
			osver.isVistaOrHigher () && !IsUserAnAdmin ())
		{
			vPluginsToDeleteElevated.push_back (vFiles [i]->getBrowser ());
			continue;
		}

		bOK = false;
	}

	if (!vPluginsToDeleteElevated.empty ())
	{
		if (!vmsElevatedFdm::o ().InstallIntegration (vPluginsToDeleteElevated, false, true))
			bOK = false;
	}
	
	return bOK;
}