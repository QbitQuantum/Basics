VfsPath CColladaManager::GetLoadableFilename(const VfsPath& pathnameNoExtension, FileType type)
{
	std::wstring extn;
	switch (type)
	{
	case PMD: extn = L".pmd"; break;
	case PSA: extn = L".psa"; break;
		// no other alternatives
	}

	/*

	If there is a .dae file:
		* Calculate a hash to identify it.
		* Look for a cached .pmd file matching that hash.
		* If it exists, load it. Else, convert the .dae into .pmd and load it.
	Otherwise, if there is a (non-cache) .pmd file:
		* Load it.
	Else, fail.

	The hash calculation ought to be fast, since normally (during development)
	the .dae file will exist but won't have changed recently and so the cache
	would be used. Hence, just hash the file's size, mtime, and the converter
	version number (so updates of the converter can cause regeneration of .pmds)
	instead of the file's actual contents.

	TODO (maybe): The .dae -> .pmd conversion may fail (e.g. if the .dae is
	invalid or unsupported), but it may take a long time to start the conversion
	then realise it's not going to work. That will delay the loading of the game
	every time, which is annoying, so maybe it should cache the error message
	until the .dae is updated and fixed. (Alternatively, avoid having that many
	broken .daes in the game.)

	*/

	// (TODO: the comments and variable names say "pmd" but actually they can
	// be "psa" too.)

	VfsPath dae(pathnameNoExtension.ChangeExtension(L".dae"));
	if (! VfsFileExists(dae))
	{
		// No .dae - got to use the .pmd, assuming there is one
		return pathnameNoExtension.ChangeExtension(extn);
	}

	// There is a .dae - see if there's an up-to-date cached copy

	FileInfo fileInfo;
	if (g_VFS->GetFileInfo(dae, &fileInfo) < 0)
	{
		// This shouldn't occur for any sensible reasons
		LOGERROR(L"Failed to stat DAE file '%ls'", dae.string().c_str());
		return VfsPath();
	}

	// Build a struct of all the data we want to hash.
	// (Use ints and not time_t/off_t because we don't care about overflow
	// but do care about the fields not being 64-bit aligned)
	// (Remove the lowest bit of mtime because some things round it to a
	// resolution of 2 seconds)
#pragma pack(push, 1)
	struct { int version; int mtime; int size; } hashSource
		= { COLLADA_CONVERTER_VERSION, (int)fileInfo.MTime() & ~1, (int)fileInfo.Size() };
	cassert(sizeof(hashSource) == sizeof(int) * 3); // no padding, because that would be bad
#pragma pack(pop)

	// Calculate the hash, convert to hex
	u32 hash = fnv_hash(static_cast<void*>(&hashSource), sizeof(hashSource));
	wchar_t hashString[9];
	swprintf_s(hashString, ARRAY_SIZE(hashString), L"%08x", hash);
	std::wstring extension(L"_");
	extension += hashString;
	extension += extn;

	// realDaePath_ is "[..]/mods/whatever/art/meshes/whatever.dae"
	OsPath realDaePath_;
	Status ret = g_VFS->GetRealPath(dae, realDaePath_);
	ENSURE(ret == INFO::OK);
	wchar_t realDaeBuf[PATH_MAX];
	wcscpy_s(realDaeBuf, ARRAY_SIZE(realDaeBuf), realDaePath_.string().c_str());
	std::replace(realDaeBuf, realDaeBuf+ARRAY_SIZE(realDaeBuf), '\\', '/');
	const wchar_t* realDaePath = wcsstr(realDaeBuf, L"mods/");

	// cachedPmdVfsPath is "cache/mods/whatever/art/meshes/whatever_{hash}.pmd"
	VfsPath cachedPmdVfsPath = VfsPath("cache") / realDaePath;
	cachedPmdVfsPath = cachedPmdVfsPath.ChangeExtension(extension);

	// If it's not in the cache, we'll have to create it first
	if (! VfsFileExists(cachedPmdVfsPath))
	{
		if (! m->Convert(dae, cachedPmdVfsPath, type))
			return L""; // failed to convert
	}

	return cachedPmdVfsPath;
}