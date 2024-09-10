/*
 * inet_setip_raw: fills the `ip' inet_prefix struct with `data' and `family'.
 */
int inet_setip_raw(inet_prefix *ip, u_int *data, int family)
{
	ip->family=family;
	setzero(ip->data, sizeof(ip->data));
	
	if(family==AF_INET) {
		ip->data[0]=data[0];
		ip->len=4;
	} else if(family==AF_INET6) {
		memcpy(ip->data, data, sizeof(ip->data));
		ip->len=16;
	} else 
		fatal(ERROR_MSG "family not supported", ERROR_POS);

	ip->bits=ip->len<<3; /* bits=len*8 */
	
	return 0;
}