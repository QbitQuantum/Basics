void PrefsWindow::add_serial_names(BPopUpMenu *menu, uint32 msg)
{
	BSerialPort *port = new BSerialPort;
	char name[B_PATH_NAME_LENGTH];
	for (int i=0; i<port->CountDevices(); i++) {
		port->GetDeviceName(i, name);
		menu->AddItem(new BMenuItem(name, new BMessage(msg)));
	}
	if (sys_info.platform_type == B_BEBOX_PLATFORM) {
		BDirectory dir;
		BEntry entry;
		dir.SetTo("/dev/parallel");
		if (dir.InitCheck() == B_NO_ERROR) {
			dir.Rewind();
			while (dir.GetNextEntry(&entry) >= 0) {
				if (!entry.IsDirectory()) {
					entry.GetName(name);
					menu->AddItem(new BMenuItem(name, new BMessage(msg)));
				}
			}
		}
	}
	delete port;
}