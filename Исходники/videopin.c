static void update_plunger(running_machine &machine)
{
	videopin_state *state = machine.driver_data<videopin_state>();
	UINT8 val = input_port_read(machine, "IN2");

	if (state->m_prev != val)
	{
		if (val == 0)
		{
			state->m_time_released = machine.time();

			if (!state->m_mask)
				cputag_set_input_line(machine, "maincpu", INPUT_LINE_NMI, ASSERT_LINE);
		}
		else
			state->m_time_pushed = machine.time();

		state->m_prev = val;
	}
}