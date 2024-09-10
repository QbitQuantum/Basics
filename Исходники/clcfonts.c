void RegisterCListFonts()
{
	FontIDT fontid = {0};
	ColourIDT colourid = {0};
	char idstr[10];
	int i;

	fontid.cbSize = sizeof(FontIDT);
	fontid.flags = FIDF_ALLOWREREGISTER | FIDF_APPENDNAME | FIDF_NOAS | FIDF_SAVEPOINTSIZE | FIDF_ALLOWEFFECTS;

	for (i = 0; i <= CLIST_FONTID_MAX; i++) {

		switch (fontListOrder[i])
		{
		case FONTID_GROUPS:
		case FONTID_GROUPCOUNTS:
			fontid.flags &= ~FIDF_CLASSMASK;
			fontid.flags |= FIDF_CLASSHEADER;
			break;
		case FONTID_DIVIDERS:
			fontid.flags &= ~FIDF_CLASSMASK;
			fontid.flags |= FIDF_CLASSSMALL;
			break;
		default:
			fontid.flags &= ~FIDF_CLASSMASK;
			fontid.flags |= FIDF_CLASSGENERAL;
			break;
		}

		strncpy(fontid.dbSettingsGroup, "CLC", sizeof(fontid.dbSettingsGroup));
		_tcsncpy(fontid.group, _T("Contact List"), SIZEOF(fontid.group));
		_tcsncpy(fontid.name, szClistFontIdDescr[fontListOrder[i]], SIZEOF(fontid.name));
		sprintf(idstr, "Font%d", fontListOrder[i]);
		strncpy(fontid.prefix, idstr, SIZEOF(fontid.prefix));
		fontid.order = fontListOrder[i];

		CallService(MS_FONT_REGISTERT, (WPARAM)&fontid, 0);
	}

	// and colours
	colourid.cbSize = sizeof(ColourIDT);
	colourid.order = 0;
	strncpy(colourid.dbSettingsGroup, "CLC", sizeof(colourid.dbSettingsGroup));

	strncpy(colourid.setting, "BkColour", sizeof(colourid.setting));
	_tcsncpy(colourid.name, LPGENT("Background"), SIZEOF(colourid.name));
	_tcsncpy(colourid.group, LPGENT("Contact List"), SIZEOF(colourid.group));
	colourid.defcolour = CLCDEFAULT_BKCOLOUR;
	CallService(MS_COLOUR_REGISTERT, (WPARAM)&colourid, 0);

	strncpy(colourid.setting, "SelTextColour", sizeof(colourid.setting));
	_tcsncpy(colourid.name, LPGENT("Selected Text"), SIZEOF(colourid.name));
	colourid.order = 1;
	colourid.defcolour = CLCDEFAULT_SELTEXTCOLOUR;
	CallService(MS_COLOUR_REGISTERT, (WPARAM)&colourid, 0);

	strncpy(colourid.setting, "HotTextColour", sizeof(colourid.setting));
	_tcsncpy(colourid.name, LPGENT("Hottrack Text"), SIZEOF(colourid.name));
	colourid.order = 1;
	colourid.defcolour = CLCDEFAULT_HOTTEXTCOLOUR;
	CallService(MS_COLOUR_REGISTERT, (WPARAM)&colourid, 0);

	strncpy(colourid.setting, "QuickSearchColour", sizeof(colourid.setting));
	_tcsncpy(colourid.name, LPGENT("Quicksearch Text"), SIZEOF(colourid.name));
	colourid.order = 1;
	colourid.defcolour = CLCDEFAULT_QUICKSEARCHCOLOUR;
	CallService(MS_COLOUR_REGISTERT, (WPARAM)&colourid, 0);

	HookEvent(ME_FONT_RELOAD, FS_FontsChanged);
}