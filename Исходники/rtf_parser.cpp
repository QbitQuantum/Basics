static std::string ustring_to_string(const UString& s)
{
	std::string r;
	for (int i = 0; i < s.length(); i++)
	{
		gchar out[6];
		gint len = g_unichar_to_utf8(s[i].unicode(), out);
		out[len] = '\0';
		r += out;
	}
	return r;
}