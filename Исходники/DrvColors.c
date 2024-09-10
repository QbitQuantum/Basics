static HPALETTE CreateDefaultPalette()
{
	union
	{
		LOGPALETTE LogPalette;
		PALETTEENTRY pad[sizeof(LOGPALETTE)/sizeof(PALETTEENTRY)
			+ DefaultPaletteSize];
	} u;
	int i;

	/* create logical palette from default palette */
	u.LogPalette.palVersion = 0x0300;
	u.LogPalette.palNumEntries = DefaultPaletteSize;
	for (i = 0; i < DefaultPaletteSize; i++)
		u.LogPalette.palPalEntry[i] = DefaultPalette[i];
	return (CreatePalette(&u.LogPalette));

}