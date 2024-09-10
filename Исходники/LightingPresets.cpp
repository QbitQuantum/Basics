void LightingPresets::Reset() {
	wxRadioButton* presetsOffButton =
		dynamic_cast<wxRadioButton*>(wxWindow::FindWindowById(ID_PRESETS_OFF, this));
	wxCHECK_RET( presetsOffButton != NULL, _T("Unable to find lighting presets off radio button"));
	presetsOffButton->SetValue(true);
	
	wxCommandEvent resetEvent(wxEVT_COMMAND_RADIOBUTTON_SELECTED, ID_PRESETS_OFF);
	this->OnSelectLightingPreset(resetEvent);
}