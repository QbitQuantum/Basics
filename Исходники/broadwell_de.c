void bdw_de_decode_model(int cputype, int bank, u64 status, u64 misc)
{
	switch (bank) {
	case 4:
		Wprintf("PCU: ");
		switch (EXTRACT(status, 0, 15) & ~(1ull << 12)) {
		case 0x402: case 0x403:
			Wprintf("Internal errors ");
			break;
		case 0x406:
			Wprintf("Intel TXT errors ");
			break;
		case 0x407:
			Wprintf("Other UBOX Internal errors ");
			break;
		}
		if (EXTRACT(status, 16, 19) & 3)
			Wprintf("PCU internal error ");
		if (EXTRACT(status, 20, 23) & 4)
			Wprintf("Ubox error ");
		decode_bitfield(status, pcu_mc4);
		break;
	case 9: case 10:
		Wprintf("MemCtrl: ");
		decode_bitfield(status, memctrl_mc9);
		break;
	}
}