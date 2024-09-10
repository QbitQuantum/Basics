static const char *locate_font(const std::string& path)
{
	builtin_fonts_t::iterator j = builtin_fonts.find(path);
	if (j != builtin_fonts.end() || path == "")
	{
		return path.c_str();
	}
	else
	{
		static FileSpecifier file;
		if (file.SetNameWithPath(path.c_str()))
			return file.GetPath();
		else
			return "";
	}
}