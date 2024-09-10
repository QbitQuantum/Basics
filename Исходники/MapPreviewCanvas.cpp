/* MapPreviewCanvas::openMap
 * Opens a map from a mapdesc_t
 *******************************************************************/
bool MapPreviewCanvas::openMap(Archive::mapdesc_t map)
{
	// All errors = invalid map
	Global::error = "Invalid map";

	// Check if this map is a pk3 map
	bool map_archive = false;
	if (map.archive)
	{
		map_archive = true;

		// Attempt to open entry as wad archive
		temp_archive = new WadArchive();
		if (!temp_archive->open(map.head))
		{
			delete temp_archive;
			return false;
		}

		// Detect maps
		vector<Archive::mapdesc_t> maps = temp_archive->detectMaps();

		// Set map if there are any in the archive
		if (maps.size() > 0)
			map = maps[0];
		else
			return false;
	}

	// Parse UDMF map
	if (map.format == MAP_UDMF)
	{
		ArchiveEntry* udmfdata = NULL;
		for (ArchiveEntry* mapentry = map.head; mapentry != map.end; mapentry = mapentry->nextEntry())
		{
			// Check entry type
			if (mapentry->getType() == EntryType::getType("udmf_textmap"))
			{
				udmfdata = mapentry;
				break;
			}
		}
		if (udmfdata == NULL)
			return false;

		// Start parsing
		Tokenizer tz;
		tz.openMem(udmfdata->getData(), udmfdata->getSize(), map.head->getName());

		// Get first token
		string token = tz.getToken();
		size_t vertcounter = 0, linecounter = 0;
		while (!token.IsEmpty())
		{
			if (!token.CmpNoCase("namespace"))
			{
				//  skip till we reach the ';'
				do { token = tz.getToken(); }
				while (token.Cmp(";"));
			}
			else if (!token.CmpNoCase("vertex"))
			{
				// Get X and Y properties
				bool gotx = false;
				bool goty = false;
				double x = 0.;
				double y = 0.;
				do
				{
					token = tz.getToken();
					if (!token.CmpNoCase("x") || !token.CmpNoCase("y"))
					{
						bool isx = !token.CmpNoCase("x");
						token = tz.getToken();
						if (token.Cmp("="))
						{
							wxLogMessage("Bad syntax for vertex %i in UDMF map data", vertcounter);
							return false;
						}
						if (isx) x = tz.getDouble(), gotx = true;
						else y = tz.getDouble(), goty = true;
						// skip to end of declaration after each key
						do { token = tz.getToken(); }
						while (token.Cmp(";"));
					}
				}
				while (token.Cmp("}"));
				if (gotx && goty)
					addVertex(x, y);
				else
				{
					wxLogMessage("Wrong vertex %i in UDMF map data", vertcounter);
					return false;
				}
				vertcounter++;
			}
			else if (!token.CmpNoCase("linedef"))
			{
				bool special = false;
				bool twosided = false;
				bool gotv1 = false, gotv2 = false;
				size_t v1 = 0, v2 = 0;
				do
				{
					token = tz.getToken();
					if (!token.CmpNoCase("v1") || !token.CmpNoCase("v2"))
					{
						bool isv1 = !token.CmpNoCase("v1");
						token = tz.getToken();
						if (token.Cmp("="))
						{
							wxLogMessage("Bad syntax for linedef %i in UDMF map data", linecounter);
							return false;
						}
						if (isv1) v1 = tz.getInteger(), gotv1 = true;
						else v2 = tz.getInteger(), gotv2 = true;
						// skip to end of declaration after each key
						do { token = tz.getToken(); }
						while (token.Cmp(";"));
					}
					else if (!token.CmpNoCase("special"))
					{
						special = true;
						// skip to end of declaration after each key
						do { token = tz.getToken(); }
						while (token.Cmp(";"));
					}
					else if (!token.CmpNoCase("sideback"))
					{
						twosided = true;
						// skip to end of declaration after each key
						do { token = tz.getToken(); }
						while (token.Cmp(";"));
					}
				}
				while (token.Cmp("}"));
				if (gotv1 && gotv2)
					addLine(v1, v2, twosided, special);
				else
				{
					wxLogMessage("Wrong line %i in UDMF map data", linecounter);
					return false;
				}
				linecounter++;
			}
			else
			{
				// map preview ignores things, sidedefs, sectors, comments,
				// unknown fields, etc. so skip to end of block
				do { token = tz.getToken(); }
				while (token.Cmp("}"));
			}
			// Iterate to next token
			token = tz.getToken();
		}
	}

	// Read vertices
	if (map.format == MAP_DOOM || map.format == MAP_HEXEN || map.format == MAP_DOOM64)
	{
		// Find VERTEXES entry
		ArchiveEntry* mapentry = map.head;
		ArchiveEntry* vertexes = NULL;
		while (mapentry)
		{
			// Check entry type
			if (mapentry->getType() == EntryType::getType("map_vertexes"))
			{
				vertexes = mapentry;
				break;
			}

			// Exit loop if we've reached the end of the map entries
			if (mapentry == map.end)
				break;
			else
				mapentry = mapentry->nextEntry();
		}

		// Can't open a map without vertices
		if (!vertexes)
			return false;

		// Read vertex data
		MemChunk& mc = vertexes->getMCData();
		mc.seek(0, SEEK_SET);

		if (map.format == MAP_DOOM64)
		{
			doom64vertex_t v;
			while (1)
			{
				// Read vertex
				if (!mc.read(&v, 8))
					break;

				// Add vertex
				addVertex((double)v.x/65536, (double)v.y/65536);
			}
		}
		else
		{
			doomvertex_t v;
			while (1)
			{
				// Read vertex
				if (!mc.read(&v, 4))
					break;

				// Add vertex
				addVertex((double)v.x, (double)v.y);
			}
		}
	}


	// Read linedefs
	if (map.format == MAP_DOOM || map.format == MAP_HEXEN || map.format == MAP_DOOM64)
	{
		// Find LINEDEFS entry
		ArchiveEntry* mapentry = map.head;
		ArchiveEntry* linedefs = NULL;
		while (mapentry)
		{
			// Check entry type
			if (mapentry->getType() == EntryType::getType("map_linedefs"))
			{
				linedefs = mapentry;
				break;
			}

			// Exit loop if we've reached the end of the map entries
			if (mapentry == map.end)
				break;
			else
				mapentry = mapentry->nextEntry();
		}

		// Can't open a map without linedefs
		if (!linedefs)
			return false;

		// Read line data
		MemChunk& mc = linedefs->getMCData();
		mc.seek(0, SEEK_SET);
		if (map.format == MAP_DOOM)
		{
			while (1)
			{
				// Read line
				doomline_t l;
				if (!mc.read(&l, sizeof(doomline_t)))
					break;

				// Check properties
				bool special = false;
				bool twosided = false;
				if (l.side2 != 0xFFFF)
					twosided = true;
				if (l.type > 0)
					special = true;

				// Add line
				addLine(l.vertex1, l.vertex2, twosided, special);
			}
		}
		else if (map.format == MAP_DOOM64)
		{
			while (1)
			{
				// Read line
				doom64line_t l;
				if (!mc.read(&l, sizeof(doom64line_t)))
					break;

				// Check properties
				bool macro = false;
				bool special = false;
				bool twosided = false;
				if (l.side2  != 0xFFFF)
					twosided = true;
				if (l.type > 0)
				{
					if (l.type & 0x100)
						macro = true;
					else special = true;
				}

				// Add line
				addLine(l.vertex1, l.vertex2, twosided, special, macro);
			}
		}
		else if (map.format == MAP_HEXEN)
		{
			while (1)
			{
				// Read line
				hexenline_t l;
				if (!mc.read(&l, sizeof(hexenline_t)))
					break;

				// Check properties
				bool special = false;
				bool twosided = false;
				if (l.side2 != 0xFFFF)
					twosided = true;
				if (l.type > 0)
					special = true;

				// Add line
				addLine(l.vertex1, l.vertex2, twosided, special);
			}
		}
	}

	// Clean up
	if (map_archive)
	{
		temp_archive->close();
		delete temp_archive;
		temp_archive = NULL;
	}

	// Refresh map
	Refresh();

	return true;
}