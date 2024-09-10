void MFONT::initialize()
{
	memset(mfont, 0xff, sizeof(mfont));
	
	// load multifont rom image
	FILEIO* fio = new FILEIO();
	if(fio->Fopen(create_local_path(_T("MFONT.ROM")), FILEIO_READ_BINARY)) {
		fio->Fread(mfont, sizeof(mfont), 1);
		fio->Fclose();
	}
	delete fio;
	
	cmd = new FIFO(4);
	res = new FIFO(38);
	
	status = 0;
}