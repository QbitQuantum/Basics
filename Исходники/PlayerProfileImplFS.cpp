//------------------------------------------------------------------------
bool CPlayerProfileImplFSDir::LoginUser(SUserEntry* pEntry)
{
	// lookup stored profiles of the user (pEntry->userId) and fill in the pEntry->profileDesc
	// vector 
	pEntry->profileDesc.clear();

	// scan directory for profiles

	string path;
	InternalMakeFSPath(pEntry, "", path);  // no profile name -> only path

	std::multimap<time_t, SLocalProfileInfo> profiles;

	ICryPak * pCryPak = gEnv->pCryPak;
	_finddata_t fd;

	path.TrimRight("/\\");
	string search = path + "/*.*";

	IPlatformOS* pOS = GetISystem()->GetPlatformOS();
	IPlatformOS::IFileFinderPtr fileFinder = pOS->GetFileFinder(IPlatformOS::Unknown_User);
	intptr_t handle = fileFinder->FindFirst(search.c_str(), &fd);
	if (handle != -1)
	{
		do
		{
			if (strcmp(fd.name, ".") == 0 || strcmp(fd.name, "..") == 0)
				continue;

			if (fd.attrib & _A_SUBDIR)
			{
				// profile name = folder name
				// but make sure there is a profile.xml in it
				string filename = path + "/" + fd.name;
				filename += "/" ;
				filename += "profile.xml";
				XmlNodeRef rootNode = LoadXMLFile(filename.c_str());

				// see if the root tag is o.k.
				if (rootNode && stricmp(rootNode->getTag(), PROFILE_ROOT_TAG) == 0)
				{
					string profileName = fd.name;
					if (rootNode->haveAttr(PROFILE_NAME_TAG))
					{
						const char* profileHumanName = rootNode->getAttr(PROFILE_NAME_TAG);
						if (profileHumanName!=0 && stricmp(profileHumanName, profileName) == 0)
						{
							profileName = profileHumanName;
						}
					}
					time_t time = NULL;
					if (rootNode->haveAttr(PROFILE_LAST_PLAYED))
					{
						rootNode->getAttr(PROFILE_LAST_PLAYED, time);
					}
					SLocalProfileInfo info(profileName);
					info.SetLastLoginTime(time);
					profiles.insert(std::make_pair(time, info));
				}
				else
				{
					GameWarning("CPlayerProfileImplFSDir::LoginUser: Profile '%s' of User '%s' seems to exists but is invalid (File '%s). Skipped", fd.name, pEntry->userId.c_str(), filename.c_str());
				}
			}
		} while ( fileFinder->FindNext( handle, &fd ) >= 0 );

		fileFinder->FindClose( handle );
	}

	// Insert in most recently played order
	std::multimap<time_t, SLocalProfileInfo>::const_reverse_iterator itend = profiles.rend();
	for(std::multimap<time_t, SLocalProfileInfo>::const_reverse_iterator it = profiles.rbegin(); it != itend; ++it)
		pEntry->profileDesc.push_back(it->second);

	return true;
}