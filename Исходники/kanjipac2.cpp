void KANJIPAC2::initialize(int id)
{
	FILEIO* fio = new FILEIO();
	if(fio->Fopen(emu->bios_path(_T("KANJI.ROM")), FILEIO_READ_BINARY)) {
		fio->Fread(rom, sizeof(rom), 1);
		fio->Fclose();
	}
	delete fio;
	
	ptr = 0;
}