void trs80dt1_state::trs80dt1(machine_config &config)
{
	/* basic machine hardware */
	I8051(config, m_maincpu, 7372800);
	m_maincpu->set_addrmap(AS_PROGRAM, &trs80dt1_state::prg_map);
	m_maincpu->set_addrmap(AS_IO, &trs80dt1_state::io_map);
	m_maincpu->port_out_cb<1>().set(FUNC(trs80dt1_state::port1_w));
	m_maincpu->port_out_cb<3>().set(FUNC(trs80dt1_state::port3_w));

	/* video hardware */
	screen_device &screen(SCREEN(config, "screen", SCREEN_TYPE_RASTER));
	screen.set_screen_update("crtc", FUNC(i8276_device::screen_update));
	screen.set_refresh_hz(60);
	screen.set_vblank_time(ATTOSECONDS_IN_USEC(2500)); /* not accurate */
	screen.set_size(40*12, 16*16);
	screen.set_visarea(0, 40*12-1, 0, 16*16-1);

	GFXDECODE(config, "gfxdecode", m_palette, gfx_trs80dt1);

	I8276(config, m_crtc, 12480000 / 8);
	m_crtc->set_character_width(8);
	m_crtc->set_display_callback(FUNC(trs80dt1_state::crtc_update_row), this);
	m_crtc->drq_wr_callback().set_inputline(m_maincpu, MCS51_INT0_LINE); // BRDY pin goes through inverter to /INT0, so we don't invert
	m_crtc->irq_wr_callback().set(m_7474, FUNC(ttl7474_device::clear_w)); // INT pin
	m_crtc->irq_wr_callback().append(m_7474, FUNC(ttl7474_device::d_w));
	m_crtc->vrtc_wr_callback().set(m_7474, FUNC(ttl7474_device::clock_w));
	m_crtc->set_screen("screen");

	PALETTE(config, "palette").set_entries(3);

	X2210(config, "nvram");

	TTL7474(config, m_7474, 0);
	m_7474->comp_output_cb().set_inputline(m_maincpu, MCS51_INT1_LINE).invert(); // /Q connects directly to /INT1, so we need to invert?

	/* sound hardware */
	SPEAKER(config, "mono").front_center();
	BEEP(config, m_beep, 2000);
	m_beep->add_route(ALL_OUTPUTS, "mono", 0.50);
}