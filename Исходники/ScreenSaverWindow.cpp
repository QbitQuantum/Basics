ScreenSaverWindow::ScreenSaverWindow()
	:
	BWindow(BRect(50.0f, 50.0f, 50.0f + kWindowWidth, 50.0f + kWindowHeight),
		B_TRANSLATE_SYSTEM_NAME("ScreenSaver"), B_TITLED_WINDOW,
		B_ASYNCHRONOUS_CONTROLS | B_AUTO_UPDATE_SIZE_LIMITS)
{
	fSettings.Load();

	fMinWidth = floorf(be_control_look->DefaultItemSpacing()
		* (kWindowWidth / kDefaultItemSpacingAt12pt));

	font_height fontHeight;
	be_plain_font->GetHeight(&fontHeight);
	float textHeight = ceilf(fontHeight.ascent + fontHeight.descent);

	fMinHeight = ceilf(std::max(kWindowHeight, textHeight * 28));

	// Create the password editing window
	fPasswordWindow = new PasswordWindow(fSettings);
	fPasswordWindow->Run();

	// Create the tab view
	fTabView = new TabView();
	fTabView->SetBorder(B_NO_BORDER);

	// Create the controls inside the tabs
	fFadeView = new FadeView(B_TRANSLATE("General"), fSettings);
	fModulesView = new ModulesView(B_TRANSLATE("Screensavers"), fSettings);

	fTabView->AddTab(fFadeView);
	fTabView->AddTab(fModulesView);

	// Create the topmost background view
	BView* topView = new BView("topView", B_WILL_DRAW);
	topView->SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
	topView->SetExplicitAlignment(BAlignment(B_ALIGN_USE_FULL_WIDTH,
		B_ALIGN_USE_FULL_HEIGHT));
	topView->SetExplicitMinSize(BSize(fMinWidth, fMinHeight));
	BLayoutBuilder::Group<>(topView, B_VERTICAL)
		.SetInsets(0, B_USE_DEFAULT_SPACING, 0, B_USE_WINDOW_SPACING)
		.Add(fTabView)
		.End();

	SetLayout(new BGroupLayout(B_VERTICAL));
	GetLayout()->AddView(topView);

	fTabView->Select(fSettings.WindowTab());

	if (fSettings.WindowFrame().left > 0 && fSettings.WindowFrame().top > 0)
		MoveTo(fSettings.WindowFrame().left, fSettings.WindowFrame().top);

	if (fSettings.WindowFrame().Width() > 0
		&& fSettings.WindowFrame().Height() > 0) {
		ResizeTo(fSettings.WindowFrame().Width(),
			fSettings.WindowFrame().Height());
	}

	CenterOnScreen();
}