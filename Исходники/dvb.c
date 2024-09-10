int send_jess(int fd, int freq, int pos, int pol, int hiband, int slot,
		int ufreq, int pin)
{
	struct dvb_diseqc_master_cmd cmd =
	{
	{ 0x70, 0x00, 0x00, 0x00, 0x00 }, 4 };
//	int t = (freq / 1000) - 100;
	int t = freq - 100;

	cmd.msg[1] = slot << 3;
	cmd.msg[1] |= ((t << 8) & 0x07);
	cmd.msg[2] = (t & 0xff);
	cmd.msg[3] = ((pos & 0x3f) << 2) | (pol ? 2 : 0) | (hiband ? 1 : 0);
	if (pin < 256)
	{
		cmd.msg_len = 5;
		cmd.msg[0] = 0x71;
		cmd.msg[4] = pin;
	}

	LOGL(3,
			"send_jess fd %d, freq %d, ufreq %d, pos = %d, pol = %d, hiband = %d, slot %d, diseqc => %02x %02x %02x %02x %02x",
			fd, freq, ufreq, pos, pol, hiband, slot, cmd.msg[0], cmd.msg[1],
			cmd.msg[2], cmd.msg[3], cmd.msg[4]);

	if (ioctl(fd, FE_SET_VOLTAGE, SEC_VOLTAGE_13) == -1)
		LOG("send_jess: pre voltage  SEC_VOLTAGE_13 failed for fd %d: %s", fd,
				strerror(errno));
	usleep(15000);
	if (ioctl(fd, FE_SET_TONE, SEC_TONE_OFF) == -1)
		LOG("send_jess: FE_SET_TONE failed for fd %d: %s", fd, strerror(errno));
	if (ioctl(fd, FE_SET_VOLTAGE, SEC_VOLTAGE_18) == -1)
		LOG("send_jess: FE_SET_VOLTAGE failed for fd %d: %s", fd,
				strerror(errno));
	usleep(15000);
	if (ioctl(fd, FE_DISEQC_SEND_MASTER_CMD, &cmd) == -1)
		LOG("send_jess: FE_DISEQC_SEND_MASTER_CMD failed for fd %d: %s", fd,
				strerror(errno));
	usleep(15000);
	if (ioctl(fd, FE_SET_VOLTAGE, SEC_VOLTAGE_13) == -1)
		LOG("send_jess: FE_SET_VOLTAGE failed for fd %d: %s", fd,
				strerror(errno));

	return ufreq * 1000;
}