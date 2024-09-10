static char *
print(char *buf, size_t *len, char * const args[])
{
    static char s[2048];
    char src[20], dst[20];
    struct in_addr saddr, daddr;
    FLOWDESC *x; 
    time_t ts;


    if (buf == NULL && args != NULL) { 
        *len = sprintf(s, PRETTYHDR); 
        return s; 
    } 

    if (buf == NULL && args == NULL) { 
        *len = 0; 
        return s; 
    } 

    x = (FLOWDESC *) buf;
    ts = (time_t)ntohl(x->ts);
    saddr.s_addr = N32(x->src_ip);
    daddr.s_addr = N32(x->dst_ip);
    sprintf(src, "%s", inet_ntoa(saddr));
    sprintf(dst, "%s", inet_ntoa(daddr)); 

    *len = sprintf(s, PRETTYFMT, 
		asctime(localtime(&ts)), (uint) x->proto, 
		src, (uint) H16(x->src_port), 
		dst, (uint) H16(x->dst_port), 
	        NTOHLL(x->bytes), NTOHLL(x->pkts));
    return s;
};