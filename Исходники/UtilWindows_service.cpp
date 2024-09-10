BOOL doStartService(SC_HANDLE Service, const char* szName, std::vector<std::string> &args)
{
	BOOL res;

	if (args.size() == 0)
	{
		res = StartService(Service, 0, nullptr);
	}
	else
	{
		const char** a = new const char*[args.size()+1];

		a[0] = szName;

		for (size_t x=0; x<args.size(); x++)
			a[x+1] = args[x].c_str();

		res = StartServiceA(Service, args.size()+1, a);
		delete [] a;
	}

	return res;
}