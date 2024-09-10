const char *strxf_proto(__u8 proto)
{
	static char buf[32];
	struct protoent *pp;
	const char *p;

	pp = getprotobynumber(proto);
	if (pp)
		p = pp->p_name;
	else {
		sprintf(buf, "%u", proto);
		p = buf;
	}

	return p;
}