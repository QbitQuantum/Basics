void LoadWadconfig (const char *filename, const char *configname)
{
	int found = 0;
	int count = 0;
	int size;
	char *buffer;
	size = LoadFile (filename, &buffer);
	ParseFromMemory (buffer, size);
	while (GetToken (true))
	{
		bool skip = true;
		if (!stricmp (g_token, configname))
		{
			skip = false;
			found++;
		}
		if (!GetToken (true) || stricmp (g_token, "{"))
		{
			Error ("parsing '%s': missing '{'.", filename);
		}
		while (1)
		{
			if (!GetToken (true))
			{
				Error ("parsing '%s': unexpected end of file.", filename);
			}
			if (!stricmp (g_token, "}"))
			{
				break;
			}
			if (skip)
			{
				continue;
			}
			bool include = false;
			wadpath_t *current;
			if (!stricmp (g_token, "include"))
			{
				include = true;
				if (!GetToken (true))
				{
					Error ("parsing '%s': unexpected end of file.", filename);
				}
			}
			Developer (DEVELOPER_LEVEL_MESSAGE, "LoadWadconfig: adding wad file '%s'.\n", g_token);
			if (g_iNumWadPaths >= MAX_WADPATHS)
			{
				Error ("parsing '%s': too many wad files.", filename);
			}
			count++;
			current = (wadpath_t *)malloc (sizeof (wadpath_t));
			hlassume (current != NULL, assume_NoMemory);
			g_pWadPaths[g_iNumWadPaths] = current;
			g_iNumWadPaths++;
			safe_strncpy (current->path, g_token, _MAX_PATH);
			current->usedbymap = true; // what's this?
			current->usedtextures = 0;
			if (include)
			{
				Developer (DEVELOPER_LEVEL_MESSAGE, "LoadWadcfgfile: including '%s'.\n", current->path);
				g_WadInclude.push_back(current->path);
			}
		}
	}
	if (found == 0)
	{
		Error ("Couldn't find wad configuration '%s' in file '%s'.\n", configname, filename);
	}
	if (found >= 2)
	{
		Error ("Found more than one wad configuration for '%s' in file '%s'.\n", configname, filename);
	}
	free (buffer); // should not be freed because it is still being used as script buffer
	Log ("Using custom wadfile configuration: '%s' (with %i wad%s)\n", configname, count, count > 1 ? "s" : "");
}