int wmain(int argc, wchar_t* argv[])
{
	if(argc < 3)
	{
		std::wcerr << L"Usage: " << argv[0] << L" infile delay [forced samplerate]" << std::endl;
		std::wcerr << L"Delay is in milliseconds and may be fractional." << std::endl;
		return 1;
	}

	delay = _wtof(argv[2]);
	if(delay <= 0)
	{
		std::wcerr << L"Error: Delay must be positive millisecond value, may be fractional." << std::endl;
		return 1;
	}

	if(argc >= 4)
	{
		sampleRate = _wtoi(argv[3]);
	}

	FILE *f = _wfopen(argv[1], L"rb");
	if(f == nullptr)
	{
		std::wcerr << L"Cannot open: " << argv[1] << L" for reading!" << std::endl;
		return 1;
	}

	std::wstring newFile = argv[1];
	newFile += L".tmp";
	FILE *of = _wfopen(newFile.c_str(), L"wb");
	if(of == nullptr)
	{
		std::wcerr << L"Cannot open output file: " << newFile.c_str() << L" for writing!" << std::endl;
		return 1;
	}

	if(!DecodeWAV(f, of) && !DecodeFLAC(f, of))
	{
		std::wcerr << L"Error: Unknown file type" << std::endl;
		fclose(of);
		_wremove(newFile.c_str());
		return 1;
	}

	fclose(f);
	fclose(of);

	_stat stat;
	_wstat(argv[1], &stat);
	_utimbuf timbuf;
	timbuf.actime = stat.st_atime;
	timbuf.modtime = stat.st_mtime;
	_wutime(newFile.c_str(), &timbuf);
	
	_wremove(argv[1]);
	_wrename(newFile.c_str(), argv[1]);

	return 0;
}