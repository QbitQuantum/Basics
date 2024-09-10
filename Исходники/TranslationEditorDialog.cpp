/* TranslationEditorDialog::onBtnLoad
 * Called when the 'Load Translation' button is clicked
 *******************************************************************/
void TranslationEditorDialog::onBtnLoad(wxCommandEvent& e)
{
	// Get user directory
	string dir = appPath("translations", DIR_USER);

	// Create open file dialog
	wxFileDialog dialog_open(this, "Load Translation from File", dir, wxEmptyString,
	                         "Text Files (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST, wxDefaultPosition);

	// Run the dialog & check that the user didn't cancel
	if (dialog_open.ShowModal() == wxID_OK)
	{
		// Get the selected filename
		string filename = dialog_open.GetPath();

		// Load file in a tokenizer
		Tokenizer tz;
		tz.openFile(dialog_open.GetPath());

		// Parse translation
		Translation trans;
		string token = tz.getToken();
		while (!token.IsEmpty())
		{
			// Parse translation range
			trans.parse(token);

			tz.getToken();			// Skip ,
			token = tz.getToken();
		}

		// Open it if parsed ok
		if (trans.nRanges() > 0)
			openTranslation(trans);
		else
			wxMessageBox("Not a valid translation file", "Error", wxICON_ERROR);
	}
}