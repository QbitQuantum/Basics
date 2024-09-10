int satipc_rtcp_reply(sockets * s)
{
	unsigned char *b = s->buf, *ver, *signal;
	char *tun;
	int i, rlen = s->rlen;
	adapter *ad = get_adapter(s->sid);
	int strength, status, snr;
	uint32_t rp;
	if (!ad)
		return 0;
//	LOG("satip_rtcp_reply called");
	if (b[0] == 0x80 && b[1] == 0xC8)
	{
		copy32r(rp, b, 20);

		if ((++ad->repno % 100) == 0)  //every 20s
			LOG(
					"satipc: rtp report, adapter %d: rtcp missing packets %d, rtp missing %d, rtp ooo %d, pid err %d",
					ad->id, rp - ad->rcvp, ad->rtp_miss, ad->rtp_ooo,
					ad->pid_err - ad->dec_err);
	}
	for (i = 0; i < rlen - 4; i++)
		if (b[i] == 'v' && b[i + 1] == 'e' && b[i + 2] == 'r'
				&& b[i + 3] == '=')
		{
			ver = b + i;
			tun = strstr((const char*) ver, "tuner=");
			if (tun)
				signal = strchr(tun, ',');
			if (signal)
			{
				sscanf(signal + 1, "%d,%d,%d", &strength, &status, &snr);
				if (ad->strength != strength && ad->snr != snr)
					LOGL(3,
							"satipc: Received signal status from the server for adapter %d, stength=%d status=%d snr=%d",
							ad->id, strength, status, snr);
				ad->strength = strength;
				ad->status = status ? FE_HAS_LOCK : 0;
				ad->snr = snr;
			}
		}
	return 0;
}