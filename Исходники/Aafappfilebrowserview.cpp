// -----------------------------------------------------------------------------
// CAafAppFileBrowserView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAafAppFileBrowserView::ConstructL( const TRect& aRect )
{
	__LOGSTR_TOFILE("CAafAppFileBrowserView::ConstructL() begins");

	// Create a window for this application view
	CreateWindowL();

	// Instantiate listbox control
	iListBox = new (ELeave)CAknSingleGraphicStyleListBox;

	iListBox->ConstructL( this, EAknListBoxSelectionList);

	iListBox->SetContainerWindowL( *this );

	__LOGSTR_TOFILE("CAafAppFileBrowserView::ConstructL() before setting icon array");

	// Creates a GUI icon array
	CAknIconArray* icons = new (ELeave)CAknIconArray(5);

	__LOGSTR_TOFILE("CAafAppFileBrowserView::ConstructL() before CleanupStack::PushL(icons)");

	CleanupStack::PushL(icons);
	icons->ConstructFromResourceL(R_BROWSERVIEW_ICONS);
	// Sets graphics as listbox icons
	iListBox->ItemDrawer()->ColumnData()->SetIconArray(icons);

	__LOGSTR_TOFILE("CAafAppFileBrowserView::ConstructL() before CleanupStack::Pop()");

	CleanupStack::Pop(); // icons

	// Enable marquee effect
	iListBox->ItemDrawer()->ColumnData()->SetMarqueeParams(3, 20, 1000000, 200000);
	iListBox->ItemDrawer()->ColumnData()->EnableMarqueeL(ETrue);

	__LOGSTR_TOFILE("CAafAppFileBrowserView::ConstructL() after setting icon array");

	// Create the scroll indicator
	iListBox->CreateScrollBarFrameL(ETrue);
	iListBox->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);

	iListBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

	iListBox->ActivateL();

	// Create the FileBrowserEngine
	iBrowserEngine = new (ELeave) CFileBrowserEngine;

#ifdef __SERIES60_3X__
	iBrowserEngine->ConstructL();
#else
	iBrowserEngine->ConstructL((CEikProcess*)(((CEikAppUi*)iCoeEnv->AppUi())->Application()->Process()));
#endif

	// Set file browser to display only picture files
	//SetFileListL(EFileBrowserPictures, EFileBrowserDate);

	TFileName aFolder = TFileName(KNullDesC);
	SetFileListL(aFolder);

	// Set the windows size
	SetRect( aRect );

	// Activate the window, which makes it ready to be drawn
	ActivateL();

	__LOGSTR_TOFILE("CAafAppFileBrowserView::ConstructL() begins");
}