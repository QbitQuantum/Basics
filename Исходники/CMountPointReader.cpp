void CMountPointReader::buildDirectory()
{
	IFileList * list = Parent->createFileList();
	if (!list)
		return;

	const uint32_t size = list->getFileCount();
	for (uint32_t i=0; i < size; ++i)
	{
		io::path full = list->getFullFileName(i);
		full = full.subString(Path.size(), full.size() - Path.size());

		if (!list->isDirectory(i))
		{
			addItem(full, list->getFileOffset(i), list->getFileSize(i), false, RealFileNames.size());
			RealFileNames.push_back(list->getFullFileName(i));
		}
		else
		{
			const io::path rel = list->getFileName(i);
			RealFileNames.push_back(list->getFullFileName(i));

			io::path pwd  = Parent->getWorkingDirectory();
			if (pwd.lastChar() != '/')
				pwd.append('/');
			pwd.append(rel);

			if ( rel != "." && rel != ".." )
			{
				addItem(full, 0, 0, true, 0);
				Parent->changeWorkingDirectoryTo(pwd);
				buildDirectory();
				Parent->changeWorkingDirectoryTo("..");
			}
		}
	}

	list->drop();
}