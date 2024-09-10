static double UnquantizeSendRate(guint16 send_rate)
{
	return (send_rate >> 4) * 10.0 / 4096.0 * pow(10.0, (send_rate & 0x000f));
}