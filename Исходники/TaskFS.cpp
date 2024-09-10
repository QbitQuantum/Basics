status_t TaskFS::TaskToFile(Task *theTask, bool overwrite)
{
	BFile		taskFile;
	BEntry		entry;
	status_t	err;
	TaskList	*tskLst	= theTask->GetTaskList();
	
	BDirectory	dir		= BDirectory();

	bool	completed	= theTask->IsCompleted();
	uint32	priority	= theTask->Priority();
	time_t	due			= theTask->DueTime();


	//first find directory.. then create files in this directory
	if (tskLst!=NULL)
		dir.SetTo(&tasksDir,tskLst->Name());
	else
		dir.SetTo(&tasksDir,".");

	
	//first check if the File already exists..
	//if not and overwrite is on check the ids..
	// and search for the correspondending file...

	if (dir.FindEntry(theTask->Title(),&entry) == B_OK) {
		taskFile.SetTo((const BEntry*)&entry,B_READ_WRITE);
		err = B_OK;
	} 
	else {
		entry_ref *ref= FileForId(theTask);
		if (ref==NULL){
			dir.CreateFile(theTask->Title(),&taskFile,overwrite);
			dir.FindEntry(theTask->Title(),&entry);
		}
		else {
			entry.SetTo(ref);
			taskFile.SetTo((const BEntry*)ref,B_READ_WRITE);
		}
	}
	if (taskFile.InitCheck() == B_OK){
		taskFile.WriteAttr("META:completed",B_BOOL_TYPE, 0, &completed, sizeof(completed));
		entry.Rename(theTask->Title());
		taskFile.WriteAttrString("META:tasks",new BString(theTask->GetTaskList()->ID()));
		taskFile.WriteAttrString("META:notes",new BString(theTask->Notes()));
		taskFile.WriteAttr("META:priority", B_UINT32_TYPE, 0, &priority, sizeof(priority));
		taskFile.WriteAttr("META:due", B_TIME_TYPE, 0, &due, sizeof(due));
		taskFile.WriteAttrString("META:task_id",  new BString(theTask->ID()));
		taskFile.WriteAttrString("META:task_url",new BString(theTask->URL()));
	}
	else
		err=B_ERROR;
	return err; 
}