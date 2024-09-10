bool CHalfLife2::KVLoadFromFile(KeyValues *kv, IBaseFileSystem *filesystem, const char *resourceName, const char *pathID)
{
#if defined METAMOD_PLAPI_VERSION
	if (g_SMAPI->GetSourceEngineBuild() == SOURCE_ENGINE_ORIGINAL)
#else
	if (strcasecmp(g_SourceMod.GetGameFolderName(), "ship") == 0)
#endif
	{
		Assert(filesystem);
#ifdef _MSC_VER
		Assert(_heapchk() == _HEAPOK);
#endif

		FileHandle_t f = filesystem->Open(resourceName, "rb", pathID);
		if (!f)
			return false;

		// load file into a null-terminated buffer
		int fileSize = filesystem->Size(f);
		char *buffer = (char *)MemAllocScratch(fileSize + 1);

		Assert(buffer);

		filesystem->Read(buffer, fileSize, f); // read into local buffer

		buffer[fileSize] = 0; // null terminate file as EOF

		filesystem->Close( f );	// close file after reading

		bool retOK = kv->LoadFromBuffer( resourceName, buffer, filesystem );

		MemFreeScratch();

		return retOK;
	}
	else
	{
		return kv->LoadFromFile(filesystem, resourceName, pathID);
	}
}