status_t
DirectoryView::OpenDirectory(const Entry* dir)
{
	if (! dir->IsDirectory()) {
		return B_ERROR;
	}

	// stop node watcher
	stop_watching(this);

	// clear entry data and listview
	mListView->DeleteAllItems();
 	entryList_.DeleteAllItems();
	if (entry_) {
		delete entry_;
		entry_ = NULL;
	}
	if (parent_) {
		delete parent_;
		parent_ = NULL;
	}
	UpdateStatus();

	// set current directory
	entry_ = new Directory(*(Directory*)dir);

	// get parent directory
	BEntry bentry;
	if (entry_->GetBEntry(&bentry) == B_OK) {
		BEntry parent;
		if (bentry.GetParent(&parent) == B_OK) {
			parent_ = new Directory(parent);
		}
	}

	// get directory entry
	ListVisitor* lv1 = new ListVisitor(*entry_, &entryList_);
	lv1->Go();
	delete lv1;

	// show directory entry
	if (parent_ != NULL) {
		mListView->AddItem(new EntryListItem(parent_, EntryListItem::ENTRY_IS_PARENT));
	}
	mListView->AddEntryList((BList*) &entryList_);
	mListView->DoSort();
	if (mListView->CountItems() > 0)
		mListView->Select(0);
	UpdateStatus();

	// start node watcher
	if (bentry.InitCheck() == B_OK) {
		node_ref nref;
		bentry.GetNodeRef(&nref);
		watch_node(&nref, B_WATCH_ALL, this);
	}

	return B_OK;
}