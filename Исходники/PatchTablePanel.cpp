/* PatchTablePanel::updateDisplay
 * Called when a different patch or palette is selected
 * TODO: Separate palette changed and patch changed without breaking
 * default palette display; optimize label_textures display
 *******************************************************************/
void PatchTablePanel::updateDisplay()
{
	// Get selected patch
	patch_t& patch = patch_table->patch(list_patches->getLastSelected());

	// Load the image
	ArchiveEntry* entry = patch_table->patchEntry(list_patches->getLastSelected());
	if (Misc::loadImageFromEntry(patch_canvas->getImage(), entry))
	{
		theMainWindow->getPaletteChooser()->setGlobalFromArchive(entry->getParent());
		patch_canvas->setPalette(theMainWindow->getPaletteChooser()->getSelectedPalette());
		label_dimensions->SetLabel(S_FMT("Size: %d x %d", patch_canvas->getImage()->getWidth(), patch_canvas->getImage()->getHeight()));
	}
	else
	{
		patch_canvas->getImage()->clear();
		label_dimensions->SetLabel("Size: ? x ?");
	}
	patch_canvas->Refresh();

	// List which textures use this patch
	if (patch.used_in.size() > 0)
	{
		string alltextures = "";
		int count = 0;
		string previous = "";
		for (size_t a = 0; a < patch.used_in.size(); ++a)
		{
			string current = patch.used_in[a];

			// Is the use repeated for the same texture?
			if (!current.CmpNoCase(previous))
			{
				count++;
				// Else it's a new texture
			}
			else
			{
				// First add the count to the previous texture if needed
				if (count)
				{
					alltextures += S_FMT(" (%i)", count + 1);
					count = 0;
				}

				// Add a separator if appropriate
				if (a > 0)
					alltextures += ';';

				// Then print the new texture's name
				alltextures += S_FMT(" %s", patch.used_in[a].mb_str());

				// And set it for comparison with the next one
				previous = current;
			}
		}
		// If count is still non-zero, it's because the patch was repeated in the last texture
		if (count)
			alltextures += S_FMT(" (%i)", count + 1);

		// Finally display the listing
		label_textures->SetLabel(S_FMT("In Textures:%s", alltextures.mb_str()));
	}
	else
		label_textures->SetLabel("In Textures: -");

	// Wrap the text label
	label_textures->Wrap(label_textures->GetSize().GetWidth());

	// Update layout
	Layout();
}