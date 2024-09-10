	void RenameDialog::accept ()
	{
		std::shared_ptr<void> guard (nullptr, [this] (void*) { QDialog::accept (); });

		const auto& toRename = GetRenames ();
		if (toRename.isEmpty ())
			return;

		if (QMessageBox::question (this,
				"LMP Graffiti",
				tr ("Are you sure you want to rename %n file(s)?", 0, toRename.size ()),
				QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
			Rename (toRename);
	}