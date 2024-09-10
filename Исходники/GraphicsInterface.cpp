void GraphicsInterface::Replace(wstring & wstrText, wstring wstrFind, wstring wstrReplace)
{
	size_t pos = 0;

	pos = wstrText.find(wstrFind);
	while (pos != wstring::npos)
	{
		wstrText.replace(pos, wstrFind.length(), wstrReplace);
		pos = wstrText.find(wstrFind);
	}

	return;
}