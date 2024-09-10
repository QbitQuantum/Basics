bool get_default_theme_spec(FileSpecifier &file)
{
	FileSpecifier theme = "Themes";
	theme += getcstr(temporary, strFILENAMES, filenameDEFAULT_THEME);
	return get_default_spec(file, theme.GetPath());
}