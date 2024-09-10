/** Initializes the XOSC32K crystal failure detector, and starts it.
 *
 *  \param[in]  ok_callback    Callback function to run upon XOSC32K operational
 *  \param[in]  fail_callback  Callback function to run upon XOSC32K failure
 */
static void init_xosc32k_fail_detector(
		const tc_callback_t ok_callback,
		const tc_callback_t fail_callback)
{
	/* TC pairs share the same clock, ensure reference and crystal timers use
	 * different clocks */
	Assert(Abs(_tc_get_inst_index(CONF_TC_OSC32K) -
			_tc_get_inst_index(CONF_TC_XOSC32K)) >= 2);

	/* The crystal detection cycle count must be less than the reference cycle
	 * count, so that the reference timer is periodically reset before expiry */
	Assert(CRYSTAL_RESET_CYCLES < CRYSTAL_FAIL_CYCLES);

	/* Must use different clock generators for the crystal and reference, must
	 * not be CPU generator 0 */
	Assert(GCLK_GENERATOR_XOSC32K != GCLK_GENERATOR_OSC32K);
	Assert(GCLK_GENERATOR_XOSC32K != GCLK_GENERATOR_0);
	Assert(GCLK_GENERATOR_OSC32K  != GCLK_GENERATOR_0);

	/* Configure and enable the XOSC32K GCLK generator */
	struct system_gclk_gen_config xosc32k_gen_conf;
	system_gclk_gen_get_config_defaults(&xosc32k_gen_conf);
	xosc32k_gen_conf.source_clock = SYSTEM_CLOCK_SOURCE_XOSC32K;
	system_gclk_gen_set_config(GCLK_GENERATOR_XOSC32K, &xosc32k_gen_conf);
	system_gclk_gen_enable(GCLK_GENERATOR_XOSC32K);

	/* Configure and enable the reference clock GCLK generator */
	struct system_gclk_gen_config ref_gen_conf;
	system_gclk_gen_get_config_defaults(&ref_gen_conf);
	ref_gen_conf.source_clock = SYSTEM_CLOCK_SOURCE_OSC32K;
	system_gclk_gen_set_config(GCLK_GENERATOR_OSC32K, &ref_gen_conf);
	system_gclk_gen_enable(GCLK_GENERATOR_OSC32K);

	/* Set up crystal counter - when target count elapses, trigger event */
	struct tc_config tc_xosc32k_conf;
	tc_get_config_defaults(&tc_xosc32k_conf);
	tc_xosc32k_conf.clock_source = GCLK_GENERATOR_XOSC32K;
	tc_xosc32k_conf.counter_16_bit.compare_capture_channel[0] =
			CRYSTAL_RESET_CYCLES;
	tc_xosc32k_conf.wave_generation = TC_WAVE_GENERATION_MATCH_FREQ;
	tc_init(&tc_xosc32k, CONF_TC_XOSC32K, &tc_xosc32k_conf);

	/* Set up reference counter - when event received, restart */
	struct tc_config tc_osc32k_conf;
	tc_get_config_defaults(&tc_osc32k_conf);
	tc_osc32k_conf.clock_source = GCLK_GENERATOR_OSC32K;
	tc_osc32k_conf.counter_16_bit.compare_capture_channel[0] =
			CRYSTAL_FAIL_CYCLES;
	tc_osc32k_conf.wave_generation = TC_WAVE_GENERATION_MATCH_FREQ;
	tc_init(&tc_osc32k, CONF_TC_OSC32K, &tc_osc32k_conf);

	/* Configure event channel and link it to the xosc32k counter */
	struct events_config config;
	struct events_resource event;
	events_get_config_defaults(&config);
	config.edge_detect  = EVENTS_EDGE_DETECT_NONE;
	config.generator    = CONF_EVENT_GENERATOR_ID;
	config.path         = EVENTS_PATH_ASYNCHRONOUS;
	events_allocate(&event, &config);
	/* Configure event user and link it to the osc32k counter */
	events_attach_user(&event, CONF_EVENT_USED_ID);

	/* Enable event generation for crystal counter */
	struct tc_events tc_xosc32k_events = { .generate_event_on_overflow = true };
	tc_enable_events(&tc_xosc32k, &tc_xosc32k_events);

	/* Enable event reception for reference counter */
	struct tc_events tc_osc32k_events = { .on_event_perform_action = true };
	tc_osc32k_events.event_action = TC_EVENT_ACTION_RETRIGGER;
	tc_enable_events(&tc_osc32k, &tc_osc32k_events);

	/* Enable overflow callback for the crystal counter - if crystal count
	 * has been reached, crystal is operational */
	tc_register_callback(&tc_xosc32k, ok_callback, TC_CALLBACK_CC_CHANNEL0);
	tc_enable_callback(&tc_xosc32k, TC_CALLBACK_CC_CHANNEL0);

	/* Enable compare callback for the reference counter - if reference count
	 * has been reached, crystal has failed */
	tc_register_callback(&tc_osc32k, fail_callback, TC_CALLBACK_CC_CHANNEL0);
	tc_enable_callback(&tc_osc32k, TC_CALLBACK_CC_CHANNEL0);

	/* Start both crystal and reference counters */
	tc_enable(&tc_xosc32k);
	tc_enable(&tc_osc32k);
}

/** Main application entry point. */
int main(void)
{
	system_init();

	system_flash_set_waitstates(2);

	init_osc32k();
	init_xosc32k();
	init_xosc32k_fail_detector(
			xosc32k_ok_callback, xosc32k_fail_callback);

#if ENABLE_CPU_CLOCK_OUT == true
	/* Configure a GPIO pin as the CPU clock output */
	struct system_pinmux_config clk_out_pin;
	system_pinmux_get_config_defaults(&clk_out_pin);
	clk_out_pin.direction    = SYSTEM_PINMUX_PIN_DIR_OUTPUT;
	clk_out_pin.mux_position = CONF_CLOCK_PIN_MUX;
	system_pinmux_pin_set_config(CONF_CLOCK_PIN_OUT, &clk_out_pin);
#endif

	for (;;) {
		static bool old_run_osc = true;
		bool new_run_osc =
				(port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_INACTIVE);

		/* Check if the XOSC32K needs to be started or stopped when the board
		 * button is pressed or released */
		if (new_run_osc != old_run_osc) {
			if (new_run_osc) {
				system_clock_source_enable(SYSTEM_CLOCK_SOURCE_XOSC32K);
				while(!system_clock_source_is_ready(
						SYSTEM_CLOCK_SOURCE_XOSC32K));
			}
			else {
				system_clock_source_disable(SYSTEM_CLOCK_SOURCE_XOSC32K);
			}

			old_run_osc = new_run_osc;
		}
	}
}