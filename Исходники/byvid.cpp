void by133_state::babypac(machine_config &config)
{
	/* basic machine hardware */
	M6800(config, m_maincpu, XTAL(3'579'545)/4); // no xtal, just 2 chips
	m_maincpu->set_addrmap(AS_PROGRAM, &by133_state::main_map);

	MC6809(config, m_videocpu, XTAL(3'579'545));
	m_videocpu->set_addrmap(AS_PROGRAM, &by133_state::video_map);

	M6803(config, m_audiocpu, XTAL(3'579'545));
	m_audiocpu->set_addrmap(AS_PROGRAM, &by133_state::sound_map);
	m_audiocpu->out_p1_cb().set("dac", FUNC(dac_byte_interface::data_w)); // P10-P17
	m_audiocpu->in_p2_cb().set(FUNC(by133_state::m6803_port2_r)); // P20-P24 sound command in
	m_audiocpu->out_p2_cb().set(FUNC(by133_state::m6803_port2_w));

	NVRAM(config, "nvram", nvram_device::DEFAULT_ALL_0);

	PIA6821(config, m_pia_u7, 0);
	m_pia_u7->readpa_handler().set(FUNC(by133_state::u7_a_r));
	m_pia_u7->writepa_handler().set(FUNC(by133_state::u7_a_w));
	m_pia_u7->readpb_handler().set(FUNC(by133_state::u7_b_r));
	m_pia_u7->writepb_handler().set(FUNC(by133_state::u7_b_w));
	m_pia_u7->ca2_handler().set(FUNC(by133_state::u7_ca2_w));
	m_pia_u7->cb2_handler().set(FUNC(by133_state::u7_cb2_w));
	m_pia_u7->irqa_handler().set_inputline("videocpu", M6809_FIRQ_LINE);
	m_pia_u7->irqa_handler().set_inputline("videocpu", M6809_FIRQ_LINE);

	PIA6821(config, m_pia_u10, 0);
	m_pia_u10->readpa_handler().set(FUNC(by133_state::u10_a_r));
	m_pia_u10->writepa_handler().set(FUNC(by133_state::u10_a_w));
	m_pia_u10->readpb_handler().set(FUNC(by133_state::u10_b_r));
	m_pia_u10->writepb_handler().set(FUNC(by133_state::u10_b_w));
	m_pia_u10->ca2_handler().set(FUNC(by133_state::u10_ca2_w));
	m_pia_u10->cb2_handler().set(FUNC(by133_state::u10_cb2_w));
	m_pia_u10->irqa_handler().set_inputline("maincpu", M6800_IRQ_LINE);
	m_pia_u10->irqb_handler().set_inputline("maincpu", M6800_IRQ_LINE);
	TIMER(config, "babypac1").configure_periodic(FUNC(by133_state::u10_timer), attotime::from_hz(120)); // mains freq*2

	PIA6821(config, m_pia_u11, 0);
	m_pia_u11->readpa_handler().set(FUNC(by133_state::u11_a_r));
	m_pia_u11->writepa_handler().set(FUNC(by133_state::u11_a_w));
	m_pia_u11->readpb_handler().set(FUNC(by133_state::u11_b_r));
	m_pia_u11->writepb_handler().set(FUNC(by133_state::u11_b_w));
	m_pia_u11->ca2_handler().set(FUNC(by133_state::u11_ca2_w));
	m_pia_u11->cb2_handler().set(FUNC(by133_state::u11_cb2_w));
	m_pia_u11->irqa_handler().set_inputline("maincpu", M6800_IRQ_LINE);
	m_pia_u11->irqb_handler().set_inputline("maincpu", M6800_IRQ_LINE);
	TIMER(config, "babypac2").configure_periodic(FUNC(by133_state::u11_timer), attotime::from_hz(634)); // 555 timer*2

	/* video hardware */
	TMS9928A(config, m_crtc, XTAL(10'738'635)).set_screen("screen");
	m_crtc->set_vram_size(0x4000);
	m_crtc->int_callback().set_inputline(m_videocpu, M6809_IRQ_LINE);
	SCREEN(config, "screen", SCREEN_TYPE_RASTER);

	/* sound hardware */
	SPEAKER(config, "speaker").front_center();
	ZN429E(config, "dac", 0).add_route(ALL_OUTPUTS, "speaker", 0.25); // U32 (Vidiot) or U6 (Cheap Squeak)
	voltage_regulator_device &vref(VOLTAGE_REGULATOR(config, "vref"));
	vref.add_route(0, "dac", 1.0, DAC_VREF_POS_INPUT);
	vref.add_route(0, "dac", -1.0, DAC_VREF_NEG_INPUT);

	SPEAKER(config, "beee").front_center();
	BEEP(config, m_beep, 600).add_route(ALL_OUTPUTS, "beee", 0.10);
}