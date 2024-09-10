static char *
print(void * self, char *buf, size_t *len, char * const args[])
{
    static char s[512];
    static char * fmt; 
    static int granularity = 1; 
    static int no_records = 0; 
    static uint64_t bytes = 0;
    static uint64_t pkts = 0;
    CONFIGDESC * config = CONFIG(self); 
    FLOWDESC *x; 
    timestamp_t ts;
    time_t t; 
    int n; 

    if (buf == NULL && args != NULL) { 
	/* by default, pretty print */
	*len = sprintf(s, PRETTYHDR);  
	fmt = PRETTYFMT; 

	/* first call of print, process the arguments and return */
	for (n = 0; args[n]; n++) {
	    if (!strcmp(args[n], "format=plain")) {
		*len = 0; 
		fmt = PLAINFMT;
	    } else if (!strcmp(args[n], "format=gnuplot")) {
		*len = sprintf(s, GNUPLOTHDR); 
		fmt = GNUPLOTFMT;
	    } else if (!strncmp(args[n], "granularity=", 10)) {
		char * val = index(args[n], '=') + 1;

		/* aggregate multiple records into one to reduce 
		 * communication messages. 
		 */
		granularity = MAX(atoi(val) / config->meas_ivl, 1);
	    } else if (!strcmp(args[n], "format=mbps")) {
		*len = 0; 
		fmt = MBPSFMT; 
	    } 
	} 

	return s; 
    } 

    if (buf == NULL && args == NULL) { 
	*len = 0;
	if (fmt == GNUPLOTFMT) 
	    *len = sprintf(s, GNUPLOTFOOTER);
	return s; 
    } 
	
    x = (FLOWDESC *) buf; 
    ts = NTOHLL(x->ts);
    t = (time_t) TS2SEC(ts); 

    /* aggregate records if needed */
    pkts += ntohl(x->pkts);
    bytes += NTOHLL(x->bytes);
    no_records++;
    if (no_records % granularity != 0) { 
	*len = 0;
	return s; 
    } 

    bytes /= granularity; 
    pkts /= granularity;

    /* print according to the requested format */
    if (fmt == PRETTYFMT) {
	*len = sprintf(s, fmt, 
	               asctime(localtime(&t)), TS2SEC(ts), TS2USEC(ts), 
		       bytes, pkts); 
    } else if (fmt == GNUPLOTFMT) {
	float mbps = 8.0 * (float) bytes / 1000000.0; 
	*len = sprintf(s, fmt, (long int)t, mbps, pkts);
    } else if (fmt == MBPSFMT) { 
	float mbps = 8.0 * (float) bytes / 1000000.0; 
	*len = sprintf(s, fmt, mbps); 
    } else { 
	*len = sprintf(s, fmt, (long int)t, ts, bytes, pkts); 
    } 
	
    pkts = bytes = 0;
    return s;
}