VolumeWindow::VolumeWindow(BRect frame, bool dontBeep, int32 volumeWhich)
	: BWindow(frame, "VolumeWindow", B_BORDERED_WINDOW_LOOK,
		B_FLOATING_ALL_WINDOW_FEEL,
		B_ASYNCHRONOUS_CONTROLS | B_WILL_ACCEPT_FIRST_CLICK
		| B_AUTO_UPDATE_SIZE_LIMITS, 0),
	fUpdatedCount(0)
{
	SetLayout(new BGroupLayout(B_HORIZONTAL));

	BGroupLayout* layout = new BGroupLayout(B_HORIZONTAL);
	layout->SetInsets(5, 5, 5, 5);

	BBox* box = new BBox("sliderbox");
	box->SetLayout(layout);
	box->SetBorder(B_PLAIN_BORDER);
	AddChild(box);

	BSlider* slider = new VolumeControl(volumeWhich, !dontBeep,
		new BMessage(kMsgVolumeChanged));
	slider->SetModificationMessage(new BMessage(kMsgVolumeUpdate));
	box->AddChild(slider);

	slider->SetTarget(this);
	ResizeTo(300, 50);

	// Make sure it's not outside the screen.
	const int32 kMargin = 3;
	BRect windowRect = Frame();
	BRect screenFrame(BScreen(B_MAIN_SCREEN_ID).Frame());
	if (screenFrame.right < windowRect.right + kMargin)
		MoveBy(- kMargin - windowRect.right + screenFrame.right, 0);
	if (screenFrame.bottom < windowRect.bottom + kMargin)
		MoveBy(0, - kMargin - windowRect.bottom + screenFrame.bottom);
	if (screenFrame.left > windowRect.left - kMargin)
		MoveBy(kMargin + screenFrame.left - windowRect.left, 0);
	if (screenFrame.top > windowRect.top - kMargin)
		MoveBy(0, kMargin + screenFrame.top - windowRect.top);
}