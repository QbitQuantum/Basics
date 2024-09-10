std::string TreeSocket::MyModules(int filter)
{
	std::vector<std::string> modlist = ServerInstance->Modules->GetAllModuleNames(filter);

	std::string capabilities;
	sort(modlist.begin(),modlist.end());
	for (std::vector<std::string>::const_iterator i = modlist.begin(); i != modlist.end(); ++i)
	{
		if (i != modlist.begin())
			capabilities.push_back(' ');
		capabilities.append(*i);
		Module* m = ServerInstance->Modules->Find(*i);
		Version v = m->GetVersion();
		if (!v.link_data.empty())
		{
			capabilities.push_back('=');
			capabilities.append(v.link_data);
		}
	}
	return capabilities;
}