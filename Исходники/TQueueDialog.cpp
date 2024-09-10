//---------------------------------------------------------------------
//	HandleDirectory
//---------------------------------------------------------------------
//	iterate through the directory and pass the resulting
//	refs and attempt to add the resulting file
//
status_t TQueueDialog::HandleDirectory(entry_ref &ref, struct stat &st, BDirectory &dir) 
{
	struct stat s; 
	BEntry entry; 
	
	dir.Rewind();
	while (true)
	{
		if (dir.GetNextEntry(&entry) == B_OK)
		{
			entry.GetStat(&s);
			
			entry_ref eRef;
			entry.GetRef(&eRef);
//			HandleFile(eRef, s);
			EvaluateRef(eRef);
		} else
			break;
	}
		

	return B_ERROR;
}