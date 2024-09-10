void epson_ex800_device::device_add_mconfig(machine_config &config)
{
	/* basic machine hardware */
	upd7810_device &upd(UPD7810(config, m_maincpu, 12000000)); // 12 MHz?
	upd.set_addrmap(AS_PROGRAM, &epson_ex800_device::ex800_mem);
	upd.pa_in_cb().set(FUNC(epson_ex800_device::porta_r));
	upd.pa_out_cb().set(FUNC(epson_ex800_device::porta_w));
	upd.pb_in_cb().set(FUNC(epson_ex800_device::portb_r));
	upd.pb_out_cb().set(FUNC(epson_ex800_device::portb_w));
	upd.pc_in_cb().set(FUNC(epson_ex800_device::portc_r));
	upd.pc_out_cb().set(FUNC(epson_ex800_device::portc_w));

	config.set_default_layout(layout_ex800);

	/* audio hardware */
	SPEAKER(config, "mono").front_center();
	BEEP(config, m_beeper, 4000); // measured at 4000 Hz */
	m_beeper->add_route(ALL_OUTPUTS, "mono", 1.0);
}