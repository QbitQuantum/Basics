void PProjectWindow::NameChanged()
{
	inherited::NameChanged();
	if (EntryRef())
	{
		BEntry e;
		BPath p;
		FailOSErr(e.SetTo(EntryRef()));
		FailOSErr(e.GetPath(&p));
		fStatus->SetPath(p.Path());
		AddRecent(p.Path());
	}
}