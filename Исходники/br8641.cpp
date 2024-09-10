void brandt8641_state::brandt8641(machine_config &config)
{
	/* basic machine hardware */
	Z80(config, m_maincpu, XTAL(4'000'000)); // U4 ,4MHz crystal on board
	m_maincpu->set_addrmap(AS_PROGRAM, &brandt8641_state::brandt8641_mem);
	m_maincpu->set_addrmap(AS_IO, &brandt8641_state::brandt8641_io);
	m_maincpu->set_daisy_config(daisy_chain_intf);

	/* sound hardware */
	SPEAKER(config, "mono").front_center();
	BEEP(config, m_beep, 2000).add_route(ALL_OUTPUTS, "mono", 0.50);

	// Z80APIO U9
	// Z80APIO U14
	// Z80PIO U7 - unknown which is which
	Z80PIO(config, m_pio1, XTAL(4'000'000));
	m_pio1->out_int_callback().set_inputline(m_maincpu, INPUT_LINE_IRQ0);

	Z80PIO(config, m_pio2, XTAL(4'000'000));
	m_pio2->out_int_callback().set_inputline(m_maincpu, INPUT_LINE_IRQ0);
	m_pio2->in_pa_callback().set(FUNC(brandt8641_state::port08_r));
	m_pio2->out_pa_callback().set(FUNC(brandt8641_state::port08_w));
	m_pio2->out_pb_callback().set(FUNC(brandt8641_state::port09_w));

	Z80PIO(config, m_pio3, XTAL(4'000'000));
	m_pio3->out_int_callback().set_inputline(m_maincpu, INPUT_LINE_IRQ0);

	Z80CTC(config, "ctc", XTAL(4'000'000)); // Z80CTC U8
}