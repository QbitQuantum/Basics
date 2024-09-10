void InfoStrView::SetPath (const char *path)
{
	/* Store the given directory path in "itemPath". If the path is that of a file, it normalizes the path
		and gets its parent folder path and stores it in "itemPath"
		TODO: Accept a bool parameter "isFolder" to overcome the problem specified in the "else" part */
	DeAllocPath();
		
	BEntry entry (path, false);				/* Question: Must we traverse the link here ?? */
	if (entry.Exists() == true)
	{
		if (entry.IsFile() || entry.IsSymLink())
		{
			BEntry parentDir;
			entry.GetParent (&parentDir);
			
			BPath dirPath;
			parentDir.GetPath (&dirPath);
			AllocPath (dirPath.Path());
		}
		else								/* Means it's a directory */
		{
			AllocPath (path);
		}
	}
	else									/* Problem: Assume its a file NOT a directory */
	{
		BPath parentPath;
		BPath dirPath (path);
		dirPath.GetParent (&parentPath);
		
		AllocPath (parentPath.Path());
	}
}