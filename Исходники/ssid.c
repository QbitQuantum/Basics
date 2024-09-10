static char *
print(__unused void * self, char *buf, size_t *len, char * const args[])
{
    static char s[512];
    static char * fmt; 
    FLOWDESC *x; 
    timestamp_t ts;
    time_t t; 
    char ssid[34];
    uint8_t sig, noise;
 
    if (buf == NULL && args != NULL) { 
	int n; 

	/* first call of print, process the arguments and return */
	for (n = 0; args[n]; n++) {
	    if (!strcmp(args[n], "format=plain")) {
		*len = 0; 
		fmt = PLAINFMT;
		return s; 
	    } 
	} 
	/* by default, pretty print */
	*len = sprintf(s, PRETTYHDR);  
	fmt = PRETTYFMT; 
	return s; 
    } 

    if (buf == NULL && args == NULL) { 
	*len = 0;
	return s; 
    } 
	
    x = (FLOWDESC *) buf; 
    ts = NTOHLL(x->ts);
    t = (time_t) TS2SEC(ts); 
    snprintf(ssid, x->len+1, x->ssid);   
    sig = (uint8_t)(ntohl(x->signal) / x->samples); 
    noise = (uint8_t)(ntohl(x->noise) / x->samples); 
    
    /* print according to the requested format */
    if (fmt == PRETTYFMT) {
	char * wepmode = x->wepmode? "Y": "N"; 
	*len = sprintf(s, fmt, asctime(localtime(&t)), (sig-256), (noise-256),
					x->channel, x->samples, wepmode, ssid); 
    } else {
	*len = sprintf(s, fmt, (long int) t, x->wepmode, 
		   x->channel, (sig-256), (noise-256), x->samples); 
    } 

    return s;
}