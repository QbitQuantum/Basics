void CmdDlg::prettify(tstring &text)
{
	try {
		const tstring search(_T("\n")), replace(_T("\r\n"));

		// http://stackoverflow.com/a/14678800/98528
		tstring::size_type pos = 0;
		while ((pos = text.find(search, pos)) != tstring::npos) {
			text.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		text += replace;
	} catch (...) {
		text.clear();
	}
}