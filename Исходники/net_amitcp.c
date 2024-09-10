struct SysSocket *Sys_Net_CreateSocket(struct SysNetData *netdata, enum netaddrtype addrtype)
{
	struct SysSocket *s;
	int r;
	int one;

	one = 1;

	if (addrtype != NA_IPV4)
		return 0;

	s = AllocVec(sizeof(*s), MEMF_ANY);
	if (s)
	{
		s->s = socket(AF_INET, SOCK_DGRAM, 0);
		if (s->s != -1)
		{
			r = IoctlSocket(s->s, FIONBIO, (void *)&one);
			if (r == 0)
			{
				return s;
			}

			CloseSocket(s->s);
		}

		FreeVec(s);
	}

	return 0;
}