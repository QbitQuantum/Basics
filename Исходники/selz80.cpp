void selz80_state::selz80(machine_config &config)
{
	/* basic machine hardware */
	Z80(config, m_maincpu, XTAL(4'000'000)); // it's actually a 5MHz XTAL with a NEC uPD780C-1 cpu
	m_maincpu->set_addrmap(AS_PROGRAM, &selz80_state::selz80_mem);
	m_maincpu->set_addrmap(AS_IO, &selz80_state::selz80_io);
	MCFG_MACHINE_RESET_OVERRIDE(selz80_state, selz80 )

	/* video hardware */
	config.set_default_layout(layout_selz80);

	/* Devices */
	CLOCK(config, m_clock, 153600);
	m_clock->signal_handler().set("uart", FUNC(i8251_device::write_txc));
	m_clock->signal_handler().append("uart", FUNC(i8251_device::write_rxc));

	i8251_device &uart(I8251(config, "uart", 0));
	uart.txd_handler().set("rs232", FUNC(rs232_port_device::write_txd));
	uart.dtr_handler().set("rs232", FUNC(rs232_port_device::write_dtr));
	uart.rts_handler().set("rs232", FUNC(rs232_port_device::write_rts));

	rs232_port_device &rs232(RS232_PORT(config, "rs232", default_rs232_devices, nullptr));
	rs232.rxd_handler().set("uart", FUNC(i8251_device::write_rxd));
	rs232.dsr_handler().set("uart", FUNC(i8251_device::write_dsr));
	rs232.cts_handler().set("uart", FUNC(i8251_device::write_cts));

	i8279_device &kbdc(I8279(config, "i8279", 5000000 / 2)); // based on divider
	kbdc.out_sl_callback().set(FUNC(selz80_state::scanlines_w));    // scan SL lines
	kbdc.out_disp_callback().set(FUNC(selz80_state::digit_w));      // display A&B
	kbdc.in_rl_callback().set(FUNC(selz80_state::kbd_r));           // kbd RL lines
	kbdc.in_shift_callback().set_constant(1);                       // Shift key
	kbdc.in_ctrl_callback().set_constant(1);
}