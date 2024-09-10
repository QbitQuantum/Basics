//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CTileGenDialog::CTileGenDialog( Panel *parent, const char *name ) : BaseClass( parent, name )
{
	Assert( !g_pTileGenDialog );
	g_pTileGenDialog = this;

	m_pMapLayout = new CMapLayout();
	m_pLayoutSystem = NULL;
	m_VMFExporter = new VMFExporter();
	m_pGenerationOptions = new KeyValues( "EmptyOptions" );

	vgui::HScheme scheme = vgui::scheme()->LoadSchemeFromFile( "tilegen/tilegen_scheme.res", "GAME" );
	SetScheme( scheme );

	if ( !g_bAddedTileGenLocalization )
	{
		g_pVGuiLocalize->AddFile( "tilegen/tilegen_english.txt" );
		g_bAddedTileGenLocalization = true;
	}

	m_fTileSize = 30.0f;

	m_bShowExits = true;
	m_bShowTileSquares = true;
	m_iStartDragX = -1;
	m_iStartDragY = -1;
	m_iStartRubberBandX = -1;
	
	SetSize(384, 420);
	SetMinimumSize(384, 420);
	
	m_pCurrentThemeDetails = new CThemeDetails(this, "CurrentThemeDetails", NULL);
	m_pCurrentThemeDetails->m_iDesiredWidth = 356;
	m_pTemplateListContainer = new CScrollingWindow(this, "TemplateListWindow");
	m_pTemplateListPanel = new CRoomTemplateListPanel(m_pTemplateListContainer, "TemplateListPanel");
	m_pTemplateFilter = new TextEntry( this, "TemplateFilter" );
	m_pShowExitsCheck = new vgui::CheckButton(this, "ShowExitsCheck", "");
	m_pShowExitsCheck->SetSelected(m_bShowExits);
	m_pShowTileSquaresCheck = new vgui::CheckButton(this, "ShowTileSquaresCheck", "");
	m_pShowTileSquaresCheck->SetSelected(m_bShowTileSquares);

	m_pPropertySheet = new vgui::PropertySheet( this, "PropertySheet" );
	m_pLayoutPage = new CTileGenLayoutPage( m_pPropertySheet, "TileGenLayoutPage" );
	m_pLayoutSystemPage = new CTilegenLayoutSystemPage( m_pPropertySheet, "TilegenLayoutSystemPage" );
	m_pLayoutSystemPage->UpdateList();
	m_pPropertySheet->AddPage( m_pLayoutPage, "Layout" );
	m_pPropertySheet->AddPage( m_pLayoutSystemPage, "Missions" );

	m_pCursorPanel = new CRoomTemplatePanel(this, "CursorRoomTemplatePanel");
	m_pCursorPanel->SetMouseInputEnabled(false);
	m_pCursorPanel->SetVisible(false);
	m_pCursorTemplate = NULL;

	m_pTemplateListContainer->SetChildPanel( m_pTemplateListPanel );

	CLevelTheme::LoadLevelThemes();
	OnUpdateCurrentTheme(NULL);

	// setup the menu
	m_pMenuBar = new MenuBar(this, "TileGenMenuBar");
	MenuButton *pFileMenuButton = new MenuButton(this, "FileMenuButton", "&File");
	Menu *pFileMenu = new Menu(pFileMenuButton, "TileGenFileMenu");	
	pFileMenu->AddMenuItem("&New Map Layout",  "NewMapLayout", this);
	pFileMenu->AddMenuItem("&Open Map Layout...",  "OpenMapLayout", this);
	pFileMenu->AddMenuItem("&Open Current Map Layout...",  "OpenCurrentMapLayout", this);
	pFileMenu->AddMenuItem("&Save Map Layout",  "SaveMapLayout", this);
	pFileMenu->AddMenuItem("&Save Map Layout As...",  "SaveMapLayoutAs", this);
	pFileMenu->AddSeparator();
	pFileMenu->AddMenuItem("&Export VMF", "ExportVMF", this);
	pFileMenu->AddMenuItem("&Export VMF and Play Map", "ExportAndPlay", this);
	pFileMenu->AddMenuItem("&Export VMF and Play Without Aliens", "ExportAndPlayClean", this);	
	pFileMenuButton->SetMenu(pFileMenu);
	m_pMenuBar->AddButton(pFileMenuButton);

	MenuButton *pToolsMenuButton = new MenuButton(this, "ToolsMenuButton", "&Tools");
	m_pToolsMenu = new Menu(pToolsMenuButton, "TileGenToolsMenu");	
	pToolsMenuButton->SetMenu(m_pToolsMenu);
	m_pMenuBar->AddButton(pToolsMenuButton);
	//m_pToolsMenu->AddMenuItem("Push Encounters Apart", "PushEncountersApart", this);		// used to debug encounter push apart
	m_pToolsMenu->AddMenuItem("Generate &Thumbnails", "GenerateThumbnails", this);
	//m_pToolsMenu->AddMenuItem("&Location Layout Editor", "LocationLayoutEditor", this);
	m_pToolsMenu->AddMenuItem("&Check Room Templates for Errors", "TileCheck", this);
	m_pToolsMenu->AddSeparator();
	m_nShowDefaultParametersMenuItemID = m_pToolsMenu->AddCheckableMenuItem( "&Show Optional Parameters", "ShowOptionalParameters", this );
	m_nShowAddButtonsMenuItemID = m_pToolsMenu->AddCheckableMenuItem( "&Show 'Add' Buttons", "ShowAddButtons", this );
	// Get the checked menu items in-sync with editor settings.
	m_pToolsMenu->SetMenuItemChecked( m_nShowDefaultParametersMenuItemID, true );
	m_pToolsMenu->SetMenuItemChecked( m_nShowAddButtonsMenuItemID, true );
	m_pLayoutSystemPage->GetEditor()->ShowOptionalValues( true );
	m_pLayoutSystemPage->GetEditor()->ShowAddButtons( true );

	// disable keyboard input on the menu, otherwise once you click there, this dialog never gets key input again (is there a better way to do this and maintain keyboard shortcuts for the menu?)
	pFileMenuButton->SetKeyBoardInputEnabled(false);
	pFileMenu->SetKeyBoardInputEnabled(false);
	m_pMenuBar->SetKeyBoardInputEnabled(false);

	m_pZoomInButton = new vgui::Button( this, "ZoomInButton", "+", this, "ZoomIn" );
	m_pZoomOutButton = new vgui::Button( this, "ZoomOutButton", "-", this, "ZoomOut" );
	m_pCoordinateLabel = new vgui::Label( this, "CoordinateLabel", "" );
	
	// make sure the window get a tick all the time (could change this to only tick on necessary states?)
	vgui::ivgui()->AddTickSignal( GetVPanel(), 0 );
}