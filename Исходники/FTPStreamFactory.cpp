void FTPStreamFactory::getPathAndType(const Poco::URI& uri, std::string& path, char& type)
{
	path = uri.getPath();
	type = 'i';
	std::string::size_type pos = path.rfind(';');
	if (pos != std::string::npos)
	{
		if (path.length() == pos + 7 && path.compare(pos + 1, 5, "type=") == 0)
		{
			type = path[pos + 6];
			path.resize(pos);
		}
	}
}