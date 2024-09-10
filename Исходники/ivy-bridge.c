void ivb_decode_model(int cputype, int bank, u64 status, u64 misc)
{
	switch (bank) {
	case 4:
		Wprintf("PCU: ");
		decode_bitfield(status, pcu_mc4);
		Wprintf("\n");
		break;
	case 5:
		if (cputype == CPU_IVY_BRIDGE_EPEX) {
			/* MCACOD already decoded */
			Wprintf("QPI\n");
		}
		break;
	case 9: case 10: case 11: case 12:
	case 13: case 14: case 15: case 16:
		Wprintf("MemCtrl: ");
		decode_bitfield(status, memctrl_mc9);
		Wprintf("\n");
		break;
	}
}