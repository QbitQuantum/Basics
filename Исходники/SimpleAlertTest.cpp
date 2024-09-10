void
Window::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case kMsgShowAlert:
		{
			int32 count = fCountSlider->Value();

			BAlert* alert = new BAlert("Test title", "Lorem ipsum dolor sit "
				"amet, consectetur adipiscing elit. Suspendisse vel iaculis "
				"quam. Donec faucibus erat nunc, ac ullamcorper justo sodales.",
				"short 1", count > 1 ? "a bit longer 2" : NULL,
				count > 2 ? "very very long button 3" : NULL,
				_ButtonWidth(), _ButtonSpacing(), _AlertType());
			alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
			int result = alert->Go();
			if (result < 0) {
				fLastStringView->SetText("Canceled alert");
			} else {
				fLastStringView->SetText(BString().SetToFormat(
					"Pressed button %d", result + 1).String());
			}
			break;
		}
		default:
			BWindow::MessageReceived(message);
	}
}