/* TextureXPanel::exportTexture
 * Create standalone image entries of any selected textures
 *******************************************************************/
void TextureXPanel::exportTexture()
{
	// Get selected textures
	vector<long> selec_num = list_textures->getSelection();
	vector<CTexture*> selection;

	if (!tx_entry) return;

	//saveTEXTUREX();

	Archive* archive = tx_entry->getParent();
	bool force_rgba = texture_editor->getBlendRGBA();

	// Go through selection
	for (unsigned a = 0; a < selec_num.size(); ++a)
	{
		selection.push_back(texturex.getTexture(selec_num[a]));
	}

	// Create gfx conversion dialog
	GfxConvDialog gcd(this);

	// Send selection to the gcd
	gcd.openTextures(selection, texture_editor->getPalette(), archive, force_rgba);

	// Run the gcd
	gcd.ShowModal();

	// Show splash window
	theSplashWindow->show("Writing converted image data...", true);

	// Write any changes
	for (unsigned a = 0; a < selection.size(); a++)
	{
		// Update splash window
		theSplashWindow->setProgressMessage(selection[a]->getName());
		theSplashWindow->setProgress((float)a / (float)selection.size());

		// Skip if the image wasn't converted
		if (!gcd.itemModified(a))
			continue;

		// Get image and conversion info
		SImage* image = gcd.getItemImage(a);
		SIFormat* format = gcd.getItemFormat(a);

		// Write converted image back to entry
		MemChunk mc;
		format->saveImage(*image, mc, force_rgba ? NULL : gcd.getItemPalette(a));
		ArchiveEntry* lump = new ArchiveEntry;
		lump->importMemChunk(mc);
		lump->rename(selection[a]->getName());
		archive->addEntry(lump, "textures");
		EntryType::detectEntryType(lump);
		lump->setExtensionByType();
	}

	// Hide splash window
	theSplashWindow->hide();
}