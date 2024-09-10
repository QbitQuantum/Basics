void a5105_state::a5105(machine_config &config)
{
	/* basic machine hardware */
	Z80(config, m_maincpu, XTAL(15'000'000) / 4);
	m_maincpu->set_addrmap(AS_PROGRAM, &a5105_state::a5105_mem);
	m_maincpu->set_addrmap(AS_IO, &a5105_state::a5105_io);
	m_maincpu->set_daisy_config(a5105_daisy_chain);

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(50);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(2500)); /* not accurate */
	m_screen->set_screen_update("upd7220", FUNC(upd7220_device::screen_update));
	m_screen->set_size(40*8, 32*8);
	m_screen->set_visarea(0, 40*8-1, 0, 25*8-1);
	GFXDECODE(config, m_gfxdecode, m_palette, gfx_a5105);
	PALETTE(config, m_palette, FUNC(a5105_state::a5105_palette), 16);

	/* sound hardware */
	SPEAKER(config, "mono").front_center();
	WAVE(config, "wave", "cassette").add_route(ALL_OUTPUTS, "mono", 0.25);
	BEEP(config, "beeper", 500).add_route(ALL_OUTPUTS, "mono", 0.50);

	/* Devices */
	UPD7220(config, m_hgdc, XTAL(15'000'000) / 16); // unk clock
	m_hgdc->set_addrmap(0, &a5105_state::upd7220_map);
	m_hgdc->set_display_pixels(FUNC(a5105_state::hgdc_display_pixels));
	m_hgdc->set_draw_text(FUNC(a5105_state::hgdc_draw_text));

	z80ctc_device& ctc(Z80CTC(config, "z80ctc", XTAL(15'000'000) / 4));
	ctc.intr_callback().set_inputline(m_maincpu, 0);
	ctc.zc_callback<0>().set("z80ctc", FUNC(z80ctc_device::trg2));
	ctc.zc_callback<2>().set("z80ctc", FUNC(z80ctc_device::trg3));

	z80pio_device& pio(Z80PIO(config, "z80pio", XTAL(15'000'000) / 4));
	pio.in_pb_callback().set(FUNC(a5105_state::pio_pb_r));
	pio.out_int_callback().set_inputline(m_maincpu, 0);

	CASSETTE(config, m_cass);

	UPD765A(config, m_fdc, 8'000'000, true, true);
	FLOPPY_CONNECTOR(config, "upd765a:0", a5105_floppies, "525qd", a5105_state::floppy_formats);
	FLOPPY_CONNECTOR(config, "upd765a:1", a5105_floppies, "525qd", a5105_state::floppy_formats);
	FLOPPY_CONNECTOR(config, "upd765a:2", a5105_floppies, "525qd", a5105_state::floppy_formats);
	FLOPPY_CONNECTOR(config, "upd765a:3", a5105_floppies, "525qd", a5105_state::floppy_formats);

	/* internal ram */
	RAM(config, RAM_TAG).set_default_size("64K");
}