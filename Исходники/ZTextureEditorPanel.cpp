/* ZTextureEditorPanel::onBtnEditTranslation
 * Called when the 'Edit' translation button is pressed
 *******************************************************************/
void ZTextureEditorPanel::onBtnEditTranslation(wxCommandEvent& e)
{
	// Get selected patches
	wxArrayInt selection = list_patches->selectedItems();

	// Do nothing if no patches selected
	if (selection.size() == 0)
		return;

	// Get translation from first selected patch
	Translation trans;
	CTPatchEx* patch = (CTPatchEx*)tex_current->getPatch(selection[0]);
	trans.copy(patch->getTranslation());

	// Add palette range if no translation ranges exist
	if (trans.nRanges() == 0)
		trans.addRange(TRANS_PALETTE, 0);

	// Create patch image
	SImage image(PALMASK);
	tex_canvas->getTexture()->loadPatchImage(selection[0], image, tx_editor->getArchive(), tex_canvas->getPalette());

	// Open translation editor dialog
	TranslationEditorDialog ted(theMainWindow, tex_canvas->getPalette(), "Edit Translation", &image);
	ted.openTranslation(trans);
	if (ted.ShowModal() == wxID_OK)
	{
		// Copy updated translation to all selected patches
		for (unsigned a = 0; a < selection.size(); a++)
		{
			CTPatchEx* patchx = (CTPatchEx*)tex_current->getPatch(selection[a]);
			patchx->getTranslation().copy(ted.getTranslation());
		}

		// Update UI
		updatePatchControls();
		tex_canvas->redraw(true);

		tex_modified = true;
	}
}