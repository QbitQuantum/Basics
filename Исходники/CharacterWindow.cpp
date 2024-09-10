CharacterWindow::CharacterWindow()
	: BWindow(BRect(100, 100, 700, 550), "CharacterMap", B_TITLED_WINDOW,
		B_ASYNCHRONOUS_CONTROLS | B_QUIT_ON_WINDOW_CLOSE
			| B_AUTO_UPDATE_SIZE_LIMITS)
{
	BMessage settings;
	_LoadSettings(settings);

	BRect frame;
	if (settings.FindRect("window frame", &frame) == B_OK) {
		MoveTo(frame.LeftTop());
		ResizeTo(frame.Width(), frame.Height());
	}

	// create GUI

	SetLayout(new BGroupLayout(B_VERTICAL));

	BMenuBar* menuBar = new BMenuBar("menu");

	fFilterControl = new BTextControl("Filter:", NULL, NULL);
	fFilterControl->SetModificationMessage(new BMessage(kMsgFilterChanged));

	BButton* clearButton = new BButton("clear", "Clear",
		new BMessage(kMsgClearFilter));

	fUnicodeBlockView = new UnicodeBlockView("unicodeBlocks");
	fUnicodeBlockView->SetSelectionMessage(
		new BMessage(kMsgUnicodeBlockSelected));

	BScrollView* unicodeScroller = new BScrollView("unicodeScroller",
		fUnicodeBlockView, 0, false, true);

	fCharacterView = new CharacterView("characters");
	fCharacterView->SetTarget(this, kMsgCharacterChanged);

	// TODO: have a context object shared by CharacterView/UnicodeBlockView
	bool show;
	if (settings.FindBool("show private blocks", &show) == B_OK) {
		fCharacterView->ShowPrivateBlocks(show);
		fUnicodeBlockView->ShowPrivateBlocks(show);
	}
	if (settings.FindBool("show contained blocks only", &show) == B_OK) {
		fCharacterView->ShowContainedBlocksOnly(show);
		fUnicodeBlockView->ShowPrivateBlocks(show);
	}

	const char* family;
	const char* style;
	if (settings.FindString("font family", &family) == B_OK
		&& settings.FindString("font style", &style) == B_OK) {
		_SetFont(family, style);
	}

	int32 fontSize;
	if (settings.FindInt32("font size", &fontSize) == B_OK) {
		BFont font = fCharacterView->CharacterFont();
		if (fontSize < kMinFontSize)
			fontSize = kMinFontSize;
		else if (fontSize > kMaxFontSize)
			fontSize = kMaxFontSize;
		font.SetSize(fontSize);

		fCharacterView->SetCharacterFont(font);
	} else
		fontSize = (int32)fCharacterView->CharacterFont().Size();

	BScrollView* characterScroller = new BScrollView("characterScroller",
		fCharacterView, 0, false, true);

	fFontSizeSlider = new FontSizeSlider("fontSizeSlider", "Font size:",
		new BMessage(kMsgFontSizeChanged), kMinFontSize, kMaxFontSize);
	fFontSizeSlider->SetValue(fontSize);

	fCodeView = new BStringView("code", "-");
	fCodeView->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED,
		fCodeView->PreferredSize().Height()));

	AddChild(BGroupLayoutBuilder(B_VERTICAL)
		.Add(menuBar)
		.Add(BGroupLayoutBuilder(B_HORIZONTAL, 10)//BSplitLayoutBuilder()
			.Add(BGroupLayoutBuilder(B_VERTICAL, 10)
				.Add(BGroupLayoutBuilder(B_HORIZONTAL, 10)
					.Add(fFilterControl)
					.Add(clearButton))
				.Add(unicodeScroller))
			.Add(BGroupLayoutBuilder(B_VERTICAL, 10)
				.Add(characterScroller)
				.Add(fFontSizeSlider)
				.Add(fCodeView))
			.SetInsets(10, 10, 10, 10)));

	// Add menu

	// "File" menu
	BMenu* menu = new BMenu("File");
	BMenuItem* item;

	menu->AddItem(item = new BMenuItem("About CharacterMap" B_UTF8_ELLIPSIS,
		new BMessage(B_ABOUT_REQUESTED)));

	menu->AddSeparatorItem();

	menu->AddItem(new BMenuItem("Quit", new BMessage(B_QUIT_REQUESTED), 'Q'));
	menu->SetTargetForItems(this);
	item->SetTarget(be_app);
	menuBar->AddItem(menu);

	menu = new BMenu("View");
	menu->AddItem(item = new BMenuItem("Show private blocks",
		new BMessage(kMsgPrivateBlocks)));
	item->SetMarked(fCharacterView->IsShowingPrivateBlocks());
// TODO: this feature is not yet supported by Haiku!
#if 0
	menu->AddItem(item = new BMenuItem("Only show blocks contained in font",
		new BMessage(kMsgContainedBlocks)));
	item->SetMarked(fCharacterView->IsShowingContainedBlocksOnly());
#endif
	menuBar->AddItem(menu);

	menuBar->AddItem(_CreateFontMenu());

	AddCommonFilter(new EscapeMessageFilter(kMsgClearFilter));
	AddCommonFilter(new RedirectUpAndDownFilter(fUnicodeBlockView));

	// TODO: why is this needed?
	fUnicodeBlockView->SetTarget(this);

	fFilterControl->MakeFocus();
}