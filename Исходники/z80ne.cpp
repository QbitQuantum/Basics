void z80ne_state::z80ne(machine_config &config)
{
	/* basic machine hardware */
	Z80(config, m_maincpu, Z80NE_CPU_SPEED_HZ);
	m_maincpu->set_addrmap(AS_PROGRAM, &z80ne_state::z80ne_mem);
	m_maincpu->set_addrmap(AS_IO, &z80ne_state::z80ne_io);

	MCFG_MACHINE_START_OVERRIDE(z80ne_state,z80ne)
	MCFG_MACHINE_RESET_OVERRIDE(z80ne_state,z80ne)

	AY31015(config, m_uart);

	CLOCK(config, m_uart_clock, 4800);
	m_uart_clock->signal_handler().set(FUNC(z80ne_state::lx385_uart_tx_clock_w));
	m_uart_clock->signal_handler().append(m_uart, FUNC(ay31015_device::write_rcp));

	CASSETTE(config, m_cassette1);
	m_cassette1->set_default_state(CASSETTE_STOPPED | CASSETTE_MOTOR_ENABLED | CASSETTE_SPEAKER_ENABLED);
	m_cassette1->set_interface("z80ne_cass");

	CASSETTE(config, m_cassette2);
	m_cassette2->set_default_state(CASSETTE_STOPPED | CASSETTE_MOTOR_ENABLED | CASSETTE_SPEAKER_ENABLED);
	m_cassette2->set_interface("z80ne_cass");

	config.set_default_layout(layout_z80ne);

	/* internal ram */
	RAM(config, m_ram).set_default_size("32K");

	// all known tapes require LX.388 expansion
	//SOFTWARE_LIST(config, "cass_list").set_original("z80ne_cass");
}