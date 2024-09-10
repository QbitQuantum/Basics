int starter_cmp_pluto (struct starter_config *c1, struct starter_config *c2)
{
	if ((!c1) || (!c2)) return -1;
	VARCMP(setup.options[KBF_PLUTODEBUG]);
	VARCMP(setup.options[KBF_UNIQUEIDS]);
	VARCMP(setup.options[KBF_RETRANSMITS]);
	VARCMP(setup.options[KBF_STRICTCRLPOLICY]);
	VARCMP(setup.options[KBF_FORCEBUSY]);
	VARCMP(setup.options[KBF_NHELPERS]);
	VARCMP(setup.options[KBF_PERPEERLOG]);
	VARCMP(setup.options[KBF_PLUTOFORK]);
	STRCMP(setup.strings[KSF_LISTEN]);
	STRCMP(setup.strings[KSF_PERPEERDIR]);
#ifdef NAT_TRAVERSAL
	VARCMP(setup.options[KBF_NATTRAVERSAL]);
	VARCMP(setup.options[KBF_DISABLEPORTFLOATING]);
	VARCMP(setup.options[KBF_FORCE_KEEPALIVE]);
	VARCMP(setup.options[KBF_KEEPALIVE]);
	STRCMP(setup.strings[KSF_VIRTUALPRIVATE]);
#endif
	return 0;
}