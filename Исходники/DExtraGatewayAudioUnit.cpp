void CDExtraGatewayAudioUnit::spellReflector(const wxString &reflector)
{
	unsigned int length = reflector.Len();

	for (unsigned int i = 0U; i < (length - 1U); i++) {
		wxString c = reflector.Mid(i, 1U);

		if (!c.IsSameAs(wxT(" ")))
			lookup(c);
	}

	wxChar c = reflector.GetChar(length - 1U);

	switch (c) {
		case wxT('A'):
			lookup(wxT("alpha"));
			break;
		case wxT('B'):
			lookup(wxT("bravo"));
			break;
		case wxT('C'):
			lookup(wxT("charlie"));
			break;
		case wxT('D'):
			lookup(wxT("delta"));
			break;
		default:
			lookup(wxString(c));
			break;
	}
}