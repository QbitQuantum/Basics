UINT8 z80sio_device::sio_channel::data_read()
{
	// update the status register
	m_status[0] &= ~SIO_RR0_RX_CHAR_AVAILABLE;

	// reset the receive interrupt
	clear_interrupt(INT_RECEIVE);

	VPRINTF(("%s:sio_data_r(%c) = %02X\n", m_device->machine().describe_context(), 'A' + m_index, m_inbuf));

	return m_inbuf;
}