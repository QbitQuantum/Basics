/* TextureXList::readTEXTURESData
 * Reads in a ZDoom-format TEXTURES entry. Returns true on success,
 * false otherwise
 *******************************************************************/
bool TextureXList::readTEXTURESData(ArchiveEntry* entry)
{
	// Check for empty entry
	if (!entry)
	{
		Global::error = "Attempt to read texture data from NULL entry";
		return false;
	}
	if (entry->getSize() == 0)
	{
		txformat = TXF_TEXTURES;
		return true;
	}

	// Get text to parse
	Tokenizer tz;
	tz.openMem(&(entry->getMCData()), entry->getName());

	// Parsing gogo
	string token = tz.getToken();
	while (!token.IsEmpty())
	{
		// Texture definition
		if (S_CMPNOCASE(token, "Texture"))
		{
			CTexture* tex = new CTexture();
			if (tex->parse(tz, "Texture"))
				addTexture(tex);
		}

		// Sprite definition
		if (S_CMPNOCASE(token, "Sprite"))
		{
			CTexture* tex = new CTexture();
			if (tex->parse(tz, "Sprite"))
				addTexture(tex);
		}

		// Graphic definition
		if (S_CMPNOCASE(token, "Graphic"))
		{
			CTexture* tex = new CTexture();
			if (tex->parse(tz, "Graphic"))
				addTexture(tex);
		}

		// WallTexture definition
		if (S_CMPNOCASE(token, "WallTexture"))
		{
			CTexture* tex = new CTexture();
			if (tex->parse(tz, "WallTexture"))
				addTexture(tex);
		}

		// Flat definition
		if (S_CMPNOCASE(token, "Flat"))
		{
			CTexture* tex = new CTexture();
			if (tex->parse(tz, "Flat"))
				addTexture(tex);
		}

		token = tz.getToken();
	}

	txformat = TXF_TEXTURES;

	return true;
}