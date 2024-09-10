void snb_decode_model(int cputype, int bank, u64 status, u64 misc)
{
    switch (bank) {
    case 4:
        Wprintf("PCU: ");
        decode_bitfield(status, pcu_mc4);
        Wprintf("\n");
        break;
    case 6:
    case 7:
        if (cputype == CPU_SANDY_BRIDGE_EP) {
            /* MCACOD already decoded */
            Wprintf("QPI\n");
        }
        break;
    }
}