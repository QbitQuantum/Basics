void idsa_state::idsa(machine_config &config)
{
	/* basic machine hardware */
	Z80(config, m_maincpu, XTAL(8'000'000) / 2);
	m_maincpu->set_addrmap(AS_PROGRAM, &idsa_state::maincpu_map);
	m_maincpu->set_addrmap(AS_IO, &idsa_state::maincpu_io_map);

	clock_device &irqclock(CLOCK(config, "irqclock", XTAL(8'000'000) / 4));
	irqclock.signal_handler().set(FUNC(idsa_state::clock_w));

	/* video hardware */
	//config.set_default_layout()

	/* sound hardware */
	genpin_audio(config);
	SPEAKER(config, "lspeaker").front_left();
	SPEAKER(config, "rspeaker").front_right();
	SP0256(config, m_speech, 3120000); // unknown variant
	m_speech->add_route(ALL_OUTPUTS, "lspeaker", 1.5);

	ay8910_device &aysnd1(AY8910(config, "aysnd1", 2000000));  // 2Mhz according to pinmame, schematic omits the clock line
	aysnd1.port_a_write_callback().set(FUNC(idsa_state::ay1_a_w));
	aysnd1.port_b_write_callback().set(FUNC(idsa_state::ay1_b_w));
	aysnd1.add_route(ALL_OUTPUTS, "lspeaker", 0.75);

	ay8910_device &aysnd2(AY8910(config, "aysnd2", 2000000));
	aysnd2.port_a_write_callback().set(FUNC(idsa_state::ay2_a_w));
	aysnd2.port_b_write_callback().set(FUNC(idsa_state::ay2_b_w));
	aysnd2.add_route(ALL_OUTPUTS, "rspeaker", 0.75);
}