void PecoApp::DoIt() {

	if (NothingToDo()) return;
	
	FileListItem	*ListItem;
	
	BAlert	*myAlert	= new BAlert(NULL, MESSAGE_REALLY_DOIT, STR_CONTINUE, STR_CANCEL);
	if (myAlert->Go() == 1) return;
		for (int32 i = 0; (ListItem = (FileListItem *)fListView->ItemAt(i)) != NULL; i++ ) {
		if (ListItem->fErrorStatus == 1 ) {
			BAlert	*myAlert	= new BAlert(NULL, MESSAGE_WILL_HAVE_PROBS, STR_CONTINUE, STR_CANCEL);
			if (myAlert->Go() == 1) return;
			break;
		}
	}

	bool 	noerror = true, nomoreerrors=false, canceled=false;

	fWindow->Lock();
	fStatusBar->SetText(STATUS_RENAMING);
	fStatusBar->SetMaxValue(fList->CountItems());

	BButton		*okButton = (BButton *)fWindow->FindView("DoIt");
	okButton->SetEnabled(false);
	
	BTextControl* 	pfadView = (BTextControl *)fWindow->FindView("pfadView");
	BString	Pfad(pfadView->Text());
	fWindow->Unlock();
	
	BString	AlterName, NeuerName;
	BEntry	Datei;
	
	for (int32 i = 0; (ListItem = (FileListItem *)fListView->ItemAt(i)) != NULL; i++ ) {
		fWindow->Lock();
		fStatusBar->Update(1);
		fWindow->Unlock();
		if (canceled) { ListItem->fErrorStatus=0; continue; }
		if (ListItem->fNewName.String() != "" ) {
			AlterName = Pfad; AlterName.Append("/").Append(ListItem->fName);
			NeuerName = Pfad; NeuerName.Append("/").Append(ListItem->fNewName);
			Datei.SetTo(AlterName.String());
			if ( Datei.Rename(NeuerName.String()) != B_OK ) {
				ListItem->fErrorStatus=1;
				fWindow->Lock();
				fListView->InvalidateItem(i);
				fWindow->Unlock();

				if (!nomoreerrors) {
					noerror = false;

					BString		ErrorMessage(MESSAGE_HAVE_PROBLEM);
					ErrorMessage.ReplaceFirst("%1", ListItem->fName.String());
					ErrorMessage.ReplaceFirst("%2", ListItem->fNewName.String());
					
					BAlert	*myAlert	= new BAlert(NULL, ErrorMessage.String(), STR_CANCEL, STR_CONTINUE, STR_CONTINUE_WO_MSG, B_WIDTH_AS_USUAL, B_WARNING_ALERT);

					int32	result = myAlert->Go();
					if (result == 0) { canceled = true; continue; }
					if (result == 2) nomoreerrors = true;
				}
				
			} else {
			
				fWindow->Lock();
				ListItem->SetName(ListItem->fNewName);
				ListItem->SetNewName("");
				fListView->InvalidateItem(i);
				fWindow->Unlock();

			}
		}
	}

//	NoRenamer();

	fWindow->Lock();
	fStatusBar->Reset(STATUS_STATUS);
	fWindow->Unlock();

	if (noerror) MakeList();
	else {
		fStatusBar->SetText(STATUS_DIDIT_BAD);

		BAlert	*myAlert	= new BAlert(NULL, MESSAGE_MARKED_FILES, STR_OK);
		myAlert->Go();
	}
	
}