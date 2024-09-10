KANJIROM::KANJIROM(VM *parent_vm, EMU* parent_emu, bool type_2std): DEVICE(parent_vm, parent_emu)
{
	FILEIO *fio;
	read_ok = false;
	
	fio = new FILEIO();
	memset(data_table, 0xff, 0x20000); 
	//	read_table[0].memory = data_table;
	
	if(type_2std) {
		class2 = true;
		if(fio->Fopen(create_local_path(_T("KANJI2.ROM")), FILEIO_READ_BINARY)) {
		  fio->Fread(data_table, 0x20000, 1);
			fio->Fclose();
			read_ok = true;
		}
	} else {
		class2 = false;
		if(fio->Fopen(create_local_path(_T("KANJI1.ROM")), FILEIO_READ_BINARY)) {
		  fio->Fread(data_table, 0x20000, 1);
			fio->Fclose();
			read_ok = true;
		} else if(fio->Fopen(create_local_path(_T("KANJI.ROM")), FILEIO_READ_BINARY)) {
		  fio->Fread(data_table, 0x20000, 1);
			fio->Fclose();
			read_ok = true;
		} 
	}
	kanjiaddr.d = 0;
	delete fio;
	return;
}