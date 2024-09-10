void PathX::GetFileName(const tstring& path, tstring& outFileName)
{
	tstring::size_type pos = path.find_last_of(separator);
	if (pos == tstring::size_type(-1))
	{
		outFileName = path;
		return;
	}
	else if(pos == tstring::size_type(path.length()-1))
	{
		outFileName.clear();
		return;
	}
	else
	{
		outFileName = path.substr(pos+1, path.length());
		return;
	}
}