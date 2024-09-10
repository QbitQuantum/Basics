bool
SetupView::CheckSetup()
{
	if (*fServerAddress->Text() && *fQueuePort->Text()) {
		BNetEndpoint* ep = new BNetEndpoint(SOCK_STREAM);
		if (ep->InitCheck() == B_NO_ERROR) {
			uint16 port = atoi(fQueuePort->Text());

			if (! port)
				port = 9100;

			if (ep->Connect(fServerAddress->Text(), port) != B_OK) {
				BString text;
				text << "Failed to connect to " << fServerAddress->Text() << ":" << (int) port << "!";
				BAlert* alert = new BAlert("", text.String(), "OK");
				alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
				alert->Go();
				return false;
			};

			char str[256];
			sprintf(str, "%s:%d", fServerAddress->Text(), port);
			fPrinterDirectory->WriteAttr("transport_address", B_STRING_TYPE,
				0, str, strlen(str) + 1);
			return true;
		};
	};

	BAlert* alert = new BAlert("", "Please input parameters.", "OK");
	alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
	alert->Go();
	return false;
}