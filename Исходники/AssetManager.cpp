	bool AssetManager::loadResourceFolder(const gfs::Path& folder)
	{
		if(!folder)
		{
			Logger::get() << "[ERROR]: Could not read folder: \"" << folder << "\"\n";
			return false;
		}

		gfs::PathContents resources = gfs::contents(folder);
		
		for(auto& p : resources)
		{
			if(p.type() == gfs::Path::Type::Directory)
			{
				loadResourceFolder(p);
			}
			else if(p.type() == gfs::Path::Type::File)
			{
				loadResource(p);
			}
		}

		return true;
	}