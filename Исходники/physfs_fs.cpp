IFile FileSystem::open(const UString &path)
{
	TRACE_FN_ARGS1("PATH", path);
	IFile f;

	auto lowerPath = path.toLower();
	if (path != lowerPath)
	{
		LogError("Path \"%s\" contains CAPITAL - cut it out!", path);
	}

	if (!PHYSFS_exists(path.cStr()))
	{
		LogInfo("Failed to find \"%s\"", path);
		LogAssert(!f);
		return f;
	}
	f.f.reset(new PhysfsIFileImpl(path));
	f.rdbuf(dynamic_cast<PhysfsIFileImpl *>(f.f.get()));
	LogInfo("Loading \"%s\" from \"%s\"", path, f.systemPath());
	return f;
}