void vt100_keyboard_device::device_add_mconfig(machine_config &config)
{
	SPEAKER(config, "mono").front_center();
	BEEP(config, m_speaker, 786); // 7.945us per serial clock = ~125865.324hz, / 160 clocks per char = ~ 786 hz
	m_speaker->add_route(ALL_OUTPUTS, "mono", 0.50);

	AY31015(config, m_uart);
	m_uart->write_so_callback().set(FUNC(vt100_keyboard_device::signal_out_w));

	RIPPLE_COUNTER(config, m_scan_counter); // 2x 74LS93
	m_scan_counter->set_stages(8);
	m_scan_counter->count_out_cb().set(FUNC(vt100_keyboard_device::key_scan_w));
}