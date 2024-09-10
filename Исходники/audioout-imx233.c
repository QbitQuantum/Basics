/* volume in half dB
 * don't check input values */
static void set_hp_vol(int vol_l, int vol_r)
{
    /* minimum is -57.5dB and max is 6dB in DAC mode
     * and -51.5dB / 12dB in Line1 mode */
    int min = input_line1 ? -103 : -115;
    int max = input_line1 ? 24 : 12;

    vol_l = MAX(min, MIN(vol_l, max));
    vol_r = MAX(min, MIN(vol_r, max));
    /* unmute, enable zero cross and set volume.*/
#if IMX233_SUBTARGET >= 3700
    unsigned mstr_zcd = BM_AUDIOOUT_HPVOL_EN_MSTR_ZCD;
#else
    unsigned mstr_zcd = 0;
#endif
    HW_AUDIOOUT_HPVOL = mstr_zcd | BF_OR3(AUDIOOUT_HPVOL, SELECT(input_line1),
        VOL_LEFT(max - vol_l), VOL_RIGHT(max - vol_r));
}