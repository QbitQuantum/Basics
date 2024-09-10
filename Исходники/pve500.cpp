void pve500_state::pve500(machine_config &config)
{
	/* Main CPU */
	TMPZ84C015(config, m_maincpu, 12_MHz_XTAL / 2); // TMPZ84C015BF-6
	m_maincpu->set_addrmap(AS_PROGRAM, &pve500_state::maincpu_prg);
	m_maincpu->set_addrmap(AS_IO, &pve500_state::maincpu_io);
	m_maincpu->set_daisy_config(maincpu_daisy_chain);
	m_maincpu->out_dtra_callback().set(FUNC(pve500_state::GPI_w));
	m_maincpu->out_dtrb_callback().set(m_buzzer, FUNC(beep_device::set_state)).invert();
	m_maincpu->out_txda_callback().set("recorder", FUNC(rs232_port_device::write_txd));
	m_maincpu->out_txdb_callback().set("player1", FUNC(rs232_port_device::write_txd));

	z80ctc_device& ctc(Z80CTC(config, "external_ctc", 12_MHz_XTAL / 2));
	ctc.intr_callback().set_inputline(m_maincpu, INPUT_LINE_IRQ0);

	z80sio0_device& sio(Z80SIO0(config, "external_sio", 12_MHz_XTAL / 2));
	sio.out_int_callback().set_inputline(m_maincpu, INPUT_LINE_IRQ0);
	sio.out_txda_callback().set("player2", FUNC(rs232_port_device::write_txd));
	sio.out_txdb_callback().set("edl_inout", FUNC(rs232_port_device::write_txd));

	/* Secondary CPU */
	TMPZ84C015(config, m_subcpu, 12_MHz_XTAL / 2); /* TMPZ84C015BF-6 */
	m_subcpu->set_addrmap(AS_PROGRAM, &pve500_state::subcpu_prg);
	m_subcpu->set_addrmap(AS_IO, &pve500_state::subcpu_io);
	m_subcpu->out_dtra_callback().set(FUNC(pve500_state::cxdio_reset_w));
	m_subcpu->out_dtrb_callback().set(FUNC(pve500_state::external_monitor_w));
	m_subcpu->out_txda_callback().set("switcher", FUNC(rs232_port_device::write_txd));
	m_subcpu->out_txdb_callback().set("serial_mixer", FUNC(rs232_port_device::write_txd));

	// PIO callbacks
	m_subcpu->in_pa_callback().set(FUNC(pve500_state::eeprom_r));
	m_subcpu->out_pa_callback().set(FUNC(pve500_state::eeprom_w));

	// ICG3: I/O Expander
	CXD1095(config, m_cxdio, 0);
	m_cxdio->out_porta_cb().set(FUNC(pve500_state::io_sc_w));
	m_cxdio->out_portb_cb().set(FUNC(pve500_state::io_le_w));
	m_cxdio->in_portc_cb().set(FUNC(pve500_state::io_ky_r));
	m_cxdio->out_portd_cb().set(FUNC(pve500_state::io_ld_w));
	m_cxdio->out_porte_cb().set(FUNC(pve500_state::io_sel_w));

	/* Search Dial MCUs */
	MB88201(config, "dial_mcu_left", 4_MHz_XTAL).set_disable(); /* PLAYER DIAL MCU */
	MB88201(config, "dial_mcu_right", 4_MHz_XTAL).set_disable(); /* RECORDER DIAL MCU */

	/* Serial EEPROM (128 bytes, 8-bit data organization) */
	/* The EEPROM stores the setup data */
	EEPROM_MSM16911_8BIT(config, "eeprom");

	/* FIX-ME: These are actually RS422 ports (except EDL IN/OUT which is indeed an RS232 port)*/
	rs232_port_device &recorder(RS232_PORT(config, "recorder", default_rs232_devices, nullptr));
	recorder.rxd_handler().set(m_maincpu, FUNC(tmpz84c015_device::rxa_w));

	rs232_port_device &player1(RS232_PORT(config, "player1", default_rs232_devices, nullptr));
	player1.rxd_handler().set(m_maincpu, FUNC(tmpz84c015_device::rxb_w));

	rs232_port_device &player2(RS232_PORT(config, "player2", default_rs232_devices, nullptr));
	player2.rxd_handler().set("external_sio", FUNC(z80dart_device::rxa_w));

	rs232_port_device &edl_inout(RS232_PORT(config, "edl_inout", default_rs232_devices, nullptr));
	edl_inout.rxd_handler().set("external_sio", FUNC(z80dart_device::rxb_w));

	rs232_port_device &switcher(RS232_PORT(config, "switcher", default_rs232_devices, nullptr));
	switcher.rxd_handler().set(m_subcpu, FUNC(tmpz84c015_device::rxa_w));

	rs232_port_device &serial_mixer(RS232_PORT(config, "serial_mixer", default_rs232_devices, nullptr));
	serial_mixer.rxd_handler().set(m_subcpu, FUNC(tmpz84c015_device::rxb_w));

	clock_device &clk1(CLOCK(config, "clk1", 12_MHz_XTAL / 20));
	clk1.signal_handler().set(m_maincpu, FUNC(tmpz84c015_device::rxca_w));
	clk1.signal_handler().append(m_maincpu, FUNC(tmpz84c015_device::txca_w));
	clk1.signal_handler().append(m_maincpu, FUNC(tmpz84c015_device::rxcb_w));
	clk1.signal_handler().append(m_maincpu, FUNC(tmpz84c015_device::txcb_w));
	clk1.signal_handler().append(m_subcpu, FUNC(tmpz84c015_device::rxca_w));
	clk1.signal_handler().append(m_subcpu, FUNC(tmpz84c015_device::txca_w));
	clk1.signal_handler().append(m_subcpu, FUNC(tmpz84c015_device::rxcb_w));
	clk1.signal_handler().append(m_subcpu, FUNC(tmpz84c015_device::txcb_w));

	/* ICF5: 2kbytes of RAM shared between the two CPUs (dual-port RAM)*/
	mb8421_device &mb8421(MB8421(config, "mb8421"));
	mb8421.intl_callback().set(FUNC(pve500_state::mb8421_intl));
	mb8421.intr_callback().set(FUNC(pve500_state::mb8421_intr));

	/* video hardware */
	config.set_default_layout(layout_pve500);

	/* audio hardware */
	SPEAKER(config, "mono").front_center();
	BEEP(config, "buzzer", 12_MHz_XTAL / 3200).add_route(ALL_OUTPUTS, "mono", 0.05); // 3.75 kHz CLK2 coming out of IC D4 (frequency divider circuitry)
}