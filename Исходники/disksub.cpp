//
// initialize()
// initiailize
//
void DiskSub::initialize()
{
	FILEIO *fio;
	int high;
	int low;
	uint8 *ptr;
	uint8 eor;

	// clear rom & initialize (JR *)
	memset(&memory[0x0000], 0xff, 0x2000);
	memory[0x0000] = 0x18;
	memory[0x0001] = 0xfe;

	// clear higher memory
	memset(&memory[0x8000], 0xff, 0x8000);

	// inititlize 0x2000-0x7fff
	ptr = &memory[0x2000];
	for (high=0; high<0x60; high++) {
		// get xor data
		switch (init_table[high]) {
		case 0:
			eor = 0xf0;
			break;
		case 1:
			eor = 0x0f;
			break;
		case 2:
			eor = 0xff;
			break;
		default:
			eor = 0x00;
			break;
		}

		// fill memory
		for (low=0; low<0x10; low++) {
			memset(ptr, init_pattern[low] ^ eor, 0x10);
			ptr += 0x10;
		}
	}

	// read ROM (both PC88.ROM and DISK.ROM)
	fio = new FILEIO;
	if (fio->Fopen(emu->bios_path(_T("PC88.ROM")), FILEIO_READ_BINARY) == true) {
		fio->Fseek(0x14000, FILEIO_SEEK_CUR);
		fio->Fread(&memory[0], 1, 0x2000);
		fio->Fclose();
	}
	if (fio->Fopen(emu->bios_path(_T("DISK.ROM")), FILEIO_READ_BINARY) ==  true) {
		fio->Fread(&memory[0], 1, 0x2000);
		fio->Fclose();
	}
	delete fio;
}