ROM_END



/*************************************
 *
 *  Low byte ROM decoding
 *
 *************************************/

INLINE void generic_decode(running_machine &machine, const char *tag, int bit7, int bit6, int bit5, int bit4, int bit3, int bit2, int bit1, int bit0)
{
    UINT16 *rom = (UINT16 *)machine.region(tag)->base();
    int i;

    /* only the low byte of ROMs are encrypted in these games */
    for (i = 0; i < 0x20000/2; i++)
        rom[i] = BITSWAP16(rom[i], 15,14,13,12,11,10,9,8, bit7,bit6,bit5,bit4,bit3,bit2,bit1,bit0);

#if 0
    {
        UINT8 *ROM = machine.region(tag)->base();
        int size = machine.region(tag)->bytes();

        FILE *fp;
        char filename[256];
        sprintf(filename,"decrypted_%s", machine.system().name);
        fp=fopen(filename, "w+b");
        if (fp)
        {
            fwrite(ROM, size, 1, fp);
            fclose(fp);
        }
    }
#endif
}