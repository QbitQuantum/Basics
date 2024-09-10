void print_proto(uint16_t proto, int invert)
{
	const struct protoent *pent = getprotobynumber(proto);

	if (invert)
		printf("! ");

	if (pent) {
		printf("-p %s ", pent->p_name);
		return;
	}

	printf("-p %u ", proto);
}