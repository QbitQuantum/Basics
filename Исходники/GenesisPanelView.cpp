void PanelView::DeleteDirectory(const char *dirname)
////////////////////////////////////////////////////////////////////////
{
	BDirectory *dir;
	key_info keyinfo;
	
	// Don't delete the parent directory!!!!!!
	if (strlen(dirname)>=3)
	{
		int len = strlen(dirname);
		if (dirname[len-1]=='.' && dirname[len-2]=='.' && dirname[len-3]=='/') return;
	}
		
	dir = new BDirectory(dirname);
	if (dir)
	{
		BEntry entry;
		
		if (dir->GetEntry(&entry)==B_OK)
		{	
			while (dir->GetNextEntry(&entry)==B_OK)			
			{
				get_key_info(&keyinfo);
				if (keyinfo.key_states[0] & 0x40)	// ESC
				{
					beep();
					delete dir;
					return;
				}

				BPath path;
				entry.GetPath(&path);
				
				if (entry.IsDirectory())
					DeleteDirectory(path.Path());

				entry.Remove();
			}
		}
	
		delete dir;
	}
}