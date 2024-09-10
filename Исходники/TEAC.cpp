int wmain(int argc, wchar_t* argv[])
{
	CArguments args;
	if(!args.Parse(argc, argv))
	{
		_putws(g_wszUsage);
		return 1;
	}

	CTokenReader tokenReader;

	return 0;
}