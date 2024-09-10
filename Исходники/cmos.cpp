void CMOS::release()
{
	FILEIO* fio = new FILEIO();
	if(fio->Fopen(emu->bios_path(_T("CMOS.BIN")), FILEIO_WRITE_BINARY)) {
		fio->Fwrite(cmos, sizeof(cmos), 1);
		fio->Fclose();
	}
	delete fio;
}