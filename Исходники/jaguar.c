void cojag_sound_init(running_machine &machine)
{
	int i;

	/* fill the wave ROM -- these are pretty cheesy guesses */
	for (i = 0; i < 0x80; i++)
	{
		/* F1D000 = triangle wave */
		jaguar_wave_rom[0x000 + i] = ((i <= 0x40) ? i : 0x80 - i) * 32767 / 0x40;

		/* F1D200 = full sine wave */
		jaguar_wave_rom[0x080 + i] = (int)(32767. * sin(2.0 * M_PI * (double)i / (double)0x80));

		/* F1D400 = amplitude modulated sine wave? */
		jaguar_wave_rom[0x100 + i] = (int)(32767. * sin(2.0 * M_PI * (double)i / (double)0x80));

		/* F1D600 = sine wave and second order harmonic */
		jaguar_wave_rom[0x180 + i] = (int)(32767. * sin(2.0 * M_PI * (double)i / (double)0x80));

		/* F1D800 = chirp (sine wave of increasing frequency) */
		jaguar_wave_rom[0x200 + i] = (int)(32767. * sin(2.0 * M_PI * (double)i / (double)0x80));

		/* F1DA00 = traingle wave with noise */
		jaguar_wave_rom[0x280 + i] = jaguar_wave_rom[0x000 + i] * (machine.rand() % 32768) / 32768;

		/* F1DC00 = spike */
		jaguar_wave_rom[0x300 + i] = (i == 0x40) ? 32767 : 0;

		/* F1DE00 = white noise */
		jaguar_wave_rom[0x380 + i] = machine.rand() % 32768;
	}

#if ENABLE_SPEEDUP_HACKS
	if (jaguar_hacks_enabled)
		machine.device("audiocpu")->memory().space(AS_PROGRAM)->install_legacy_write_handler(0xf1a100, 0xf1a103, FUNC(dsp_flags_w));

#endif
}