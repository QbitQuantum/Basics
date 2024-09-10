void M_ScreenShot (const char *filename)
{
	FILE *file;
	FString autoname;
	bool writepcx = (stricmp (screenshot_type, "pcx") == 0);	// PNG is the default

	// find a file name to save it to
	if (filename == NULL || filename[0] == '\0')
	{
		size_t dirlen;
		autoname = Args->CheckValue("-shotdir");
		if (autoname.IsEmpty())
		{
			autoname = screenshot_dir;
		}
		dirlen = autoname.Len();
		if (dirlen == 0)
		{
			autoname = M_GetScreenshotsPath();
			dirlen = autoname.Len();
		}
		if (dirlen > 0)
		{
			if (autoname[dirlen-1] != '/' && autoname[dirlen-1] != '\\')
			{
				autoname += '/';
			}
		}
		autoname = NicePath(autoname);
		CreatePath(autoname);
		if (!FindFreeName (autoname, writepcx ? "pcx" : "png"))
		{
			Printf ("M_ScreenShot: Delete some screenshots\n");
			return;
		}
	}
	else
	{
		autoname = filename;
		DefaultExtension (autoname, writepcx ? ".pcx" : ".png");
	}

	// save the screenshot
	const BYTE *buffer;
	int pitch;
	ESSType color_type;

	screen->GetScreenshotBuffer(buffer, pitch, color_type);
	if (buffer != NULL)
	{
		PalEntry palette[256];

		if (color_type == SS_PAL)
		{
			screen->GetFlashedPalette(palette);
		}
		file = fopen (autoname, "wb");
		if (file == NULL)
		{
			Printf ("Could not open %s\n", autoname.GetChars());
			screen->ReleaseScreenshotBuffer();
			return;
		}
		if (writepcx)
		{
			WritePCXfile(file, buffer, palette, color_type,
				screen->GetWidth(), screen->GetHeight(), pitch);
		}
		else
		{
			WritePNGfile(file, buffer, palette, color_type,
				screen->GetWidth(), screen->GetHeight(), pitch);
		}
		fclose(file);
		screen->ReleaseScreenshotBuffer();

		if (!screenshot_quiet)
		{
			int slash = -1;
			if (!longsavemessages) slash = autoname.LastIndexOfAny(":/\\");
			Printf ("Captured %s\n", autoname.GetChars()+slash+1);
		}
	}
	else
	{
		if (!screenshot_quiet)
		{
			Printf ("Could not create screenshot.\n");
		}
	}
}