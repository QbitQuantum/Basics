    //---------------------------------------------------------------------
	void FileSystemLayer::prepareUserHome(const Ogre::String& subdir)
	{
		// fill mHomePath
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		WCHAR wpath[MAX_PATH];
		if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PERSONAL|CSIDL_FLAG_CREATE, NULL, 0, wpath)))
			widePathToOgreString(mHomePath, wpath);
#elif OGRE_PLATFORM == OGRE_PLATFORM_WINRT
		widePathToOgreString(mHomePath, Windows::Storage::ApplicationData::Current->LocalFolder->Path->Data());
#endif

		if(!mHomePath.empty())
		{
			// create Ogre subdir
			mHomePath += "\\Ogre\\";
			if (!createDirectory(mHomePath))
			{
				// couldn't create directory, fall back to current working dir
				mHomePath.clear();
			}
			else
			{
				mHomePath += subdir + '\\';
				// create release subdir
				if (!createDirectory(mHomePath))
				{
					// couldn't create directory, fall back to current working dir
					mHomePath.clear();
				}
			}
		}
	}