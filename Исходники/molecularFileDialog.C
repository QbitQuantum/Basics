bool MolecularFileDialog::canHandle(const String& fileformat) const
{
	String formats = getSupportedFileFormats();
	vector<String> fields;
	formats.split(fields, "*. ");

	for (Position p = 0; p < fields.size(); p++)
	{
		String s = fields[p];
		if (s == fileformat) return true;
		s.toUpper();
		if (s == fileformat) return true;
	}

	return false;
}