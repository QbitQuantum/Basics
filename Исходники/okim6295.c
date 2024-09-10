void okim6295_device::device_clock_changed()
{
	int divisor = m_pin7_state ? 132 : 165;
	m_stream->set_sample_rate(clock() / divisor);
}