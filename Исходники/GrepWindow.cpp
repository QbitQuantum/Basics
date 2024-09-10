void
GrepWindow::_SetWindowTitle()
{
	BEntry entry(&fModel->fDirectory, true);
	BString title;
	if (entry.InitCheck() == B_OK) {
		BPath path;
		if (entry.GetPath(&path) == B_OK) {
			if (fOldPattern.Length()) {
				title = B_TRANSLATE("%appname% : %path% : %searchtext%");
				title.ReplaceAll("%searchtext%", fOldPattern.String());
			} else
				title = B_TRANSLATE("%appname% : %path%");

			title.ReplaceAll("%appname%", B_TRANSLATE(APP_NAME));
			title.ReplaceAll("%path%", path.Path());
		}
	}

	if (!title.Length())
		title = B_TRANSLATE(APP_NAME);

	SetTitle(title.String());
}