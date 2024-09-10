void PC80S31K::initialize()
{
	// init memory
	memset(rom, 0xff, sizeof(rom));
	memset(ram, 0, sizeof(ram));
	memset(rdmy, 0xff, sizeof(rdmy));
	
	// load rom image
	FILEIO* fio = new FILEIO();
	if(fio->Fopen(create_local_path(_T("PC88.ROM")), FILEIO_READ_BINARY)) {
		fio->Fseek(0x14000, FILEIO_SEEK_CUR);
		fio->Fread(rom, sizeof(rom), 1);
		fio->Fclose();
	} else if(fio->Fopen(create_local_path(_T("DISK.ROM")), FILEIO_READ_BINARY)) {
		fio->Fread(rom, sizeof(rom), 1);
		fio->Fclose();
	} else {
		// stop cpu
		d_cpu->write_signal(SIG_CPU_BUSREQ, 1, 1);
	}
	delete fio;
	
	// init memory map
	SET_BANK(0x0000, 0x1fff, wdmy, rom);
	SET_BANK(0x2000, 0x3fff, wdmy, rdmy);
	SET_BANK(0x4000, 0x7fff, ram, ram);
	SET_BANK(0x8000, 0xffff, wdmy, rdmy);
	
	// XM8 version 1.20
	// both drives always set force ready signal
	d_fdc->write_signal(SIG_UPD765A_FREADY, 1, 1);
}