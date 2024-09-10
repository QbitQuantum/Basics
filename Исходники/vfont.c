struct vfont_file
get_font(const char* fontname, void (*vfont_log)(const char *fmt, ...))
{
    struct vfont_file font;
    struct header lochdr;
    static char	fname[FONTNAMESZ];

    /* Initialize vfont */
    memset(&font, 0, sizeof(struct vfont_file));

    if (fontname == NULL)
	fontname = FONTNAME;

    if (fontname[0] != '/') {
	/* absolute path */
	const char *vfont = bu_brlcad_data("vfont", 1);
	if (vfont)
	    snprintf(fname, FONTNAMESZ, "%s/%s", vfont, fontname);
	else
	    bu_strlcpy(fname, fontname, sizeof(fname));
    } else
	bu_strlcpy(fname, fontname, sizeof(fname));

    /* Open the file and read in the header information. */
    font.ffdes = fopen(fname, "rb");
    if (font.ffdes == NULL) {
	if (vfont_log)
	    vfont_log("Error opening font file '%s'\n", fname);

	font.ffdes = NULL;
	return font;
    }

    if (fread((char *)&lochdr, (int)sizeof(struct header), 1, font.ffdes) != 1) {
	if (vfont_log)
	    vfont_log("get_Font() read failed!\n");
	font.ffdes = NULL;
	return font;
    }

    SWAB(lochdr.magic);
    SWAB(lochdr.size);
    SWAB(lochdr.maxx);
    SWAB(lochdr.maxy);
    SWAB(lochdr.xtend);

    if (lochdr.magic != 0436) {
	if (vfont_log)
	    vfont_log("Not a font file \"%s\": magic=0%o\n", fname, (int)lochdr.magic);
	font.ffdes = NULL;
	return font;
    }
    font.hdr = lochdr;

    /* Read in the directory for the font. */
    if (fread((char *) font.dir, (int)sizeof(struct dispatch), 256, font.ffdes) != 256) {
	if (vfont_log)
	    vfont_log("get_Font() read failed!\n");
	font.ffdes = NULL;
	return font;
    }

    /* Addresses of characters in the file are relative to point in
     * the file after the directory, so grab the current position.
     */
    font.offset = bu_ftell(font.ffdes);

    return font;
}