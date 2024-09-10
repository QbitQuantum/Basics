status_t ImmersiveVideoWindow::Save(BMessage *message) {
	entry_ref ref;		// For the directory to save into
	status_t err;		// For the return code
	const char *name;	// For the filename
	BPath path;		// For the pathname
	BEntry entry;		// Used to make the path
	FILE *f;		// Standard Posix file


	// If a NULL is passed for the message pointer, use
	// the value we've cached; this lets us do saves without
	// thinking.
	
	if (!message) {
		message = savemessage;
		if (!message) {
			return B_ERROR;
		}
	}
	
	// Peel the entry_ref and name of the directory and
	// file out of the message.
	if ((err=message->FindRef("directory", &ref)) != B_OK) {
		return err;
	}
	if ((err=message->FindString("name", &name)) != B_OK) {
		return err;
	}
	
	// Take the directory and create a pathname out of it
	
	if ((err=entry.SetTo(&ref)) != B_OK) {
		return err;
	}
	entry.GetPath(&path);		// Create a pathname for the directory
	path.Append(name);			// Tack on the filename
	
	// Now we can save the file.
	
	if (!(f = fopen(path.Path(), "w"))) {
		return B_ERROR;
	}
	
	//err = fwrite(textview->Text(), 1, textview->TextLength(), f);
	fclose(f);
	if (err >= 0) {
		SetTitle(name);
		saveitem->SetEnabled(true);
		if (savemessage != message) {
			delete savemessage;
			savemessage = new BMessage(*message);
		}
	}
	return err;
}