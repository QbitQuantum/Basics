wxString CImportDialog::DecodeLegacyPassword(wxString pass)
{
	wxString output;
	const char* key = "FILEZILLA1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	int pos = (pass.Length() / 3) % strlen(key);
	for (unsigned int i = 0; i < pass.Length(); i += 3)
	{
		if (pass[i] < '0' || pass[i] > '9' ||
			pass[i + 1] < '0' || pass[i + 1] > '9' ||
			pass[i + 2] < '0' || pass[i + 2] > '9')
			return _T("");
		int number = (pass[i] - '0') * 100 +
						(pass[i + 1] - '0') * 10 +
						pass[i + 2] - '0';
		wxChar c = number ^ key[(i / 3 + pos) % strlen(key)];
		output += c;
	}

	return output;
}