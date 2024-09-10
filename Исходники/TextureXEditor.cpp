// -----------------------------------------------------------------------------
// TextureXEditor class constructor
// -----------------------------------------------------------------------------
TextureXEditor::TextureXEditor(wxWindow* parent) : wxPanel(parent, -1)
{
	// Init variables
	undo_manager_ = std::make_unique<UndoManager>();
	wxWindowBase::SetName("texturex");

	// Create texture menu
	menu_texture_ = new wxMenu();
	SAction::fromId("txed_new")->addToMenu(menu_texture_);
	SAction::fromId("txed_new_patch")->addToMenu(menu_texture_);
	SAction::fromId("txed_new_file")->addToMenu(menu_texture_);
	SAction::fromId("txed_delete")->addToMenu(menu_texture_);
	menu_texture_->AppendSeparator();
	SAction::fromId("txed_rename")->addToMenu(menu_texture_);
	SAction::fromId("txed_rename_each")->addToMenu(menu_texture_);
	auto menu_export = new wxMenu();
	SAction::fromId("txed_export")->addToMenu(menu_export, "Archive (as image)");
	SAction::fromId("txed_extract")->addToMenu(menu_export, "File");
	menu_texture_->AppendSubMenu(menu_export, "&Export To");
	menu_texture_->AppendSeparator();
	SAction::fromId("txed_copy")->addToMenu(menu_texture_);
	SAction::fromId("txed_cut")->addToMenu(menu_texture_);
	SAction::fromId("txed_paste")->addToMenu(menu_texture_);
	menu_texture_->AppendSeparator();
	SAction::fromId("txed_up")->addToMenu(menu_texture_);
	SAction::fromId("txed_down")->addToMenu(menu_texture_);
	SAction::fromId("txed_sort")->addToMenu(menu_texture_);
	auto menu_patch = new wxMenu();
	SAction::fromId("txed_patch_add")->addToMenu(menu_patch);
	SAction::fromId("txed_patch_remove")->addToMenu(menu_patch);
	SAction::fromId("txed_patch_replace")->addToMenu(menu_patch);
	SAction::fromId("txed_patch_back")->addToMenu(menu_patch);
	SAction::fromId("txed_patch_forward")->addToMenu(menu_patch);
	SAction::fromId("txed_patch_duplicate")->addToMenu(menu_patch);
	menu_texture_->AppendSubMenu(menu_patch, "&Patch");

	// Create patch browser
	patch_browser_ = new PatchBrowser(theMainWindow);
	patch_browser_->CenterOnParent();
	patch_browser_->Show(false);

	// Setup sizer
	auto sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(sizer);

	// Add tabs
	tabs_ = STabCtrl::createControl(this);
	sizer->Add(tabs_, 1, wxEXPAND | wxALL, UI::pad());

	// Bind events
	Bind(wxEVT_SHOW, &TextureXEditor::onShow, this);

	// Palette chooser
	listenTo(theMainWindow->paletteChooser());
	updateTexturePalette();

	// Listen to patch table
	listenTo(&patch_table_);

	// Listen to resource manager
	listenTo(&App::resources());

	// Update + layout
	wxWindowBase::Layout();
	wxWindow::Show();
}