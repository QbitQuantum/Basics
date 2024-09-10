void
MemoryBarMenuItem::DrawBar(bool force)
{
	// only draw anything if something has changed
	if (!force && fWriteMemory == fLastWrite && fAllMemory == fLastAll
		&& fCommittedMemory == fLastCommitted)
		return;

	bool selected = IsSelected();
	BRect frame = Frame();
	BMenu* menu = Menu();

	// draw the bar itself

	BRect rect(frame.right - kMargin - kBarWidth, frame.top + 5,
		frame.right - kMargin, frame.top + 13);
	if (fWriteMemory < 0)
		return;

	if (fGrenze1 < 0)
		force = true;

	if (force) {
		if (selected)
			menu->SetHighColor(gFrameColorSelected);
		else
			menu->SetHighColor(gFrameColor);
		menu->StrokeRect(rect);
	}

	rect.InsetBy(1, 1);
	BRect r = rect;
	double grenze1 = rect.left + (rect.right - rect.left) * float(fWriteMemory)
		/ fCommittedMemory;
	double grenze2 = rect.left + (rect.right - rect.left) * float(fAllMemory)
		/ fCommittedMemory;
	if (grenze1 > rect.right)
		grenze1 = rect.right;
	if (grenze2 > rect.right)
		grenze2 = rect.right;
	r.right = grenze1;
	if (!force)
		r.left = fGrenze1;
	if (r.left < r.right) {
		if (selected)
			menu->SetHighColor(gKernelColorSelected);
		else
			menu->SetHighColor(gKernelColor);
		menu->FillRect(r);
	}

	r.left = grenze1;
	r.right = grenze2;

	if (!force) {
		if (fGrenze2 > r.left && r.left >= fGrenze1)
			r.left = fGrenze2;
		if (fGrenze1 < r.right && r.right  <= fGrenze2)
			r.right = fGrenze1;
	}

	if (r.left < r.right) {
		if (selected)
			menu->SetHighColor(gUserColorSelected);
		else
			menu->SetHighColor(gUserColor);
		menu->FillRect(r);
	}

	r.left = grenze2;
	r.right = rect.right;

	if (!force)
		r.right = fGrenze2;

	if (r.left < r.right) {
		if (selected)
			menu->SetHighColor(gWhiteSelected);
		else
			menu->SetHighColor(kWhite);
		menu->FillRect(r);
	}

	menu->SetHighColor(kBlack);
	fGrenze1 = grenze1;
	fGrenze2 = grenze2;

	fLastCommitted = fCommittedMemory;

	// Draw the values if necessary; if only fCommitedMemory changes, only
	// the bar might have to be updated

	if (!force && fWriteMemory == fLastWrite && fAllMemory == fLastAll)
		return;

	if (selected)
		menu->SetLowColor(gMenuBackColorSelected);
	else
		menu->SetLowColor(gMenuBackColor);

	BRect textRect(rect.left - kMargin - gMemoryTextWidth, frame.top,
		rect.left - kMargin, frame.bottom);
	menu->FillRect(textRect, B_SOLID_LOW);

	fLastWrite = fWriteMemory;
	fLastAll = fAllMemory;

	menu->SetHighColor(kBlack);

	char infos[128];
	string_for_size(fWriteMemory * 1024.0, infos, sizeof(infos));

	BPoint loc(rect.left - kMargin - gMemoryTextWidth / 2 - menu->StringWidth(infos),
		rect.bottom + 1);
	menu->DrawString(infos, loc);

	string_for_size(fAllMemory * 1024.0, infos, sizeof(infos));
	loc.x = rect.left - kMargin - menu->StringWidth(infos);
	menu->DrawString(infos, loc);
}