bool ModuleManager::Load(const std::string& filename, bool defer)
{
	/* Don't allow people to specify paths for modules, it doesn't work as expected */
	if (filename.find('/') != std::string::npos)
		return false;

	char modfile[MAXBUF];
	snprintf(modfile,MAXBUF,"%s/%s",ServerInstance->Config->ModPath.c_str(),filename.c_str());

	if (!ServerConfig::FileExists(modfile))
	{
		LastModuleError = "Module file could not be found: " + filename;
		ServerInstance->Logs->Log("MODULE", LOG_DEFAULT, LastModuleError);
		return false;
	}

	if (Modules.find(filename) != Modules.end())
	{
		LastModuleError = "Module " + filename + " is already loaded, cannot load a module twice!";
		ServerInstance->Logs->Log("MODULE", LOG_DEFAULT, LastModuleError);
		return false;
	}

	Module* newmod = NULL;
	DLLManager* newhandle = new DLLManager(modfile);

	try
	{
		newmod = newhandle->CallInit();

		if (newmod)
		{
			newmod->ModuleSourceFile = filename;
			newmod->ModuleDLLManager = newhandle;
			newmod->dying = false;
			Modules[filename] = newmod;
			std::string version = newhandle->GetVersion();
			if (defer)
			{
				ServerInstance->Logs->Log("MODULE", LOG_DEFAULT,"New module introduced: %s (Module version %s)",
					filename.c_str(), version.c_str());
			}
			else
			{
				newmod->init();

				Version v = newmod->GetVersion();
				ServerInstance->Logs->Log("MODULE", LOG_DEFAULT,"New module introduced: %s (Module version %s)%s",
					filename.c_str(), version.c_str(), (!(v.Flags & VF_VENDOR) ? " [3rd Party]" : " [Vendor]"));
			}
		}
		else
		{
			LastModuleError = "Unable to load " + filename + ": " + newhandle->LastError();
			ServerInstance->Logs->Log("MODULE", LOG_DEFAULT, LastModuleError);
			delete newhandle;
			return false;
		}
	}
	catch (CoreException& modexcept)
	{
		// failure in module constructor
		if (newmod)
		{
			DoSafeUnload(newmod);
			ServerInstance->GlobalCulls.AddItem(newhandle);
		}
		else
			delete newhandle;
		LastModuleError = "Unable to load " + filename + ": " + modexcept.GetReason();
		ServerInstance->Logs->Log("MODULE", LOG_DEFAULT, LastModuleError);
		return false;
	}

	this->ModCount++;
	if (defer)
		return true;

	FOREACH_MOD(I_OnLoadModule,OnLoadModule(newmod));
	/* We give every module a chance to re-prioritize when we introduce a new one,
	 * not just the one thats loading, as the new module could affect the preference
	 * of others
	 */
	for(int tries = 0; tries < 20; tries++)
	{
		prioritizationState = tries > 0 ? PRIO_STATE_LAST : PRIO_STATE_FIRST;
		for (std::map<std::string, Module*>::iterator n = Modules.begin(); n != Modules.end(); ++n)
			n->second->Prioritize();

		if (prioritizationState == PRIO_STATE_LAST)
			break;
		if (tries == 19)
			ServerInstance->Logs->Log("MODULE", LOG_DEFAULT, "Hook priority dependency loop detected while loading " + filename);
	}

	ServerInstance->ISupport.Build();
	return true;
}