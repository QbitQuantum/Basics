AudioBox::AudioBox(wxWindow *parent, agi::Context *context)
: wxSashWindow(parent, -1, wxDefaultPosition, wxDefaultSize, wxSW_3D | wxCLIP_CHILDREN)
, controller(context->audioController.get())
, context(context)
, audio_open_connection(context->audioController->AddAudioPlayerOpenListener(&AudioBox::OnAudioOpen, this))
, panel(new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxBORDER_RAISED))
, audioDisplay(new AudioDisplay(panel, context->audioController.get(), context))
, HorizontalZoom(new wxSlider(panel, Audio_Horizontal_Zoom, -OPT_GET("Audio/Zoom/Horizontal")->GetInt(), -50, 30, wxDefaultPosition, wxSize(-1, 20), wxSL_VERTICAL|wxSL_BOTH))
, VerticalZoom(new wxSlider(panel, Audio_Vertical_Zoom, OPT_GET("Audio/Zoom/Vertical")->GetInt(), 0, 100, wxDefaultPosition, wxSize(-1, 20), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE))
, VolumeBar(new wxSlider(panel, Audio_Volume, OPT_GET("Audio/Volume")->GetInt(), 0, 100, wxDefaultPosition, wxSize(-1, 20), wxSL_VERTICAL|wxSL_BOTH|wxSL_INVERSE))
{
	SetSashVisible(wxSASH_BOTTOM, true);
	Bind(wxEVT_SASH_DRAGGED, &AudioBox::OnSashDrag, this);

	HorizontalZoom->SetToolTip(_("Horizontal zoom"));
	VerticalZoom->SetToolTip(_("Vertical zoom"));
	VolumeBar->SetToolTip(_("Audio Volume"));

	bool link = OPT_GET("Audio/Link")->GetBool();
	if (link) {
		VolumeBar->SetValue(VerticalZoom->GetValue());
		VolumeBar->Enable(false);
	}

	// VertVol sider
	wxSizer *VertVol = new wxBoxSizer(wxHORIZONTAL);
	VertVol->Add(VerticalZoom,1,wxEXPAND,0);
	VertVol->Add(VolumeBar,1,wxEXPAND,0);
	wxSizer *VertVolArea = new wxBoxSizer(wxVERTICAL);
	VertVolArea->Add(VertVol,1,wxEXPAND,0);

	auto link_btn = new ToggleBitmap(panel, context, "audio/opt/vertical_link", 16, "Audio", wxSize(20, -1));
	link_btn->SetMaxSize(wxDefaultSize);
	VertVolArea->Add(link_btn, 0, wxRIGHT | wxEXPAND, 0);
	OPT_SUB("Audio/Link", &AudioBox::OnVerticalLink, this);

	// Top sizer
	wxSizer *TopSizer = new wxBoxSizer(wxHORIZONTAL);
	TopSizer->Add(audioDisplay,1,wxEXPAND,0);
	TopSizer->Add(HorizontalZoom,0,wxEXPAND,0);
	TopSizer->Add(VertVolArea,0,wxEXPAND,0);

	context->karaoke = new AudioKaraoke(panel, context);

	// Main sizer
	auto MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->Add(TopSizer,1,wxEXPAND|wxALL,3);
	MainSizer->Add(toolbar::GetToolbar(panel, "audio", context, "Audio"),0,wxEXPAND|wxLEFT|wxRIGHT,3);
	MainSizer->Add(context->karaoke,0,wxEXPAND|wxALL,3);
	MainSizer->Show(context->karaoke, false);
	panel->SetSizer(MainSizer);

	wxSizer *audioSashSizer = new wxBoxSizer(wxHORIZONTAL);
	audioSashSizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(audioSashSizer);
	SetMinSize(wxSize(-1, OPT_GET("Audio/Display Height")->GetInt()));
	SetMinimumSizeY(panel->GetSize().GetHeight());

	audioDisplay->Bind(wxEVT_MOUSEWHEEL, &AudioBox::OnMouseWheel, this);

	audioDisplay->SetZoomLevel(-HorizontalZoom->GetValue());
	audioDisplay->SetAmplitudeScale(pow(mid(1, VerticalZoom->GetValue(), 100) / 50.0, 3));
}