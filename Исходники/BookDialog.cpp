// ID_BOOK_PICKER
void BookDialog::OnFilePicked( wxFileDirPickerEvent& event )
{
    wxString file = event.GetPath();
    dat.m_file = file;
}