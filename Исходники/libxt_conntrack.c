static int
conntrack_mt_parse(int c, char **argv, int invert, unsigned int *flags,
                   struct xt_entry_match **match)
{
	struct xt_conntrack_mtinfo1 *info = (void *)(*match)->data;
	unsigned int port;
	char *p;

	switch (c) {
	case '1': /* --ctstate */
		conntrack_ps_states(info, optarg);
		info->match_flags |= XT_CONNTRACK_STATE;
		if (invert)
			info->invert_flags |= XT_CONNTRACK_STATE;
		break;

	case '2': /* --ctproto */
		/* Canonicalize into lower case */
		for (p = optarg; *p != '\0'; ++p)
			*p = tolower(*p);
		info->l4proto = xtables_parse_protocol(optarg);

		if (info->l4proto == 0 && (info->invert_flags & XT_INV_PROTO))
			xtables_error(PARAMETER_PROBLEM, "conntrack: rule would "
			           "never match protocol");

		info->match_flags |= XT_CONNTRACK_PROTO;
		if (invert)
			info->invert_flags |= XT_CONNTRACK_PROTO;
		break;

	case '7': /* --ctstatus */
		conntrack_ps_statuses(info, optarg);
		info->match_flags |= XT_CONNTRACK_STATUS;
		if (invert)
			info->invert_flags |= XT_CONNTRACK_STATUS;
		break;

	case '8': /* --ctexpire */
		conntrack_ps_expires(info, optarg);
		info->match_flags |= XT_CONNTRACK_EXPIRES;
		if (invert)
			info->invert_flags |= XT_CONNTRACK_EXPIRES;
		break;

	case 'a': /* --ctorigsrcport */
		if (!xtables_strtoui(optarg, NULL, &port, 0, UINT16_MAX))
			xtables_param_act(XTF_BAD_VALUE, "conntrack",
			          "--ctorigsrcport", optarg);
		info->match_flags |= XT_CONNTRACK_ORIGSRC_PORT;
		info->origsrc_port = htons(port);
		if (invert)
			info->invert_flags |= XT_CONNTRACK_ORIGSRC_PORT;
		break;

	case 'b': /* --ctorigdstport */
		if (!xtables_strtoui(optarg, NULL, &port, 0, UINT16_MAX))
			xtables_param_act(XTF_BAD_VALUE, "conntrack",
			          "--ctorigdstport", optarg);
		info->match_flags |= XT_CONNTRACK_ORIGDST_PORT;
		info->origdst_port = htons(port);
		if (invert)
			info->invert_flags |= XT_CONNTRACK_ORIGDST_PORT;
		break;

	case 'c': /* --ctreplsrcport */
		if (!xtables_strtoui(optarg, NULL, &port, 0, UINT16_MAX))
			xtables_param_act(XTF_BAD_VALUE, "conntrack",
			          "--ctreplsrcport", optarg);
		info->match_flags |= XT_CONNTRACK_REPLSRC_PORT;
		info->replsrc_port = htons(port);
		if (invert)
			info->invert_flags |= XT_CONNTRACK_REPLSRC_PORT;
		break;

	case 'd': /* --ctrepldstport */
		if (!xtables_strtoui(optarg, NULL, &port, 0, UINT16_MAX))
			xtables_param_act(XTF_BAD_VALUE, "conntrack",
			          "--ctrepldstport", optarg);
		info->match_flags |= XT_CONNTRACK_REPLDST_PORT;
		info->repldst_port = htons(port);
		if (invert)
			info->invert_flags |= XT_CONNTRACK_REPLDST_PORT;
		break;

	case 'e': /* --ctdir */
		xtables_param_act(XTF_NO_INVERT, "conntrack", "--ctdir", invert);
		if (strcasecmp(optarg, "ORIGINAL") == 0) {
			info->match_flags  |= XT_CONNTRACK_DIRECTION;
			info->invert_flags &= ~XT_CONNTRACK_DIRECTION;
		} else if (strcasecmp(optarg, "REPLY") == 0) {
			info->match_flags  |= XT_CONNTRACK_DIRECTION;
			info->invert_flags |= XT_CONNTRACK_DIRECTION;
		} else {
			xtables_param_act(XTF_BAD_VALUE, "conntrack", "--ctdir", optarg);
		}
		break;

	default:
		return false;
	}

	*flags = info->match_flags;
	return true;
}