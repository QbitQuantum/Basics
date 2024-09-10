	EntryPath(const BString& directory, const BString& name)
		:
		directory(directory.Length() > 0 ? directory.String() : NULL),
		name(name.String())
	{
	}