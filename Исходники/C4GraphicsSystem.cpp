bool C4GraphicsSystem::SaveScreenshot(bool fSaveAll, float fSaveAllZoom)
{
	// Find a unique screenshot filename by iterating over all possible names
	// Keep static counter so multiple screenshots in succession do not use same filename even if the background thread hasn't started writing the file yet
	char szFilename[_MAX_PATH+1];
	static int32_t iScreenshotIndex=1;
	const char *strFilePath = NULL;
	do
		sprintf(szFilename,"Screenshot%03i.png",iScreenshotIndex++);
	while (FileExists(strFilePath = Config.AtScreenshotPath(szFilename)));
	bool fSuccess=DoSaveScreenshot(fSaveAll, strFilePath, fSaveAllZoom);
	// log if successful/where it has been stored
	if (!fSuccess)
		LogF(LoadResStr("IDS_PRC_SCREENSHOTERROR"), Config.AtUserDataRelativePath(Config.AtScreenshotPath(szFilename)));
	else
		LogF(LoadResStr("IDS_PRC_SCREENSHOT"), Config.AtUserDataRelativePath(Config.AtScreenshotPath(szFilename)));
	// return success
	return !!fSuccess;
}