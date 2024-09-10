frmDatabaseDesigner::frmDatabaseDesigner(frmMain *form, const wxString &_title, pgConn *conn)
	: pgFrame(NULL, _title)
{
	mainForm = form;
	SetTitle(wxT("Database Designer"));
	SetIcon(wxIcon(*ddmodel_32_png_ico));
	loading = true;
	closing = false;

	RestorePosition(100, 100, 600, 500, 450, 300);
	SetMinSize(wxSize(450, 300));

	// connection
	connection = conn;

	// notify wxAUI which frame to use
	manager.SetManagedWindow(this);
	manager.SetFlags(wxAUI_MGR_DEFAULT | wxAUI_MGR_TRANSPARENT_DRAG);

	wxWindowBase::SetFont(settings->GetSystemFont());

	// Set File menu
	fileMenu = new wxMenu();
	fileMenu->Append(MNU_NEW, _("&New database design\tCtrl-N"), _("Create a new database design"));
	fileMenu->AppendSeparator();
	fileMenu->Append(MNU_LOADMODEL, _("&Open Model..."), _("Open an existing database design from a file"));
	fileMenu->Append(MNU_SAVEMODEL, _("&Save Model"), _("Save changes at database design"));
	fileMenu->Append(MNU_SAVEMODELAS, _("&Save Model As..."), _("Save database design at new file"));
	fileMenu->AppendSeparator();
	fileMenu->Append(CTL_IMPSCHEMA, _("&Import Tables..."), _("Import tables from database schema to database designer model"));
	fileMenu->AppendSeparator();
	fileMenu->Append(MNU_EXIT, _("E&xit\tCtrl-W"), _("Exit database designer window"));

	// Set Diagram menu
	diagramMenu = new wxMenu();
	diagramMenu->Append(MNU_NEWDIAGRAM, _("&New model diagram"), _("Create a new diagram"));
	diagramMenu->Append(MNU_DELDIAGRAM, _("&Delete selected model diagram..."), _("Delete selected diagram"));
	diagramMenu->Append(MNU_RENDIAGRAM, _("&Rename selected model diagram..."), _("Rename selected diagram"));

	// Set View menu
	viewMenu = new wxMenu();
	viewMenu->AppendCheckItem(MNU_TOGGLEMBROWSER, _("&Model Browser"), _("Show / Hide Model Browser Window"));
	viewMenu->AppendCheckItem(MNU_TOGGLEDDSQL, _("&SQL Window"), _("Show / Hide SQL Window"));
	viewMenu->Check(MNU_TOGGLEDDSQL, true);
	viewMenu->Check(MNU_TOGGLEMBROWSER, true);

	// Set Help menu
	helpMenu = new wxMenu();
	helpMenu->Append(MNU_CONTENTS, _("&Help"), _("Open the helpfile."));
	helpMenu->Append(MNU_HELP, _("&SQL Help\tF1"), _("Display help on SQL commands."));

	// Set menu bar
	menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, _("&File"));
	menuBar->Append(diagramMenu, _("&Diagram"));
	menuBar->Append(viewMenu, _("&View"));
	menuBar->Append(helpMenu, _("&Help"));
	SetMenuBar(menuBar);

	// Set status bar
	int iWidths[6] = {0, -1, 40, 150, 80, 80};
	CreateStatusBar(6);
	SetStatusBarPane(-1);
	SetStatusWidths(6, iWidths);

	// Set toolbar
	toolBar = new ctlMenuToolbar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);
	toolBar->SetToolBitmapSize(wxSize(16, 16));
	toolBar->AddTool(MNU_NEW, _("New Model"), *file_new_png_bmp, _("Create new model"), wxITEM_NORMAL);
	toolBar->AddTool(MNU_NEWDIAGRAM, _("New Diagram"), *ddnewdiagram_png_bmp, _("Add new diagram"), wxITEM_NORMAL);
	toolBar->AddSeparator();
	toolBar->AddTool(MNU_LOADMODEL, _("Open Model"), *file_open_png_bmp, _("Open existing model"), wxITEM_NORMAL);
	toolBar->AddTool(MNU_SAVEMODEL, _("Save Model"), *file_save_png_bmp, _("Save current model"), wxITEM_NORMAL);
	toolBar->AddSeparator();
	toolBar->AddTool(MNU_ADDTABLE, _("Add Table"), *table_png_bmp, _("Add empty table to the current model"), wxITEM_NORMAL);
	toolBar->AddTool(MNU_DELETETABLE, _("Delete Table"), wxBitmap(*ddRemoveTable2_png_img), _("Delete selected table"), wxITEM_NORMAL);
	toolBar->AddTool(MNU_ADDCOLUMN, _("Add Column"), *table_png_bmp, _("Add new column to the selected table"), wxITEM_NORMAL);
	toolBar->AddSeparator();
	toolBar->AddTool(MNU_GENERATEMODEL, _("Generate Model"), *continue_png_bmp, _("Generate SQL for the current model"), wxITEM_NORMAL);
	toolBar->AddTool(MNU_GENERATEDIAGRAM, _("Generate Diagram"), *ddgendiagram_png_bmp, _("Generate SQL for the current diagram"), wxITEM_NORMAL);
	toolBar->AddSeparator();
	toolBar->AddTool(CTL_IMPSCHEMA, _("Import Tables from database..."), *conversion_png_ico, _("Import tables from database schema to database designer model"), wxITEM_NORMAL);
	toolBar->AddSeparator();
	toolBar->AddTool(MNU_HELP, _("Help"), *help_png_bmp, _("Display help"), wxITEM_NORMAL);
	toolBar->Realize();

	// Create notebook for diagrams
	diagrams = new ctlAuiNotebook(this, CTL_DDNOTEBOOK, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TOP | wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE | wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_WINDOWLIST_BUTTON | wxAUI_NB_CLOSE_ON_ALL_TABS);

	// Now, the scratchpad
	sqltext = new ctlSQLBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxSIMPLE_BORDER | wxTE_RICH2);

	//Now, the Objects Browser
	wxSizer *browserSizer = new wxBoxSizer(wxHORIZONTAL);
	browserPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	// Add the database designer
	design = new ddDatabaseDesign(diagrams, this);

	// Create database model browser
	modelBrowser = new ddModelBrowser(browserPanel, DD_BROWSER, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS | wxSIMPLE_BORDER, design);
	design->registerBrowser(modelBrowser);

	// Set browser Sizers
	browserSizer->Add(modelBrowser, 1, wxEXPAND);
	browserPanel->SetSizer(browserSizer);
	browserSizer->SetSizeHints(browserPanel);

	// Add view to notebook
	diagrams->AddPage(design->createDiagram(diagrams, _("unnamed"), false)->getView(), _("unnamed"));


	// Add the database selection bar and schema selector
	wxSizer *connectionSizer = new wxBoxSizer(wxHORIZONTAL);
	connectionPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1));
	cbConnection = new wxBitmapComboBox(connectionPanel, CTL_DDCONNECTION, wxEmptyString, wxDefaultPosition, wxSize(-1, -1), wxArrayString(), wxCB_READONLY | wxCB_DROPDOWN);
	if(conn)
		cbConnection->Append(conn->GetName(), CreateBitmap(GetServerColour(conn)), (void *)conn);
	cbConnection->Append(_("<new connection>"), wxNullBitmap, (void *) NULL);

	connectionSizer->Add(cbConnection, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 1);
	connectionSizer->AddSpacer(5);
	connectionPanel->SetSizer(connectionSizer);
	connectionSizer->SetSizeHints(connectionPanel);


	// Add the panes
	manager.AddPane(diagrams,
	                wxAuiPaneInfo().Center().
	                Name(wxT("sqlQuery")).Caption(_("Database Designer")).
	                CaptionVisible(true).CloseButton(false).MaximizeButton(true).
	                Dockable(true).Movable(true));
	manager.AddPane(browserPanel,
	                wxAuiPaneInfo().Left().
	                Name(wxT("ModelBrowser")).Caption(_("Model Browser")).
	                CaptionVisible(true).CloseButton(true).MinimizeButton(true).
	                MinSize(wxSize(140, 100)).BestSize(wxSize(200, 200)));
	manager.AddPane(sqltext,
	                wxAuiPaneInfo().Bottom().
	                Name(wxT("sqlText")).Caption(_("SQL query")).
	                CaptionVisible(true).CloseButton(true).MaximizeButton(true).MinimizeButton(true).
	                MinSize(wxSize(200, 100)).BestSize(wxSize(350, 150)));
	manager.AddPane(toolBar,
	                wxAuiPaneInfo().Top().
	                Name(wxT("toolBar")).Caption(_("Tool bar")).
	                ToolbarPane().
	                LeftDockable(false).RightDockable(false));
	manager.AddPane(connectionPanel, wxAuiPaneInfo().Name(wxT("databaseBar"))
	                .Caption(_("Connection bar")).ToolbarPane().Top().
	                LeftDockable(false).RightDockable(false));

	// Update the AUI manager
	manager.Update();

	//Update browser info
	modelBrowser->SetSize(browserPanel->GetSize());

	previousChanged = true;
	setModelChanged(false);
	SetStatusText(wxString(wxT("Ready")), 1);
}