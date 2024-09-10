static sfx_t *GetPlayerSound(clEntityState_t *ent, const char *base)
{
	clientInfo_t &ci = cl.clientInfo[ent->number - 1];	// may use ent->skinnum & 0xFF too ...
	bool isFemale = ci.modelGender == 'f';

	// see if we already know of the model specific sound
	TString<MAX_QPATH> LocalFilename;
	LocalFilename.sprintf("#players/%s/%s", *ci.ModelName, base+1);
	sfx_t *sfx = S_FindName(LocalFilename, false);
	if (sfx) return sfx;

	// try sound in Quake2 model directory ("players/[model_name]/[sound]")
	if (GFileSystem->FileExists(LocalFilename + 1))
	{
		sfx = S_RegisterSound(LocalFilename);
		if (sfx) return sfx;
	}

	// try sound in Quake3 model directory ("sound/player/[model_name]/[sound]")
	static const struct {
		const char *q2name, *q3name;
	} convert[] = {
		{"death4.wav",	 "death1.wav"},
		{"fall2.wav",	 "fall1.wav"},
		{"pain25_2.wav", "pain25_1.wav"},
		{"pain50_2.wav", "pain50_1.wav"},
		{"pain75_2.wav", "pain75_1.wav"},
		{"pain100_2.wav","pain100_1.wav"}
	};
	// Quake3 models have no some Quake2 sounds
	const char *newName = base + 1;
	for (int i = 0; i < ARRAY_COUNT(convert); i++)
		if (!stricmp(newName, convert[i].q2name))
		{
			newName = convert[i].q3name;
			break;
		}
	TString<MAX_QPATH> FileName2;
	FileName2.sprintf("sound/player/%s/%s", *ci.ModelName, newName);	// NOTE: used below as filename2+6 too
	if (GFileSystem->FileExists(FileName2))
	{
		sfx = S_AliasName(LocalFilename, FileName2 + 6 /* skip "sound/" */);
		if (sfx) return sfx;
	}

	// setup as default sound
	return S_AliasName(LocalFilename, va("player/%smale/%s", isFemale ? "fe" : "", base+1));
}