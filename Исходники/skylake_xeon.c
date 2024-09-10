void skylake_s_decode_model(int cputype, int bank, u64 status, u64 misc)
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
		if (EXTRACT(status, 16, 19))
			Wprintf("PCU internal error ");
		decode_bitfield(status, pcu_mc4);
		break;
	case 5:
	case 12:
	case 19:
		Wprintf("UPI: ");
		decode_bitfield(status, upi_mc);
		if (EXTRACT(status, 16, 21) == 0x12)
			decode_bitfield(status, upi_0x12);
		break;
	case 7: case 8:
		Wprintf("M2M: ");
		decode_bitfield(status, m2m);
		break;
	case 13: case 14: case 15:
	case 16: case 17: case 18:
		Wprintf("MemCtrl: ");
		if (EXTRACT(status, 27, 27))
			decode_bitfield(status, memctrl_mc13);
		else
			decode_bitfield(status, mc_bits);
		break;
	}
}