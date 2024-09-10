static void Error(BView *view, status_t status, bool unlock=false)
{
	BAlert *alert;
	if (view && unlock)
		view->UnlockLooper();
	BString s(strerror(status));
	alert = new BAlert("Error", s.String(), "OK");
	alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
	alert->Go();
}