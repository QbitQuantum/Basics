void
TemplateWindow::CheckTemplates(void)
{
	// This checks for the Templates folder in the Paladin application directory
	// and if it doesn't exist or it's empty, we make sure that it exists and
	// at least has empty project templates for each of the four basic types of projects
	
	DPath templatePath(gAppPath.GetFolder());
	templatePath << "Templates";
	
	bool needInit = false;
	if (!BEntry(templatePath.GetFullPath()).Exists())
		needInit = true;
	
	if (!needInit)
	{
		BDirectory dir(templatePath.GetFullPath());
		if (dir.CountEntries() == 0)
			needInit = true;
	}
	
	if (needInit)
	{
		create_directory(templatePath.GetFullPath(),0777);
		
		DPath tpath(templatePath);
		BFile file;
		BString filedata;
		
		tpath.Append("Addon");
		create_directory(tpath.GetFullPath(),0777);
		tpath.Append("TEMPLATEINFO");
		file.SetTo(tpath.GetFullPath(), B_READ_WRITE | B_CREATE_FILE);
		filedata = "TYPE=Shared\n";
		file.Write(filedata.String(),filedata.Length());
		
		tpath = templatePath;
		tpath.Append("Empty Application");
		create_directory(tpath.GetFullPath(),0777);
		tpath.Append("TEMPLATEINFO");
		file.SetTo(tpath.GetFullPath(), B_READ_WRITE | B_CREATE_FILE);
		filedata = "TYPE=Application\n";
		file.Write(filedata.String(),filedata.Length());
		
		tpath = templatePath;
		tpath.Append("Kernel Driver");
		create_directory(tpath.GetFullPath(),0777);
		tpath.Append("TEMPLATEINFO");
		file.SetTo(tpath.GetFullPath(), B_READ_WRITE | B_CREATE_FILE);
		filedata = "TYPE=Driver\n";
		file.Write(filedata.String(),filedata.Length());
		
		tpath = templatePath;
		tpath.Append("Shared Library");
		create_directory(tpath.GetFullPath(),0777);
		tpath.Append("TEMPLATEINFO");
		file.SetTo(tpath.GetFullPath(), B_READ_WRITE | B_CREATE_FILE);
		filedata = "TYPE=Shared\n";
		file.Write(filedata.String(),filedata.Length());
		
		tpath = templatePath;
		tpath.Append("Static Library");
		create_directory(tpath.GetFullPath(),0777);
		tpath.Append("TEMPLATEINFO");
		file.SetTo(tpath.GetFullPath(), B_READ_WRITE | B_CREATE_FILE);
		filedata = "TYPE=Static\n";
		file.Write(filedata.String(),filedata.Length());
		
	}
}