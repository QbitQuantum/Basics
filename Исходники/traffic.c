static char *
print(void * self, char *buf, size_t *len, char * const args[])
{
    static char s[512];
    static char * fmt; 
    static int granularity = 1; 
    static int use_bytes = 0; 
    static int no_records = 0; 
    static int64_t count[2] = {0, 0};
    config_t * cf = CONFIG(self); 
    FLOWDESC *x; 
    timestamp_t ts;
    time_t t; 
    int n; 

    if (buf == NULL && args != NULL) { 
	/* by default, pretty print */
	*len = sprintf(s, PRETTYHDR);  
	fmt = prettyfmt; 

	/* first call of print, process the arguments and return */
	for (n = 0; args[n]; n++) {
	    if (!strcmp(args[n], "format=plain")) {
		*len = 0; 
		fmt = plainfmt;
	    } else if (!strcmp(args[n], "format=gnuplot")) {
		fmt = gnuplotfmt;
	    } else if (!strcmp(args[n], "use-bytes")) { 
		use_bytes = 1;
	    } else if (!strncmp(args[n], "granularity=", 10)) {
		char * val = index(args[n], '=') + 1;

		/* aggregate multiple records into one to reduce 
		 * communication messages. 
		 */
		granularity = MAX(atoi(val) / cf->meas_ivl, 1);
	    }
	} 

	if (fmt == gnuplotfmt) { 
	    *len = sprintf(s, GNUPLOTHDR, use_bytes? "Mbps" : "packets/sec"); 
	} 

	return s; 
    } 

    if (buf == NULL && args == NULL) { 
	*len = 0;
	if (fmt == gnuplotfmt) 
	    *len = sprintf(s, GNUPLOTFOOTER);
	return s; 
    } 
	
    x = (FLOWDESC *) buf; 
    ts = NTOHLL(x->ts);
    t = (time_t) TS2SEC(ts); 

    /* aggregate records if needed */
    count[0] += use_bytes? NTOHLL(x->bytes[0]) : ntohl(x->pkts[0]);
    count[1] -= use_bytes? NTOHLL(x->bytes[1]) : ntohl(x->pkts[1]);
    no_records++;
    if (no_records % granularity != 0) { 
	*len = 0;
	return s; 
    } 

    count[0] /= granularity; 
    count[1] /= granularity;

    /* print according to the requested format */
    if (fmt == prettyfmt) {  
	*len = sprintf(s, fmt, asctime(localtime(&t)), 
		       TS2SEC(ts), TS2USEC(ts), count[0], count[1]);
    } else if (fmt == gnuplotfmt) {  
	if (use_bytes) { 
	    float mbps_in = 8.0 * (float) count[0] / 1000000.0; 
	    float mbps_out = 8.0 * (float) count[1] / 1000000.0; 
	    *len = sprintf(s, "%ld %f %f\n", (long int) t, mbps_in, mbps_out);
	} else { 
	    *len = sprintf(s, "%ld %u %u\n", (long int) t, 
			   (uint32_t) count[0], (uint32_t) count[1]);
	} 
    } else { 
	*len = sprintf(s, fmt, (long int)t, ts, count[0], count[1]); 
    }
	
    count[0] = count[1] = 0; 
    return s;
}