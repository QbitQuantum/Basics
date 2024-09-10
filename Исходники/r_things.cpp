void R_InitSkins (void)
{
	char sndname[128];
	int sndlumps[8];
	char key[10];
	int intname;
	size_t i;
	int j, k, base;
	int stop;
	char *def;

	key[9] = 0;

	for (i = 1; i < numskins; i++)
	{
		for (j = 0; j < 8; j++)
			sndlumps[j] = -1;
		base = W_CheckNumForName ("S_SKIN", skins[i].namespc);
		// The player sprite has 23 frames. This means that the S_SKIN
		// marker needs a minimum of 23 lumps after it (probably more).
		if (base + 23 >= (int)numlumps || base == -1)
			continue;
		def = (char *)W_CacheLumpNum (base, PU_CACHE);
		intname = 0;

		// Data is stored as "key = data".
		while ( (def = COM_Parse (def)) )
		{
			strncpy (key, com_token, 9);
			def = COM_Parse (def);
			if (com_token[0] != '=')
			{
				Printf (PRINT_HIGH, "Bad format for skin %d: %s %s", i, key, com_token);
				break;
			}
			def = COM_Parse (def);
			if (!stricmp (key, "name")) {
				strncpy (skins[i].name, com_token, 16);
			} else if (!stricmp (key, "sprite")) {
				for (j = 3; j >= 0; j--)
					com_token[j] = toupper (com_token[j]);
				intname = *((int *)com_token);
			} else if (!stricmp (key, "face")) {
				for (j = 2; j >= 0; j--)
					skins[i].face[j] = toupper (com_token[j]);
			} else {
				for (j = 0; j < 8; j++) {
					if (!stricmp (key, skinsoundnames[j][0])) {
						// Can't use W_CheckNumForName because skin sounds
						// haven't been assigned a namespace yet.
						for (k = base + 1; k < (int)numlumps &&
										   lumpinfo[k].handle == lumpinfo[base].handle; k++) {
							if (!strnicmp (com_token, lumpinfo[k].name, 8)) {
								//W_SetLumpNamespace (k, skins[i].namespc);
								sndlumps[j] = k;
								break;
							}
						}
						if (sndlumps[j] == -1) {
							// Replacement not found, try finding it in the global namespace
							sndlumps[j] = W_CheckNumForName (com_token);
						}
						break;
					}
				}
				//if (j == 8)
				//	Printf (PRINT_HIGH, "Funny info for skin %i: %s = %s\n", i, key, com_token);
			}
		}

		if (skins[i].name[0] == 0)
			sprintf (skins[i].name, "skin%d", (unsigned)i);

		// Register any sounds this skin provides
		for (j = 0; j < 8; j++) {
			if (sndlumps[j] != -1) {
				if (j > 1) {
					sprintf (sndname, "player/%s/%s", skins[i].name, skinsoundnames[j][1]);
					S_AddSoundLump (sndname, sndlumps[j]);
				} else if (j == 1) {
					int r;

					for (r = 1; r <= 4; r++) {
						sprintf (sndname, "player/%s/death%d", skins[i].name, r);
						S_AddSoundLump (sndname, sndlumps[j]);
					}
				} else {	// j == 0
					int l, r;

					for (l =  1; l <= 4; l++)
						for (r = 1; r <= 2; r++) {
							sprintf (sndname, "player/%s/pain%d_%d", skins[i].name, l*25, r);
							S_AddSoundLump (sndname, sndlumps[j]);
						}
				}
			}
		}

		// Now collect the sprite frames for this skin. If the sprite name was not
		// specified, use whatever immediately follows the specifier lump.
		if (intname == 0) {
			intname = *(int *)(lumpinfo[base+1].name);
			for (stop = base + 2; stop < (int)numlumps &&
								  lumpinfo[stop].handle == lumpinfo[base].handle &&
								  *(int *)lumpinfo[stop].name == intname; stop++)
				;
		} else {
			stop = numlumps;
		}

		memset (sprtemp, -1, sizeof(sprtemp));
		maxframe = -1;

		for (k = base + 1;
			 k < stop && lumpinfo[k].handle == lumpinfo[base].handle;
			 k++) {
			if (*(int *)lumpinfo[k].name == intname)
			{
				R_InstallSpriteLump (k,
									 lumpinfo[k].name[4] - 'A', // denis - fixme - security
									 lumpinfo[k].name[5] - '0',
									 false);

				if (lumpinfo[k].name[6])
					R_InstallSpriteLump (k,
									 lumpinfo[k].name[6] - 'A',
									 lumpinfo[k].name[7] - '0',
									 true);

				//W_SetLumpNamespace (k, skins[i].namespc);
			}
		}
		R_InstallSprite ((char *)&intname, (skins[i].sprite = (spritenum_t)(numsprites - numskins + i)));

		// Now go back and check for face graphics (if necessary)
		if (skins[i].face[0] == 0 || skins[i].face[1] == 0 || skins[i].face[2] == 0) {
			// No face name specified, so this skin doesn't replace it
			skins[i].face[0] = 0;
		} else {
			// Need to go through and find all face graphics for the skin
			// and assign them to the skin's namespace.
			for (j = 0; j < 8; j++)
				strncpy (facenames[j], skins[i].face, 3);

			for (k = base + 1;
				 k < (int)numlumps && lumpinfo[k].handle == lumpinfo[base].handle;
				 k++) {
				for (j = 0; j < 8; j++)
					if (!strncmp (facenames[j], lumpinfo[k].name, facelens[j])) {
						//W_SetLumpNamespace (k, skins[i].namespc);
						break;
					}
			}
		}
	}
	// Grrk. May have changed sound table. Fix it.
	if (numskins > 1)
		S_HashSounds ();
}