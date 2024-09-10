void KANJI::initialize()
{
	// init image
	memset(kanji, 0xff, sizeof(kanji));
	
	// load kanji image
	FILEIO* fio = new FILEIO();
	if(fio->Fopen(create_local_path(_T("KANJI.ROM")), FILEIO_READ_BINARY)) {
		fio->Fread(kanji, sizeof(kanji), 1);
		fio->Fclose();
	}
	delete fio;
	
	ptr = 0;
	strobe = false;
}