void z80ctc_device::device_reset()
{
	// reset each channel
	m_channel[0].reset();
	m_channel[1].reset();
	m_channel[2].reset();
	m_channel[3].reset();

	// check for interrupts
	interrupt_check();
	VPRINTF(("CTC Reset\n"));
}