const char *inet_ntop(int af, const void *src, char *dst, size_t size)
{
	switch (af) {
		case AF_INET:
			return inet_ntop_v4(src, dst, size);
		default:
			Set_errno(EAFNOSUPPORT);
			return NULL;
	}
}