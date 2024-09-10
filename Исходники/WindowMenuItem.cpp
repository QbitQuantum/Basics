void
TWindowMenuItem::Draw()
{
	if (!fExpanded) {
		BMenuItem::Draw();
		return;
	}

	// TODO: Tint this smartly based on the low color, this does
	// nothing to black.
	rgb_color menuColor = tint_color(Menu()->LowColor(), 1.07);
	BRect frame(Frame());
	BMenu* menu = Menu();

	menu->PushState();

	// if not selected or being tracked on, fill with gray
	TBarView* barview = (static_cast<TBarApp*>(be_app))->BarView();
	if ((!IsSelected() && !menu->IsRedrawAfterSticky())
		|| barview->Dragging() || !IsEnabled()) {

		rgb_color shadow = tint_color(menuColor, 1.09);
		menu->SetHighColor(shadow);
		frame.right = frame.left + kHPad / 2;
		menu->FillRect(frame);

		menu->SetHighColor(menuColor);
		frame.left = frame.right + 1;
		frame.right = Frame().right;
		menu->FillRect(frame);
	}

	if (IsEnabled() && IsSelected() && !menu->IsRedrawAfterSticky()) {
		// fill
		rgb_color backColor = tint_color(menuColor,
			B_HIGHLIGHT_BACKGROUND_TINT);
		menu->SetLowColor(backColor);
		menu->SetHighColor(backColor);
		menu->FillRect(frame);
	} else {
		menu->SetLowColor(menuColor);
		menu->SetHighColor(menuColor);
	}

	DrawContent();

	menu->PopState();
}