void
MediaConverterWindow::_SetOutputFolder(BEntry entry)
{
	BPath path;
	entry.GetPath(&path);
	fOutputFolder->SetText(path.Path());
	fOutputFolder->ResizeToPreferred();
	fOutputDir.SetTo(path.Path());
}