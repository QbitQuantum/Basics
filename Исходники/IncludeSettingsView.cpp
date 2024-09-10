void
IncludeSettingsView::AddRefsToList(BListView* list, BMessage* message, bool relative = false)
{
	//XXX - it is possible for now to select only one directory each time.
	entry_ref ref;
	BEntry entry;
	BPath path;
	BString pathString;
	status_t err;
	int32 ref_num;
	bool relpath = false;
	ref_num = 0;
	//find boolean in the message
	err =  message->FindBool("relpath", &relpath);
	if (err != B_OK) {
		DPRINT("IncludeSettingsView::AddRefsToList: boolean not found");
	}

	//add this entry to the list view
	do {
		if ( (err = message->FindRef("refs", ref_num, &ref)) != B_OK ) {
			return;
		}
		entry.SetTo(&ref, true);
		//we return if for some strange reason the entry is unavailable
		if (entry.InitCheck() != B_OK) return;
		entry.GetPath(&path);
		//XXX - if "relative" convert path
		DPRINT("IncludeSettingsView::AddRefsToList: entry name = " << path.Path());
		//convert path to relative if requested
		if (relpath) {
			//find the window we are attached to...
			DPRINT("IncludeSettingsView::AddRefsToList: add relative path");
			TargetConfig* c = ((TargetSettingsWin*) Window() )->TConfig();
			assert(c != NULL); //we *must* be attached to a window here
			c->RelPathToWorkingDir(path.Path(), &pathString);
		} else {
			DPRINT("IncludeSettingsView::AddRefsToList: add absolute path");
			pathString = path.Path();
		}
		list->AddItem(new BStringItem(pathString.String()));
		//tell the window that this view has changed
		CommunicateChanges();

		ref_num++;
	} while (1);	

}