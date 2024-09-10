void CreateCodeDialog::PressOK(wxCommandEvent& ev)
{
	const wxString code_name = textctrl_name->GetValue();
	if (code_name.empty())
	{
		PanicAlertT("You must enter a name!");
		return;
	}

	long code_value;
	if (!textctrl_value->GetValue().ToLong(&code_value, 10 + checkbox_use_hex->GetValue()*6))
	{
		PanicAlertT("Invalid Value!");
		return;
	}

	//wxString full_code = textctrl_code->GetValue();
	//full_code += wxT(' ');
	//full_code += wxString::Format(wxT("0x%08x"), code_value);

	// create the new code
	ActionReplay::ARCode new_cheat;
	new_cheat.active = false;
	new_cheat.name = std::string(code_name.ToAscii());
	const ActionReplay::AREntry new_entry(code_address, code_value);
	new_cheat.ops.push_back(new_entry);

	// pretty hacky - add the code to the gameini
	{
	CISOProperties isoprops(SConfig::GetInstance().m_LastFilename, this);
	// add the code to the isoproperties arcode list
	arCodes.push_back(new_cheat);
	// save the gameini
	isoprops.SaveGameConfig();
	isoprops.ActionReplayList_Load();	// loads the new arcodes
	//ActionReplay::UpdateActiveList();
	}

	// refresh arcode list in other tab
	::g_cheat_window->Load_ARCodes();

	Close();
}