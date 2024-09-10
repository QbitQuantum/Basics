void CL_FileDialog_Generic::refresh()
{
	CL_DirectoryScanner scanner;
	unsigned int i;
	bool parent = false;

	treeview_files->clear();
	Directories.clear();
	Files.clear();

	scanner.scan (".", "*");
	while (scanner.next())
	{
		std::string file = scanner.get_name();

		if(file == "." || file == "..")
			parent = true;
		else 
		{
			if (!scanner.is_hidden() || show_hidden == true)
			{	
				if (scanner.is_directory())
				{
					Directories.push_back(FileInfo(file, scanner.is_directory(), scanner.is_readable(), scanner.is_writable(), scanner.is_hidden(), 0));
				}
			}
		}
	}
	
	scanner.scan (".", filter);
	while (scanner.next())
	{
		std::string file = scanner.get_name();

		if(file == "." || file == "..")
			parent = true;
		else 
		{
			if (!scanner.is_hidden() || show_hidden == true)
			{	
				if (!scanner.is_directory())
				{
					Files.push_back(FileInfo(file, scanner.is_directory(), scanner.is_readable(), scanner.is_writable(), scanner.is_hidden(), scanner.get_size()));
				}
			}
		}
	}

	std::sort(Directories.begin(), Directories.end(), CL_FileDialog_Generic::sort);
	std::sort(Files.begin(), Files.end(), CL_FileDialog_Generic::sort);

	for(i = 0; i < Directories.size(); i++)
		treeview_files->insert_item(Directories[i].name, "", "Directory");

	for(i = 0; i < Files.size(); i++)
	{
		std::string AppendName = Files[i].name;
		int index = AppendName.rfind('.');
		std::string file_size;
		
		file_size = CL_String::format("%1 bytes", Files[i].size);

		if(Files[i].size > 1024)
			file_size = CL_String::format("%1 KB", Files[i].size / 1024);

		if(Files[i].size > 1024 * 1024)
			file_size = CL_String::format("%1 MB", Files[i].size / (1024 * 1024));


		if(index >= 0)
		{
			AppendName = AppendName.substr(index);
			AppendName = CL_String::format("%1 file", AppendName);
		}

		treeview_files->insert_item(Files[i].name, file_size, AppendName);
	}

	button_parent->enable(parent);
}