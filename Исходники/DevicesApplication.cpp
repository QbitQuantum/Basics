DevicesWindow::DevicesWindow()
	:
	BWindow(BRect(50, 50, 750, 550), B_TRANSLATE_SYSTEM_NAME("Devices"),
		B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS  | B_AUTO_UPDATE_SIZE_LIMITS
			| B_QUIT_ON_WINDOW_CLOSE)
{
	BLayoutBuilder::Group<>(this, B_VERTICAL)
		.SetInsets(0)
		.Add(fDevicesView = new DevicesView());
	GetLayout()->SetExplicitMinSize(BSize(600, 300));
}