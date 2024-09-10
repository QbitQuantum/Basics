bool
LprSetupView::UpdateViewData()
{
	if (*fServer->Text() && *fQueue->Text()) {

		try {
			LpsClient lpr(fServer->Text());
			lpr.connect();
		}

		catch (LPSException &err) {
			BAlert *alert = new BAlert("", err.what(), "OK");
			alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
			alert->Go();
			return false;
		}

		fDir->WriteAttr(LPR_SERVER_NAME, B_STRING_TYPE, 0, fServer->Text(),
			strlen(fServer->Text()) + 1);
		fDir->WriteAttr(LPR_QUEUE_NAME,  B_STRING_TYPE, 0, fQueue->Text(),
			strlen(fQueue->Text())  + 1);
		return true;
	}

	BAlert *alert = new BAlert("", "Please enter server address and printer"
		"queue name.", "OK");
	alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
	alert->Go();
	return false;
}