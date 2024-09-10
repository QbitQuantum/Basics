bool InspIRCd::LoadModule(const char* filename)
{
	/* Do we have a glob pattern in the filename?
	 * The user wants to load multiple modules which
	 * match the pattern.
	 */
	if (strchr(filename,'*') || (strchr(filename,'?')))
	{
		int n_match = 0;
		DIR* library = opendir(Config->ModPath);
		if (library)
		{
			/* Try and locate and load all modules matching the pattern */
			dirent* entry = NULL;
			while ((entry = readdir(library)))
			{
				if (this->MatchText(entry->d_name, filename))
				{
					if (!this->LoadModule(entry->d_name))
						n_match++;
				}
			}
			closedir(library);
		}
		/* Loadmodule will now return false if any one of the modules failed
		 * to load (but wont abort when it encounters a bad one) and when 1 or
		 * more modules were actually loaded.
		 */
		return (n_match > 0);
	}

	char modfile[MAXBUF];
	snprintf(modfile,MAXBUF,"%s/%s",Config->ModPath,filename);
	std::string filename_str = filename;

	if (!ServerConfig::DirValid(modfile))
	{
		this->Log(DEFAULT,"Module %s is not within the modules directory.",modfile);
		snprintf(MODERR,MAXBUF,"Module %s is not within the modules directory.",modfile);
		return false;
	}
	if (ServerConfig::FileExists(modfile))
	{

		for (unsigned int j = 0; j < Config->module_names.size(); j++)
		{
			if (Config->module_names[j] == filename_str)
			{
				this->Log(DEFAULT,"Module %s is already loaded, cannot load a module twice!",modfile);
				snprintf(MODERR,MAXBUF,"Module already loaded");
				return false;
			}
		}
		Module* m = NULL;
		ircd_module* a = NULL;
		try
		{
			a = new ircd_module(this, modfile);
			factory[this->ModCount+1] = a;
			if (factory[this->ModCount+1]->LastError())
			{
				this->Log(DEFAULT,"Unable to load %s: %s",modfile,factory[this->ModCount+1]->LastError());
				snprintf(MODERR,MAXBUF,"Loader/Linker error: %s",factory[this->ModCount+1]->LastError());
				return false;
			}
			if ((long)factory[this->ModCount+1]->factory != -1)
			{
				m = factory[this->ModCount+1]->factory->CreateModule(this);

				Version v = m->GetVersion();

				if (v.API != API_VERSION)
				{
					delete m;
					this->Log(DEFAULT,"Unable to load %s: Incorrect module API version: %d (our version: %d)",modfile,v.API,API_VERSION);
					snprintf(MODERR,MAXBUF,"Loader/Linker error: Incorrect module API version: %d (our version: %d)",v.API,API_VERSION);
					return false;
				}
				else
				{
					this->Log(DEFAULT,"New module introduced: %s (API version %d, Module version %d.%d.%d.%d)%s", filename, v.API, v.Major, v.Minor, v.Revision, v.Build, (!(v.Flags & VF_VENDOR) ? " [3rd Party]" : " [Vendor]"));
				}

				modules[this->ModCount+1] = m;
				/* save the module and the module's classfactory, if
				 * this isnt done, random crashes can occur :/ */
				Config->module_names.push_back(filename);

				char* x = &Config->implement_lists[this->ModCount+1][0];
				for(int t = 0; t < 255; t++)
					x[t] = 0;

				modules[this->ModCount+1]->Implements(x);

				for(int t = 0; t < 255; t++)
					Config->global_implementation[t] += Config->implement_lists[this->ModCount+1][t];
			}
			else
			{
				this->Log(DEFAULT,"Unable to load %s",modfile);
				snprintf(MODERR,MAXBUF,"Factory function failed: Probably missing init_module() entrypoint.");
				return false;
			}
		}
		catch (CoreException& modexcept)
		{
			this->Log(DEFAULT,"Unable to load %s: %s",modfile,modexcept.GetReason());
			snprintf(MODERR,MAXBUF,"Factory function of %s threw an exception: %s", modexcept.GetSource(), modexcept.GetReason());
			return false;
		}
	}
	else
	{
		this->Log(DEFAULT,"InspIRCd: startup: Module Not Found %s",modfile);
		snprintf(MODERR,MAXBUF,"Module file could not be found");
		return false;
	}
	this->ModCount++;
	FOREACH_MOD_I(this,I_OnLoadModule,OnLoadModule(modules[this->ModCount],filename_str));
	// now work out which modules, if any, want to move to the back of the queue,
	// and if they do, move them there.
	std::vector<std::string> put_to_back;
	std::vector<std::string> put_to_front;
	std::map<std::string,std::string> put_before;
	std::map<std::string,std::string> put_after;
	for (unsigned int j = 0; j < Config->module_names.size(); j++)
	{
		if (modules[j]->Prioritize() == PRIORITY_LAST)
			put_to_back.push_back(Config->module_names[j]);
		else if (modules[j]->Prioritize() == PRIORITY_FIRST)
			put_to_front.push_back(Config->module_names[j]);
		else if ((modules[j]->Prioritize() & 0xFF) == PRIORITY_BEFORE)
			put_before[Config->module_names[j]] = Config->module_names[modules[j]->Prioritize() >> 8];
		else if ((modules[j]->Prioritize() & 0xFF) == PRIORITY_AFTER)
			put_after[Config->module_names[j]] = Config->module_names[modules[j]->Prioritize() >> 8];
	}