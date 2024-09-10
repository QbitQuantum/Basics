/*
 * Process a received prefix option.
 * Unless addrconf is turned off we process both the addrconf and the
 * onlink aspects of the prefix option.
 *
 * Note that when a flag (onlink or auto) is turned off we do nothing -
 * the prefix will time out.
 */
static void
incoming_prefix_opt(struct phyint *pi, uchar_t *opt,
    struct sockaddr_in6 *from, boolean_t loopback)
{
	struct nd_opt_prefix_info *po = (struct nd_opt_prefix_info *)opt;
	boolean_t	good_prefix = _B_TRUE;

	if (8 * po->nd_opt_pi_len != sizeof (*po)) {
		char abuf[INET6_ADDRSTRLEN];

		(void) inet_ntop(AF_INET6, (void *)&from->sin6_addr,
		    abuf, sizeof (abuf));
		logmsg(LOG_INFO, "prefix option from %s on %s wrong size "
		    "(%d bytes)\n",
		    abuf, pi->pi_name,
		    8 * (int)po->nd_opt_pi_len);
		return;
	}
	if (IN6_IS_ADDR_LINKLOCAL(&po->nd_opt_pi_prefix)) {
		char abuf[INET6_ADDRSTRLEN];

		(void) inet_ntop(AF_INET6, (void *)&from->sin6_addr,
		    abuf, sizeof (abuf));
		logmsg(LOG_INFO, "RA from %s on %s contains link-local prefix "
		    "- ignored\n",
		    abuf, pi->pi_name);
		return;
	}
	if ((po->nd_opt_pi_flags_reserved & ND_OPT_PI_FLAG_AUTO) &&
	    pi->pi_stateless && pi->pi_autoconf) {
		good_prefix = incoming_prefix_addrconf(pi, opt, from, loopback);
	}
	if ((po->nd_opt_pi_flags_reserved & ND_OPT_PI_FLAG_ONLINK) &&
	    good_prefix) {
		incoming_prefix_onlink(pi, opt);
	}
	if (pi->pi_stateful && pi->pi_autoconf)
		incoming_prefix_stateful(pi, opt);
}