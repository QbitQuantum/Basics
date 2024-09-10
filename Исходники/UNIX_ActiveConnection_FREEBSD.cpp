static int set_default_protos(void)
{
	struct protoent *prot;
	const char *pname;
	size_t pindex;

	init_protos(default_numprotos);

	for (pindex = 0; pindex < default_numprotos; pindex++) {
		pname = default_protos[pindex];
		prot = getprotobyname(pname);
		if (prot == NULL)
			err(1, "getprotobyname: %s", pname);
		protos[pindex] = prot->p_proto;
	}
	numprotos = pindex;
	return (pindex);
}