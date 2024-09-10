void acorn_vib_device::device_add_mconfig(machine_config &config)
{
	INPUT_MERGER_ANY_HIGH(config, m_irqs).output_handler().set(FUNC(acorn_vib_device::irq_w));

	VIA6522(config, m_via6522, XTAL(1'000'000));
	m_via6522->writepa_handler().set("cent_data_out", FUNC(output_latch_device::bus_w));
	m_via6522->ca2_handler().set(m_centronics, FUNC(centronics_device::write_strobe));
	m_via6522->irq_handler().set(m_irqs, FUNC(input_merger_device::in_w<0>));

	CENTRONICS(config, m_centronics, centronics_devices, "printer");
	m_centronics->ack_handler().set(m_via6522, FUNC(via6522_device::write_ca1));
	m_centronics->busy_handler().set(m_via6522, FUNC(via6522_device::write_pa7));
	output_latch_device &cent_data_out(OUTPUT_LATCH(config, "cent_data_out"));
	m_centronics->set_output_latch(cent_data_out);

	I8255(config, m_ppi8255, 0);

	ACIA6850(config, m_acia, 0);
	m_acia->txd_handler().set(m_rs232, FUNC(rs232_port_device::write_txd));
	m_acia->rts_handler().set(m_rs232, FUNC(rs232_port_device::write_rts));
	m_acia->irq_handler().set(m_irqs, FUNC(input_merger_device::in_w<1>));

	RS232_PORT(config, m_rs232, default_rs232_devices, nullptr);
	m_rs232->rxd_handler().set(m_acia, FUNC(acia6850_device::write_rxd));
	m_rs232->cts_handler().set(m_acia, FUNC(acia6850_device::write_cts));
	m_rs232->dcd_handler().set(m_acia, FUNC(acia6850_device::write_dcd));

	CLOCK(config, m_acia_clock, 1.8432_MHz_XTAL);
	m_acia_clock->signal_handler().set(FUNC(acorn_vib_device::write_acia_clock));
}