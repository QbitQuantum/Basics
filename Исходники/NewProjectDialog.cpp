//-------------------------------------------------------------------
void
NewProjectDialog::onLocationPicked(wxFileDirPickerEvent& event)
{
    _locationEntry->SetValue(event.GetPath());
}