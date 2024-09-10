static void update_interrupt_state(running_machine &machine)
{
	compis_state *state = machine.driver_data<compis_state>();
	int i, j, new_vector = 0;

	if (LOG_INTERRUPTS) logerror("update_interrupt_status: req=%02X stat=%02X serv=%02X\n", state->m_i186.intr.request, state->m_i186.intr.status, state->m_i186.intr.in_service);

	/* loop over priorities */
	for (i = 0; i <= state->m_i186.intr.priority_mask; i++)
	{
		/* note: by checking 4 bits, we also verify that the mask is off */
		if ((state->m_i186.intr.timer & 15) == i)
		{
			/* if we're already servicing something at this level, don't generate anything new */
			if (state->m_i186.intr.in_service & 0x01)
				return;

			/* if there's something pending, generate an interrupt */
			if (state->m_i186.intr.status & 0x07)
			{
				if (state->m_i186.intr.status & 1)
					new_vector = 0x08;
				else if (state->m_i186.intr.status & 2)
					new_vector = 0x12;
				else if (state->m_i186.intr.status & 4)
					new_vector = 0x13;
				else
					popmessage("Invalid timer interrupt!");

				/* set the clear mask and generate the int */
				state->m_i186.intr.ack_mask = 0x0001;
				goto generate_int;
			}
		}

		/* check DMA interrupts */
		for (j = 0; j < 2; j++)
			if ((state->m_i186.intr.dma[j] & 15) == i)
			{
				/* if we're already servicing something at this level, don't generate anything new */
				if (state->m_i186.intr.in_service & (0x04 << j))
					return;

				/* if there's something pending, generate an interrupt */
				if (state->m_i186.intr.request & (0x04 << j))
				{
					new_vector = 0x0a + j;

					/* set the clear mask and generate the int */
					state->m_i186.intr.ack_mask = 0x0004 << j;
					goto generate_int;
				}
			}

		/* check external interrupts */
		for (j = 0; j < 4; j++)
			if ((state->m_i186.intr.ext[j] & 15) == i)
			{
				/* if we're already servicing something at this level, don't generate anything new */
				if (state->m_i186.intr.in_service & (0x10 << j))
					return;

				/* if there's something pending, generate an interrupt */
				if (state->m_i186.intr.request & (0x10 << j))
				{
					/* otherwise, generate an interrupt for this request */
					new_vector = 0x0c + j;

					/* set the clear mask and generate the int */
					state->m_i186.intr.ack_mask = 0x0010 << j;
					goto generate_int;
				}
			}
	}
	return;

generate_int:
	/* generate the appropriate interrupt */
	state->m_i186.intr.poll_status = 0x8000 | new_vector;
	if (!state->m_i186.intr.pending)
		cputag_set_input_line(machine, "maincpu", 0, ASSERT_LINE);
	state->m_i186.intr.pending = 1;
	machine.scheduler().trigger(CPU_RESUME_TRIGGER);
	if (LOG_OPTIMIZATION) logerror("  - trigger due to interrupt pending\n");
	if (LOG_INTERRUPTS) logerror("(%f) **** Requesting interrupt vector %02X\n", machine.time().as_double(), new_vector);
}