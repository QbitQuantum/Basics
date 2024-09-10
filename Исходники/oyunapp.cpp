void OyunApp::ShowHelp(wxWindow *parent, const wxString &fileName)
{
	if (parent == NULL)
		parent = GetTopWindow();
	
	wxHtmlModalHelp help(parent, FS::GetDocPath(), fileName,
	                     wxHF_DEFAULT_STYLE | wxHF_DIALOG | wxHF_MODAL | wxHF_MERGE_BOOKS);
}