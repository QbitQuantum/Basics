// -----------------------------------------------------------------------------
// GfxEntryPanel class constructor
// -----------------------------------------------------------------------------
GfxEntryPanel::GfxEntryPanel(wxWindow* parent) : EntryPanel(parent, "gfx")
{
	// Init variables
	prev_translation_.addRange(TransRange::Type::Palette, 0);
	edit_translation_.addRange(TransRange::Type::Palette, 0);

	// Add gfx canvas
	gfx_canvas_ = new GfxCanvas(this, -1);
	sizer_main_->Add(gfx_canvas_->toPanel(this), 1, wxEXPAND, 0);
	gfx_canvas_->setViewType(GfxCanvas::View::Default);
	gfx_canvas_->allowDrag(true);
	gfx_canvas_->allowScroll(true);
	gfx_canvas_->setPalette(MainEditor::currentPalette());
	gfx_canvas_->setTranslation(&edit_translation_);

	// Offsets
	wxSize spinsize = { UI::px(UI::Size::SpinCtrlWidth), -1 };
	spin_xoffset_   = new wxSpinCtrl(
        this,
        -1,
        wxEmptyString,
        wxDefaultPosition,
        wxDefaultSize,
        wxSP_ARROW_KEYS | wxTE_PROCESS_ENTER,
        SHRT_MIN,
        SHRT_MAX,
        0);
	spin_yoffset_ = new wxSpinCtrl(
		this,
		-1,
		wxEmptyString,
		wxDefaultPosition,
		wxDefaultSize,
		wxSP_ARROW_KEYS | wxTE_PROCESS_ENTER,
		SHRT_MIN,
		SHRT_MAX,
		0);
	spin_xoffset_->SetMinSize(spinsize);
	spin_yoffset_->SetMinSize(spinsize);
	sizer_bottom_->Add(new wxStaticText(this, -1, "Offsets:"), 0, wxALIGN_CENTER_VERTICAL, 0);
	sizer_bottom_->Add(spin_xoffset_, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, UI::pad());
	sizer_bottom_->Add(spin_yoffset_, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, UI::pad());

	// Gfx (offset) type
	wxString offset_types[] = { "Auto", "Graphic", "Sprite", "HUD" };
	choice_offset_type_     = new wxChoice(this, -1, wxDefaultPosition, wxDefaultSize, 4, offset_types);
	choice_offset_type_->SetSelection(0);
	sizer_bottom_->Add(choice_offset_type_, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, UI::pad());

	// Auto offset
	btn_auto_offset_ = new SIconButton(this, "offset", "Modify Offsets...");
	sizer_bottom_->Add(btn_auto_offset_, 0, wxALIGN_CENTER_VERTICAL);

	sizer_bottom_->AddStretchSpacer();

	// Aspect ratio correction checkbox
	cb_arc_ = new wxCheckBox(this, -1, "Aspect Ratio Correction");
	cb_arc_->SetValue(gfx_arc);
	sizer_bottom_->Add(cb_arc_, 0, wxEXPAND, 0);
	sizer_bottom_->AddSpacer(UI::padLarge());

	// Tile checkbox
	cb_tile_ = new wxCheckBox(this, -1, "Tile");
	sizer_bottom_->Add(cb_tile_, 0, wxEXPAND, 0);
	sizer_bottom_->AddSpacer(UI::padLarge());

	// Image selection buttons
	btn_nextimg_ = new SIconButton(this, "right");
	btn_previmg_ = new SIconButton(this, "left");
	text_curimg_ = new wxStaticText(this, -1, "Image XX/XX");
	btn_nextimg_->Show(false);
	btn_previmg_->Show(false);
	text_curimg_->Show(false);

	// Palette chooser
	listenTo(theMainWindow->paletteChooser());

	// Custom menu
	menu_custom_ = new wxMenu();
	GfxEntryPanel::fillCustomMenu(menu_custom_);
	custom_menu_name_ = "Graphic";

	// Brushes menu
	menu_brushes_ = new wxMenu();
	fillBrushMenu(menu_brushes_);

	// Custom toolbar
	setupToolbar();

	// Bind Events
	cb_colour_->Bind(wxEVT_COLOURBOX_CHANGED, &GfxEntryPanel::onPaintColourChanged, this);
	spin_xoffset_->Bind(wxEVT_SPINCTRL, &GfxEntryPanel::onXOffsetChanged, this);
	spin_yoffset_->Bind(wxEVT_SPINCTRL, &GfxEntryPanel::onYOffsetChanged, this);
	spin_xoffset_->Bind(wxEVT_TEXT_ENTER, &GfxEntryPanel::onXOffsetChanged, this);
	spin_yoffset_->Bind(wxEVT_TEXT_ENTER, &GfxEntryPanel::onYOffsetChanged, this);
	choice_offset_type_->Bind(wxEVT_CHOICE, &GfxEntryPanel::onOffsetTypeChanged, this);
	cb_tile_->Bind(wxEVT_CHECKBOX, &GfxEntryPanel::onTileChanged, this);
	cb_arc_->Bind(wxEVT_CHECKBOX, &GfxEntryPanel::onARCChanged, this);
	Bind(wxEVT_GFXCANVAS_OFFSET_CHANGED, &GfxEntryPanel::onGfxOffsetChanged, this, gfx_canvas_->GetId());
	Bind(wxEVT_GFXCANVAS_PIXELS_CHANGED, &GfxEntryPanel::onGfxPixelsChanged, this, gfx_canvas_->GetId());
	Bind(wxEVT_GFXCANVAS_COLOUR_PICKED, &GfxEntryPanel::onColourPicked, this, gfx_canvas_->GetId());
	btn_nextimg_->Bind(wxEVT_BUTTON, &GfxEntryPanel::onBtnNextImg, this);
	btn_previmg_->Bind(wxEVT_BUTTON, &GfxEntryPanel::onBtnPrevImg, this);
	btn_auto_offset_->Bind(wxEVT_BUTTON, &GfxEntryPanel::onBtnAutoOffset, this);

	// Apply layout
	wxWindowBase::Layout();
}