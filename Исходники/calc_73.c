static int		set_clock	(CalcHandle* handle, CalcClock* _clock)
{
	int ret;
	uint8_t buffer[9];
	uint32_t calc_time;

	struct tm ref, cur;
	time_t r, c, now;

	time(&now);	// retrieve current DST setting
	memcpy(&ref, localtime(&now), sizeof(struct tm));

	ref.tm_year = 1997 - 1900;
	ref.tm_mon = 0;
	ref.tm_yday = 0;
	ref.tm_mday = 1;
	ref.tm_wday = 3;
	ref.tm_hour = 0;
	ref.tm_min = 0;
	ref.tm_sec = 0;
	//ref.tm_isdst = 1;
	r = mktime(&ref);
	//printf("%s\n", asctime(&ref));

	cur.tm_year = _clock->year - 1900;
	cur.tm_mon = _clock->month - 1;
	cur.tm_mday = _clock->day;
	cur.tm_hour = _clock->hours;
	cur.tm_min = _clock->minutes;
	cur.tm_sec = _clock->seconds;
	cur.tm_isdst = 1;
	c = mktime(&cur);
	//printf("%s\n", asctime(&cur));

	calc_time = (uint32_t)difftime(c, r);

	buffer[0] = 0;
	buffer[1] = 0;
	buffer[2] = MSB(MSW(calc_time));
	buffer[3] = LSB(MSW(calc_time));
	buffer[4] = MSB(LSW(calc_time));
	buffer[5] = LSB(LSW(calc_time));
	buffer[6] = _clock->date_format;
	buffer[7] = _clock->time_format;
	buffer[8] = 0xff;

	ticalcs_strlcpy(handle->updat->text, _("Setting clock..."), sizeof(handle->updat->text));
	ticalcs_update_label(handle);

	ret = SEND_RTS(handle, 13, TI73_CLK, "\0x08\0\0\0\0\0\0\0", 0x00, 0x00);
	if (!ret)
	{
		ret = RECV_ACK(handle, NULL);
		if (!ret)
		{
			ret = RECV_CTS(handle, 13);
			if (!ret)
			{
				ret = SEND_ACK(handle);
				if (!ret)
				{
					ret = SEND_XDP(handle, 9, buffer);
					if (!ret)
					{
						ret = RECV_ACK(handle, NULL);
						if (!ret)
						{
							ret = SEND_EOT(handle);
						}
					}
				}
			}
		}
	}

	return ret;
}