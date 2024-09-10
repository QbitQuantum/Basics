DialogStyling::DialogStyling(agi::Context *context)
: wxDialog(context->parent, -1, _("Styling Assistant"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxMINIMIZE_BOX)
, c(context)
, active_line_connection(context->selectionController->AddActiveLineListener(&DialogStyling::OnActiveLineChanged, this))
, active_line(nullptr)
{
	SetIcon(GETICON(styling_toolbutton_16));

	wxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);
	wxSizer *bottom_sizer = new wxBoxSizer(wxHORIZONTAL);

	{
		wxSizer *cur_line_box = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Current line"));
		current_line_text = new wxTextCtrl(this, -1, _("Current line"), wxDefaultPosition, wxSize(300, 60), wxTE_MULTILINE | wxTE_READONLY);
		cur_line_box->Add(current_line_text, 1, wxEXPAND, 0);
		main_sizer->Add(cur_line_box, 0, wxEXPAND | wxALL, 5);
	}

	{
		wxSizer *styles_box = new wxStaticBoxSizer(wxVERTICAL, this, _("Styles available"));
		style_list = new wxListBox(this, -1, wxDefaultPosition, wxSize(150, 180), to_wx(context->ass->GetStyles()));
		styles_box->Add(style_list, 1, wxEXPAND, 0);
		bottom_sizer->Add(styles_box, 1, wxEXPAND | wxRIGHT, 5);
	}

	wxSizer *right_sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxSizer *style_text_box = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Set style"));
		style_name = new wxTextCtrl(this, -1, "", wxDefaultPosition, wxSize(180, -1), wxTE_PROCESS_ENTER);
		style_text_box->Add(style_name, 1, wxEXPAND);
		right_sizer->Add(style_text_box, 0, wxEXPAND | wxBOTTOM, 5);
	}

	{
		wxSizer *hotkey_box = new wxStaticBoxSizer(wxVERTICAL, this, _("Keys"));

		wxSizer *hotkey_grid = new wxGridSizer(2, 0, 5);
		add_hotkey(hotkey_grid, this, "tool/styling_assistant/commit", _("Accept changes"));
		add_hotkey(hotkey_grid, this, "tool/styling_assistant/preview", _("Preview changes"));
		add_hotkey(hotkey_grid, this, "grid/line/prev", _("Previous line"));
		add_hotkey(hotkey_grid, this, "grid/line/next", _("Next line"));
		add_hotkey(hotkey_grid, this, "video/play/line", _("Play video"));
		add_hotkey(hotkey_grid, this, "audio/play/selection", _("Play audio"));
		hotkey_grid->Add(new wxStaticText(this, -1, _("Click on list")));
		hotkey_grid->Add(new wxStaticText(this, -1, _("Select style")));

		hotkey_box->Add(hotkey_grid, 0, wxEXPAND | wxBOTTOM, 5);

		auto_seek = new wxCheckBox(this, -1, _("&Seek video to line start time"));
		auto_seek->SetValue(true);
		hotkey_box->Add(auto_seek, 0, 0, 0);
		hotkey_box->AddStretchSpacer(1);

		right_sizer->Add(hotkey_box, 0, wxEXPAND | wxBOTTOM, 5);
	}

	{
		wxSizer *actions_box = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Actions"));
		actions_box->AddStretchSpacer(1);

		play_audio = new wxButton(this, -1, _("Play &Audio"));
		play_audio->Enable(c->audioController->IsAudioOpen());
		actions_box->Add(play_audio, 0, wxLEFT | wxRIGHT | wxBOTTOM, 5);

		play_video = new wxButton(this, -1, _("Play &Video"));
		play_video->Enable(c->videoController->IsLoaded());
		actions_box->Add(play_video, 0, wxBOTTOM | wxRIGHT, 5);

		actions_box->AddStretchSpacer(1);
		right_sizer->Add(actions_box, 0, wxEXPAND, 5);
	}
	bottom_sizer->Add(right_sizer);
	main_sizer->Add(bottom_sizer, 1, wxEXPAND | wxLEFT | wxBOTTOM | wxRIGHT, 5);

	{
		auto button_sizer = new wxStdDialogButtonSizer;
		button_sizer->AddButton(new wxButton(this, wxID_CANCEL));
		button_sizer->AddButton(new HelpButton(this, "Styling Assistant"));
		button_sizer->Realize();

		main_sizer->Add(button_sizer, 0, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 5);
	}

	SetSizerAndFit(main_sizer);

	persist = agi::util::make_unique<PersistLocation>(this, "Tool/Styling Assistant");

	Bind(wxEVT_ACTIVATE, &DialogStyling::OnActivate, this);
	Bind(wxEVT_CHAR_HOOK, &DialogStyling::OnCharHook, this);
	style_name->Bind(wxEVT_CHAR_HOOK, &DialogStyling::OnCharHook, this);
	style_name->Bind(wxEVT_KEY_DOWN, &DialogStyling::OnKeyDown, this);
	play_video->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &DialogStyling::OnPlayVideoButton, this);
	play_audio->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &DialogStyling::OnPlayAudioButton, this);
	style_list->Bind(wxEVT_COMMAND_LISTBOX_SELECTED, &DialogStyling::OnListClicked, this);
	style_list->Bind(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, &DialogStyling::OnListDoubleClicked, this);
	style_name->Bind(wxEVT_COMMAND_TEXT_UPDATED, &DialogStyling::OnStyleBoxModified, this);

	OnActiveLineChanged(c->selectionController->GetActiveLine());
}