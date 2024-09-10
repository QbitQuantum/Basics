void RAMPAC2::release()
{
	// save modified data
	if(opened && modified) {
		FILEIO* fio = new FILEIO();
		if(fio->Fopen(path, FILEIO_WRITE_BINARY)) {
			fio->Fwrite(ram, sizeof(ram), 1);
			fio->Fclose();
		}
		delete fio;
	}
}