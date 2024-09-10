/*
 * Rtt_tol is the fractional tollerance for RTT comparisons.
 * If a later (further down the list) host's RTT is less than
 * 1/Rtt_tol better than my current best then I don't bother
 * with it.  This biases me towards entries at the top of the list
 * which Active Directory has already chosen for me and prevents
 * noise in RTTs from pushing me to more distant machines.
 */
static int
remap(Dfscache *cp, Refer *re)
{
	int n;
	long rtt;
	char *p, *a[4];
	enum {
		Hostname = 1,
		Sharename = 2,
		Pathname = 3,

		Rtt_tol = 10
	};

	if(Debug && strstr(Debug, "dfs") != nil)
		print("	remap %s\n", re->addr);

	for(p = re->addr; *p; p++)
		if(*p == '\\')
			*p = '/';

	if(cp->prox < re->prox){
		if(Debug && strstr(Debug, "dfs") != nil)
			print("	remap %d < %d\n", cp->prox, re->prox);
		return -1;
	}
	if((n = getfields(re->addr, a, sizeof(a), 0, "/")) < 3){
		if(Debug && strstr(Debug, "dfs") != nil)
			print("	remap nfields=%d\n", n);
		return -1;
	}
	if((rtt = ping(a[Hostname], Dfstout)) == -1){
		if(Debug && strstr(Debug, "dfs") != nil)
			print("	remap ping failed\n");
		return -1;
	}
	if(cp->rtt < rtt && (rtt/labs(rtt-cp->rtt)) < Rtt_tol){
		if(Debug && strstr(Debug, "dfs") != nil)
			print("	remap bad ping %ld < %ld && %ld < %d\n",
				cp->rtt, rtt, (rtt/labs(rtt-cp->rtt)), Rtt_tol);
		return -1;
	}

	if(n < 4)
		a[Pathname] = "";
	if(re->ttl == 0)
		re->ttl = 60*5;

	free(cp->host);
	free(cp->share);
	free(cp->path);
	cp->rtt = rtt;
	cp->prox = re->prox;
	cp->expiry = time(nil)+re->ttl;
	cp->host = estrdup9p(a[Hostname]);
	cp->share = estrdup9p(trimshare(a[Sharename]));
	cp->path = estrdup9p(a[Pathname]);
	if(Debug && strstr(Debug, "dfs") != nil)
		print("	remap ping OK prox=%d host=%s share=%s path=%s\n",
			cp->prox, cp->host, cp->share, cp->path);
	return 0;
}