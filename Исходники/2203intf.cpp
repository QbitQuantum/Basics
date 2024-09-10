void ym2203_device::device_clock_changed()
{
	calculate_rates();
	ym2203_clock_changed(m_chip, clock(), clock() / 72);
}