void ROMPACK::initialize()
{
	memset(rom, 0xff, sizeof(rom));
	
	FILEIO* fio = new FILEIO();
	if(fio->Fopen(emu->bios_path(_T("ROMPACK.ROM")), FILEIO_READ_BINARY)) {
		fio->Fread(rom, sizeof(rom), 1);
		fio->Fclose();
	}
	delete fio;
}