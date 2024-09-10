void z80ctc_device::ctc_channel::trigger(UINT8 data)
{
	// normalize data
	data = data ? 1 : 0;

	// see if the trigger value has changed
	if (data != m_extclk)
	{
		m_extclk = data;

		// see if this is the active edge of the trigger
		if (((m_mode & EDGE) == EDGE_RISING && data) || ((m_mode & EDGE) == EDGE_FALLING && !data))
		{
			// if we're waiting for a trigger, start the timer
			if ((m_mode & WAITING_FOR_TRIG) && (m_mode & MODE) == MODE_TIMER)
			{
				attotime curperiod = period();
				VPRINTF(("CTC period %s\n", curperiod.as_string()));
				m_timer->adjust(curperiod, m_index, curperiod);
			}

			// we're no longer waiting
			m_mode &= ~WAITING_FOR_TRIG;

			// if we're clocking externally, decrement the count
			if ((m_mode & MODE) == MODE_COUNTER)
			{
				// if we hit zero, do the same thing as for a timer interrupt
				if (--m_down == 0)
					timer_callback();
			}
		}
	}
}