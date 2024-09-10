int netcv_set_pid(adapter *ad, uint16_t pid)
{
	//fprintf(stderr, "REEL: netcv_set_pid (id=%d, pid=%d)\n", ad->id, pid);

	int aid = ad->id;
	LOGL(3, "netceiver: set_pid for adapter %d, pid %d, err %d", aid, pid, SN.err);

	if (SN.err) // error reported, return error
		return 0;

	SN.npid[SN.lp] = pid;
	SN.lp++;
	SN.want_commit = 1;

	return aid + 100;
}