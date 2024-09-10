u32 MetaFileSystem::OpenFile(std::string filename, FileAccess access)
{
	std::string of;
	IFileSystem *system;
	if (MapFilePath(filename, of, &system))
	{
		return system->OpenFile(of, access);
	}
	else
	{
		return 0;
	}
}