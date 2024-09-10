void
mangle_mapped_sockaddr(struct sockaddr *in)
{
	struct sockaddr_in6 *in6 = (struct sockaddr_in6 *)in;								

	if(in->sa_family == AF_INET)
		return;

	if(in->sa_family == AF_INET6 && IN6_IS_ADDR_V4MAPPED(&in6->sin6_addr))
	{
		struct sockaddr_in in4;
		memset(&in4, 0, sizeof(struct sockaddr_in));
		in4.sin_family = AF_INET;
		in4.sin_port = in6->sin6_port;
		in4.sin_addr.s_addr = ((uint32_t *)&in6->sin6_addr)[3];
		memcpy(in, &in4, sizeof(struct sockaddr_in)); 		
	}	
	return;
}