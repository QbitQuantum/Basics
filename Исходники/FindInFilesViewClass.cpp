void t4p::FindInFilesDialogClass::OnDirChanged(wxFileDirPickerEvent& event) {
    wxString path = event.GetPath();

    // add the selected directory, but only if its not already in the list
    int index = Directory->FindString(path);
    if (wxNOT_FOUND != index && !path.IsEmpty()) {
        Directory->SetSelection(index);
    } else {
        int newIndex = Directory->Append(path);
        Directory->SetSelection(newIndex);
    }
}