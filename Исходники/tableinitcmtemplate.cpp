static void
rfbInitColourMapSingleTableOUT (char **table,
								rfbPixelFormat *in,
								rfbPixelFormat *out)
{
//	log.Print(LL_ALL, VNCLOG("rfbInitColourMapSingleTable called\n"));

	// ALLOCATE SPACE FOR COLOUR TABLE

    int nEntries = 1 << in->bitsPerPixel;

	// Allocate the table
    if (*table) free(*table);
    *table = (char *)malloc(nEntries * sizeof(OUT_T));
	if (*table == NULL)
	{
//		log.Print(LL_INTERR, VNCLOG("failed to allocate translation table\n"));
		return;
	}

	// Obtain the system palette
	HDC hDC = GetDC(NULL);
	PALETTEENTRY palette[256];
	if (GetSystemPaletteEntries(hDC,
		0, 256, palette) == 0)
	{
//		log.Print(LL_INTERR, VNCLOG("failed to get system palette (%d)\n"), GetLastError());
		ReleaseDC(NULL, hDC);
		return;
	}
	ReleaseDC(NULL, hDC);

	// COLOUR TRANSLATION

	// We now have the colour table intact.  Map it into a translation table
    int i, r, g, b;
    OUT_T *t = (OUT_T *)*table;

    for (i = 0; i < nEntries; i++)
	{
		// Split down the RGB data
		r = palette[i].peRed;
		g = palette[i].peGreen;
		b = palette[i].peBlue;

		// Now translate it
		t[i] = ((((r * out->redMax + 127) / 255) << out->redShift) |
			(((g * out->greenMax + 127) / 255) << out->greenShift) |
			(((b * out->blueMax + 127) / 255) << out->blueShift));
#if (BITSOUT != 8)
		if (out->bigEndian != in->bigEndian)
		{
			t[i] = SwapOUT(t[i]);
		}
#endif
	}

//	log.Print(LL_ALL, VNCLOG("rfbInitColourMapSingleTable done\n"));
}