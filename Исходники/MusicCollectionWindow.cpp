MusicCollectionWindow::MusicCollectionWindow(BRect frame, const char* title)
	:
	BWindow(frame, title, B_DOCUMENT_WINDOW, B_AVOID_FRONT)
{
	BView* rootView = new BView(Bounds(), NULL, B_FOLLOW_ALL, B_WILL_DRAW);
	AddChild(rootView);
	rootView->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	fQueryField = new BTextControl("Search: ", "", NULL);
	fQueryField->SetExplicitAlignment(BAlignment(B_ALIGN_HORIZONTAL_CENTER,
		B_ALIGN_USE_FULL_HEIGHT));
	fQueryField->SetModificationMessage(new BMessage(kMsgQueryInput));

	fCountView = new BStringView("Count View", "Count:");

	fFileListView = new MusicFileListView("File List View");
	fFileListView->SetInvocationMessage(new BMessage(kMsgItemInvoked));
	BScrollView* scrollView = new BScrollView("list scroll", fFileListView, 0,
		true, true, B_PLAIN_BORDER);

	float spacing = be_control_look->DefaultItemSpacing() / 2;
	BALMLayout* layout = new BALMLayout(spacing);
	layout->SetInset(spacing);
	rootView->SetLayout(layout);

	layout->AddView(fQueryField, layout->Left(), layout->Top());
	layout->AddViewToRight(fCountView, layout->Right());
	layout->AddView(scrollView, layout->Left(),
		layout->AreaFor(fQueryField)->Bottom(), layout->Right(),
		layout->Bottom());

	Area* area = layout->AreaFor(scrollView);
	area->SetLeftInset(0);
	area->SetRightInset(0);
	area->SetBottomInset(0);

	BSize min = layout->MinSize();
	BSize max = layout->MaxSize();
	SetSizeLimits(min.Width(), max.Width(), min.Height(), max.Height());

	fEntryViewInterface = new ListViewListener<FileListItem>(fFileListView,
		fCountView);
	fQueryHandler = new QueryHandler(fEntryViewInterface);
	AddHandler(fQueryHandler);
	fQueryReader = new QueryReader(fQueryHandler);
	fQueryHandler->SetReadThread(fQueryReader);

	// start initial query
	PostMessage(kMsgQueryInput);
}