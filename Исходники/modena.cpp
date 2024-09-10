void mephisto_modena_state::modena(machine_config &config)
{
	M65C02(config, m_maincpu, XTAL(4'194'304));          // W65C02SP
	m_maincpu->set_addrmap(AS_PROGRAM, &mephisto_modena_state::modena_mem);
	timer_device &nmi_on(TIMER(config, "nmi_on"));
	nmi_on.configure_periodic(FUNC(mephisto_modena_state::nmi_on), attotime::from_hz(XTAL(4'194'304) / (1 << 13)));
	nmi_on.set_start_delay(attotime::from_hz(XTAL(4'194'304) / (1 << 13)) - attotime::from_usec(975));  // active for 975us
	TIMER(config, "nmi_off").configure_periodic(FUNC(mephisto_modena_state::nmi_off), attotime::from_hz(XTAL(4'194'304) / (1 << 13)));

	NVRAM(config, "nvram", nvram_device::DEFAULT_ALL_0);

	MEPHISTO_BUTTONS_BOARD(config, m_board, 0);
	m_board->set_disable_leds(true);
	config.set_default_layout(layout_mephisto_modena);

	/* sound hardware */
	SPEAKER(config, "mono").front_center();
	BEEP(config, m_beeper, 3250).add_route(ALL_OUTPUTS, "mono", 1.0);
}