void
ProjectWindow::AddFolder(entry_ref folderref)
{
	BDirectory dir;
	if (dir.SetTo(&folderref) != B_OK)
		return;
	
	if (strcmp(folderref.name,"CVS") == 0 ||
		strcmp(folderref.name,".svn") == 0 ||
		strcmp(folderref.name,".git") == 0 ||
		strcmp(folderref.name,".hg") == 0)
		return;
	
	dir.Rewind();
	
	entry_ref ref;
	while (dir.GetNextRef(&ref) == B_OK)
	{
		if (BEntry(&ref).IsDirectory())
			AddFolder(ref);
		else
		{
			// Here is where we actually add the file to the project. The name of the folder
			// containing the file will be the name of the file's group. If the group doesn't
			// exist, it will be created at the end of the list, but if it does, we will fake
			// a drop onto the group item to reuse the code path by finding the group and getting
			// its position in the list.
			
			DPath filepath(ref);
			if (filepath.GetExtension() && 
				!( strcmp(filepath.GetExtension(),"cpp") == 0 ||
				strcmp(filepath.GetExtension(),"c") == 0 ||
				strcmp(filepath.GetExtension(),"cc") == 0 ||
				strcmp(filepath.GetExtension(),"cxx") == 0 ||
				strcmp(filepath.GetExtension(),"rdef") == 0 ||
				strcmp(filepath.GetExtension(),"rsrc") == 0) )
				continue;
			
			// Don't bother adding build files from other systems
			if (strcmp(filepath.GetFileName(), "Jamfile") == 0 ||
				strcmp(filepath.GetFileName(), "Makefile") == 0)
				continue;
			
			DPath parent(filepath.GetFolder());
			SourceGroup *group = NULL;
			SourceGroupItem *groupItem = NULL;
			
			fProject->Lock();
			group = fProject->FindGroup(parent.GetFileName());
			
			Lock();
			if (group)
				groupItem = fProjectList->ItemForGroup(group);
			else
			{
				group = fProject->AddGroup(parent.GetFileName());
				groupItem = new SourceGroupItem(group);
				fProjectList->AddItem(groupItem);
				UpdateIfNeeded();
			}
			
			if (groupItem)
			{
				int32 index = fProjectList->IndexOf(groupItem);
				BPoint pt = fProjectList->ItemFrame(index).LeftTop();
				pt.x += 5;
				pt.y += 5;
				
				AddFile(ref,&pt);
			}
			
			Unlock();
				
			fProject->Unlock();
		}
	}
}