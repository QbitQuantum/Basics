NetworkWindow::NetworkWindow(Setting* setting)
	: BWindow(BRect(50, 50, 269, 302), "Network", B_TITLED_WINDOW,
		B_NOT_RESIZABLE | B_ASYNCHRONOUS_CONTROLS | B_NOT_ZOOMABLE
		| B_AUTO_UPDATE_SIZE_LIMITS)
{
	SetLayout(new BGroupLayout(B_HORIZONTAL));
	fEthernetView = new EthernetSettingsView(setting);
	GetLayout()->AddView(fEthernetView);
	
	SetTitle(setting->Name());
}