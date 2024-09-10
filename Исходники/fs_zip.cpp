int VZipFile::CheckNumForFileName(VStr Name)
{
	guard(VZipFile::CheckNumForFileName);
	VStr CheckName = Name.ToLower();
	for (int i = NumFiles - 1; i >= 0; i--)
	{
		if (Files[i].Name == CheckName)
		{
			return i;
		}
	}

	// Not found.
	return -1;
	unguard;
}