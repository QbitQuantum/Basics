void RP5C01::release()
{
#ifndef HAS_RP5C15
	// save ram image
	FILEIO* fio = new FILEIO();
	if(fio->Fopen(emu->bios_path(_T("RP5C01.BIN")), FILEIO_WRITE_BINARY)) {
		fio->Fwrite(ram, sizeof(ram), 1);
		fio->Fclose();
	}
	delete fio;
#endif
}