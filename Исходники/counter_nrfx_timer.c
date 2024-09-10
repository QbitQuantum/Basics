static int counter_nrfx_cancel_alarm(struct device *dev, u8_t chan_id)
{
	_disable(dev, chan_id);

	return 0;
}