/*
===============
Cmd_Skin

Skins aren't actually stored in the file, only a reference
is saved out to the header file.
===============
*/
void Cmd_Skin (void)
{
	byte	*palette;
	byte	*pixels;
	int		width, height;
	byte	*cropped;
	int		y;
	char	name[1024], savename[1024];

	GetToken (false);

	if (model.num_skins == MAX_MD2SKINS)
		Error ("model.num_skins == MAX_MD2SKINS");

	if (g_skipmodel)
		return;

	sprintf (name, "%s/%s.lbm", cdarchive, token);
	strcpy (name, ExpandPathAndArchive( name ) );
//	sprintf (name, "%s/%s.lbm", cddir, token);

	if (TokenAvailable())
	{
		GetToken (false);
		sprintf (g_skins[model.num_skins], "%s.pcx", token);
		sprintf (savename, "%s%s.pcx", gamedir, g_skins[model.num_skins]);
	}
	else
	{
		sprintf (savename, "%s/%s.pcx", cddir, token);
		sprintf (g_skins[model.num_skins], "%s/%s.pcx", cdpartial, token);
	}

	model.num_skins++;

	if (g_skipmodel || g_release || g_archive)
		return;

	// load the image
	printf ("loading %s\n", name);
	Load256Image (name, &pixels, &palette, &width, &height);
	RemapZero (pixels, palette, width, height);

	// crop it to the proper size
	cropped = malloc (model.skinwidth*model.skinheight);
	for (y=0 ; y<model.skinheight ; y++)
	{
		memcpy (cropped+y*model.skinwidth,
			pixels+y*width, model.skinwidth);
	}

	// save off the new image
	printf ("saving %s\n", savename);
	CreatePath (savename);
	WritePCXfile (savename, cropped, model.skinwidth,
		model.skinheight, palette);

	free (pixels);
	free (palette);
	free (cropped);
}