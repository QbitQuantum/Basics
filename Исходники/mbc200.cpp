GFXDECODE_END


void mbc200_state::mbc200(machine_config &config)
{
	/* basic machine hardware */
	Z80(config, m_maincpu, 8_MHz_XTAL / 2); // NEC D780C-1
	m_maincpu->set_addrmap(AS_PROGRAM, &mbc200_state::mbc200_mem);
	m_maincpu->set_addrmap(AS_IO, &mbc200_state::mbc200_io);

	z80_device &subcpu(Z80(config, "subcpu", 8_MHz_XTAL / 2)); // NEC D780C-1
	subcpu.set_addrmap(AS_PROGRAM, &mbc200_state::mbc200_sub_mem);
	subcpu.set_addrmap(AS_IO, &mbc200_state::mbc200_sub_io);

	/* video hardware */
	screen_device &screen(SCREEN(config, "screen", SCREEN_TYPE_RASTER));
	screen.set_refresh_hz(50);
	screen.set_vblank_time(ATTOSECONDS_IN_USEC(2500)); /* not accurate */
	screen.set_size(640, 400);
	screen.set_visarea(0, 640-1, 0, 400-1);
	screen.set_screen_update("crtc", FUNC(hd6845s_device::screen_update));
	GFXDECODE(config, "gfxdecode", m_palette, gfx_mbc200);
	PALETTE(config, m_palette, palette_device::MONOCHROME);

	HD6845S(config, m_crtc, 8_MHz_XTAL / 4); // HD46505SP
	m_crtc->set_screen("screen");
	m_crtc->set_show_border_area(false);
	m_crtc->set_char_width(8);
	m_crtc->set_update_row_callback(FUNC(mbc200_state::update_row), this);

	// sound
	SPEAKER(config, "mono").front_center();
	BEEP(config, m_beep, 1000).add_route(ALL_OUTPUTS, "mono", 0.50); // frequency unknown
	SPEAKER_SOUND(config, m_speaker).add_route(ALL_OUTPUTS, "mono", 0.50);

	I8255(config, "ppi_1").out_pc_callback().set(FUNC(mbc200_state::p1_portc_w));
	I8255(config, "ppi_2").in_pa_callback().set(FUNC(mbc200_state::p2_porta_r));

	I8255(config, m_ppi_m);
	m_ppi_m->out_pa_callback().set(FUNC(mbc200_state::pm_porta_w));
	m_ppi_m->out_pb_callback().set(FUNC(mbc200_state::pm_portb_w));

	I8251(config, "uart1", 0); // INS8251N

	I8251(config, "uart2", 0); // INS8251A

	MB8876(config, m_fdc, 8_MHz_XTAL / 8); // guess
	FLOPPY_CONNECTOR(config, "fdc:0", mbc200_floppies, "qd", floppy_image_device::default_floppy_formats).enable_sound(true);
	FLOPPY_CONNECTOR(config, "fdc:1", mbc200_floppies, "qd", floppy_image_device::default_floppy_formats).enable_sound(true);

	/* Keyboard */
	generic_keyboard_device &keyboard(GENERIC_KEYBOARD(config, "keyboard", 0));
	keyboard.set_keyboard_callback(FUNC(mbc200_state::kbd_put));

	/* software lists */
	SOFTWARE_LIST(config, "flop_list").set_original("mbc200");
}