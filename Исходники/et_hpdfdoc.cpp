void hpdf_doc::text_out_eng(HPDF_REAL& f_xpos, HPDF_REAL& f_ypos, wstring out_string, HPDF_REAL& f_advance, HPDF_REAL f_width, HPDF_REAL f_gap, HPDF_REAL f_space, _locale_t loceng)
{
	char line[4];

	int len = out_string.length();

	for (int i = 0; i < len; i++)
	{
		wchar_t out_wchar = out_string[i];
		memset(line, 0, 4);

		size_t size = _wcstombs_l(line, &out_wchar, 1, loceng);
		if (size == 0) break;

		HPDF_Page_TextOut(h_current_page, f_xpos + f_advance, f_ypos - f_linespace, line);
		f_advance += (f_width + f_gap);
	}

}