bool
MSHLanguageMgr::LoadLanguageFiles(const char * pathToFileStub)
{
	if (NULL != fTransFiles) {
		DeleteAllLanguageFilesAndList();
	}

	fTransFiles = new BList();

	// Sanity check.
	if (NULL == fTransFiles) {
		return false;
	}

	bool loadedAtLeastOne = false;

	// Create a list of MSHLanguageFiles, one for each file found at
	// the passed-in location, using the included stub file prefix.
	fFileNameStub = "";
	BString pathAndStub(pathToFileStub);
	BString pathOnly = "";

	// Obtain the path component separately from the file name stub.
	const int32 posOfLastFolderSlash = pathAndStub.FindLast('/');
	if (B_ERROR == posOfLastFolderSlash) {
		// Must be just a filename.
		fFileNameStub = pathAndStub;
	} else {
		pathAndStub.CopyInto(pathOnly, 0 /*sourceOffset*/, posOfLastFolderSlash);
		if (pathAndStub.Length() >= (posOfLastFolderSlash + 1)) {
			pathAndStub.CopyInto(fFileNameStub, (posOfLastFolderSlash + 1), (pathAndStub.Length() - 1));
		}
	}

	if (fFileNameStub.Length() > 0) {

		// Check for a relative path. If relative, then add the app directory to the start.
		if ((pathOnly == "") || (pathOnly.FindFirst('/') > 0)) {
			app_info ai;
			be_app->GetAppInfo(&ai);
			BEntry appEntry(&ai.ref);
			BPath appPathWithLeafName;
			appEntry.GetPath(&appPathWithLeafName);
			BPath appPathOnly;
			appPathWithLeafName.GetParent(&appPathOnly);
			appPathWithLeafName.Unset();

			if (pathOnly.FindLast('/') != (pathOnly.Length() - 1)) {
				pathOnly.Prepend("/");
			}
			pathOnly.Prepend(appPathOnly.Path());
			appPathOnly.Unset();
			appEntry.Unset();			
		}

		if (pathOnly.Length() > 0) {
			// Find all files in the specified directory that have a name beginning
			// with the specified stub.
			char nameBuffer[B_FILE_NAME_LENGTH];
			BDirectory langDir(pathOnly.String());
			BEntry nextEntry;
			while (langDir.GetNextEntry(&nextEntry) == B_OK) {
				if (B_OK == nextEntry.GetName(nameBuffer)) {
					BString nameStr(nameBuffer);
					if (nameStr.FindFirst(fFileNameStub) == 0) {
						// We have a winner! Matching stub on filename (after adding on path)
						nameStr.Prepend("/");
						nameStr.Prepend(pathOnly);
						MSHLanguageFile* newLangFile = new MSHLanguageFile(nameStr.String());
						fTransFiles->AddItem(newLangFile);
						loadedAtLeastOne = true;
					}
				}
				nextEntry.Unset();
			}
		}
	}

	if (!loadedAtLeastOne) {
		DeleteAllLanguageFilesAndList();
	}

	return loadedAtLeastOne;
}