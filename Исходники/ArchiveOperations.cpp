void ArchiveOperations::removeUnusedTextures(Archive* archive)
{
	// Check archive was given
	if (!archive)
		return;

	// --- Build list of used textures ---
	TexUsedMap used_textures;
	int        total_maps = 0;

	// Get all SIDEDEFS entries
	Archive::SearchOptions opt;
	opt.match_type = EntryType::fromId("map_sidedefs");
	auto sidedefs  = archive->findAll(opt);
	total_maps += sidedefs.size();

	// Go through and add used textures to list
	DoomMapFormat::SideDef sdef;
	wxString               tex_lower, tex_middle, tex_upper;
	for (auto& sidedef : sidedefs)
	{
		int nsides = sidedef->size() / 30;
		sidedef->seek(0, SEEK_SET);
		for (int s = 0; s < nsides; s++)
		{
			// Read side data
			sidedef->read(&sdef, 30);

			// Get textures
			tex_lower  = wxString::FromAscii(sdef.tex_lower, 8);
			tex_middle = wxString::FromAscii(sdef.tex_middle, 8);
			tex_upper  = wxString::FromAscii(sdef.tex_upper, 8);

			// Add to used textures list
			used_textures[tex_lower].used  = true;
			used_textures[tex_middle].used = true;
			used_textures[tex_upper].used  = true;
		}
	}

	// Get all TEXTMAP entries
	opt.match_name = "TEXTMAP";
	opt.match_type = EntryType::fromId("udmf_textmap");
	auto udmfmaps  = archive->findAll(opt);
	total_maps += udmfmaps.size();

	// Go through and add used textures to list
	Tokenizer tz;
	tz.setSpecialCharacters("{};=");
	for (auto& udmfmap : udmfmaps)
	{
		// Open in tokenizer
		tz.openMem(udmfmap->data(), "UDMF TEXTMAP");

		// Go through text tokens
		wxString token = tz.getToken();
		while (!token.IsEmpty())
		{
			// Check for sidedef definition
			if (token == "sidedef")
			{
				tz.getToken(); // Skip {

				token = tz.getToken();
				while (token != "}")
				{
					// Check for texture property
					if (token == "texturetop" || token == "texturemiddle" || token == "texturebottom")
					{
						tz.getToken(); // Skip =
						used_textures[tz.getToken()].used = true;
					}

					token = tz.getToken();
				}
			}

			// Next token
			token = tz.getToken();
		}
	}

	// Check if any maps were found
	if (total_maps == 0)
		return;

	// Find all TEXTUREx entries
	opt.match_name  = "";
	opt.match_type  = EntryType::fromId("texturex");
	auto tx_entries = archive->findAll(opt);

	// Go through texture lists
	PatchTable    ptable; // Dummy patch table, patch info not needed here
	wxArrayString unused_tex;
	for (auto& tx_entrie : tx_entries)
	{
		TextureXList txlist;
		txlist.readTEXTUREXData(tx_entrie, ptable);

		// Go through textures
		bool anim = false;
		for (unsigned t = 1; t < txlist.size(); t++)
		{
			wxString texname = txlist.texture(t)->name();

			// Check for animation start
			for (int b = 0; b < n_tex_anim; b++)
			{
				if (texname == tex_anim_start[b])
				{
					anim = true;
					break;
				}
			}

			// Check for animation end
			bool thisend = false;
			for (int b = 0; b < n_tex_anim; b++)
			{
				if (texname == tex_anim_end[b])
				{
					anim    = false;
					thisend = true;
					break;
				}
			}

			// Mark if unused and not part of an animation
			if (!used_textures[texname].used && !anim && !thisend)
				unused_tex.Add(txlist.texture(t)->name());
		}
	}

	// Pop up a dialog with a checkbox list of unused textures
	wxMultiChoiceDialog dialog(
		theMainWindow,
		"The following textures are not used in any map,\nselect which textures to delete",
		"Delete Unused Textures",
		unused_tex);

	// Get base resource textures (if any)
	auto                  base_resource = App::archiveManager().baseResourceArchive();
	vector<ArchiveEntry*> base_tx_entries;
	if (base_resource)
		base_tx_entries = base_resource->findAll(opt);
	PatchTable   pt_temp;
	TextureXList tx;
	for (auto& texturex : base_tx_entries)
		tx.readTEXTUREXData(texturex, pt_temp, true);
	vector<wxString> base_resource_textures;
	for (unsigned a = 0; a < tx.size(); a++)
		base_resource_textures.push_back(tx.texture(a)->name());

	// Determine which textures to check initially
	wxArrayInt selection;
	for (unsigned a = 0; a < unused_tex.size(); a++)
	{
		bool swtex = false;

		// Check for switch texture
		if (unused_tex[a].StartsWith("SW1"))
		{
			// Get counterpart switch name
			wxString swname = unused_tex[a];
			swname.Replace("SW1", "SW2", false);

			// Check if its counterpart is used
			if (used_textures[swname].used)
				swtex = true;
		}
		else if (unused_tex[a].StartsWith("SW2"))
		{
			// Get counterpart switch name
			wxString swname = unused_tex[a];
			swname.Replace("SW2", "SW1", false);

			// Check if its counterpart is used
			if (used_textures[swname].used)
				swtex = true;
		}

		// Check for base resource texture
		bool br_tex = false;
		for (auto& texture : base_resource_textures)
		{
			if (texture.CmpNoCase(unused_tex[a]) == 0)
			{
				Log::info(3, "Texture " + texture + " is in base resource");
				br_tex = true;
				break;
			}
		}

		if (!swtex && !br_tex)
			selection.Add(a);
	}
	dialog.SetSelections(selection);

	int n_removed = 0;
	if (dialog.ShowModal() == wxID_OK)
	{
		// Get selected textures
		selection = dialog.GetSelections();

		// Go through texture lists
		for (auto& entry : tx_entries)
		{
			TextureXList txlist;
			txlist.readTEXTUREXData(entry, ptable);

			// Go through selected textures to delete
			for (int i : selection)
			{
				// Get texture index
				int index = txlist.textureIndex(WxUtils::strToView(unused_tex[i]));

				// Delete it from the list (if found)
				if (index >= 0)
				{
					txlist.removeTexture(index);
					n_removed++;
				}
			}

			// Write texture list data back to entry
			txlist.writeTEXTUREXData(entry, ptable);
		}
	}

	wxMessageBox(wxString::Format("Removed %d unused textures", n_removed));
}