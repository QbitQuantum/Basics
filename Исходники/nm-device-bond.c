static NMActStageReturn
apply_bonding_config (NMDevice *device)
{
	NMConnection *connection;
	NMSettingBond *s_bond;
	int ifindex = nm_device_get_ifindex (device);
	const char *mode, *value;
	char *contents;
	gboolean set_arp_interval = TRUE;

	/* Option restrictions:
	 *
	 * arp_interval conflicts miimon > 0
	 * arp_interval conflicts [ alb, tlb ]
	 * arp_validate needs [ active-backup ]
	 * downdelay needs miimon
	 * updelay needs miimon
	 * primary needs [ active-backup, tlb, alb ]
	 *
	 * clearing miimon requires that arp_interval be 0, but clearing
	 *     arp_interval doesn't require miimon to be 0
	 */

	connection = nm_device_get_connection (device);
	g_assert (connection);
	s_bond = nm_connection_get_setting_bond (connection);
	g_assert (s_bond);

	mode = nm_setting_bond_get_option_by_name (s_bond, NM_SETTING_BOND_OPTION_MODE);
	if (mode == NULL)
		mode = "balance-rr";

	value = nm_setting_bond_get_option_by_name (s_bond, NM_SETTING_BOND_OPTION_MIIMON);
	if (value && atoi (value)) {
		/* clear arp interval */
		set_bond_attr (device, "arp_interval", "0");
		set_arp_interval = FALSE;

		set_bond_attr (device, "miimon", value);
		set_simple_option (device, "updelay", s_bond, NM_SETTING_BOND_OPTION_UPDELAY);
		set_simple_option (device, "downdelay", s_bond, NM_SETTING_BOND_OPTION_DOWNDELAY);
	} else if (!value) {
		/* If not given, and arp_interval is not given, default to 100 */
		long int val_int;
		char *end;

		value = nm_setting_bond_get_option_by_name (s_bond, NM_SETTING_BOND_OPTION_ARP_INTERVAL);
		errno = 0;
		val_int = strtol (value ? value : "0", &end, 10);
		if (!value || (val_int == 0 && errno == 0 && *end == '\0'))
			set_bond_attr (device, "miimon", "100");
	}

	/* The stuff after 'mode' requires the given mode or doesn't care */
	set_bond_attr (device, "mode", mode);

	/* arp_interval not compatible with ALB, TLB */
	if (g_strcmp0 (mode, "balance-alb") == 0 || g_strcmp0 (mode, "balance-tlb") == 0)
		set_arp_interval = FALSE;

	if (set_arp_interval) {
		set_simple_option (device, "arp_interval", s_bond, NM_SETTING_BOND_OPTION_ARP_INTERVAL);

		/* Just let miimon get cleared automatically; even setting miimon to
		 * 0 (disabled) clears arp_interval.
		 */
	}

	value = nm_setting_bond_get_option_by_name (s_bond, NM_SETTING_BOND_OPTION_ARP_VALIDATE);
	/* arp_validate > 0 only valid in active-backup mode */
	if (   value
	    && g_strcmp0 (value, "0") != 0
	    && g_strcmp0 (value, "none") != 0
	    && g_strcmp0 (mode, "active-backup") == 0)
		set_bond_attr (device, "arp_validate", value);
	else
		set_bond_attr (device, "arp_validate", "0");

	if (   g_strcmp0 (mode, "active-backup") == 0
	    || g_strcmp0 (mode, "balance-alb") == 0
	    || g_strcmp0 (mode, "balance-tlb") == 0) {
		value = nm_setting_bond_get_option_by_name (s_bond, NM_SETTING_BOND_OPTION_PRIMARY);
		set_bond_attr (device, "primary", value ? value : "");
	}

	/* Clear ARP targets */
	contents = nm_platform_master_get_option (ifindex, "arp_ip_target");
	set_arp_targets (device, contents, " \n", "-");
	g_free (contents);

	/* Add new ARP targets */
	value = nm_setting_bond_get_option_by_name (s_bond, NM_SETTING_BOND_OPTION_ARP_IP_TARGET);
	set_arp_targets (device, value, ",", "+");

	set_simple_option (device, "primary_reselect", s_bond, NM_SETTING_BOND_OPTION_PRIMARY_RESELECT);
	set_simple_option (device, "fail_over_mac", s_bond, NM_SETTING_BOND_OPTION_FAIL_OVER_MAC);
	set_simple_option (device, "use_carrier", s_bond, NM_SETTING_BOND_OPTION_USE_CARRIER);
	set_simple_option (device, "ad_select", s_bond, NM_SETTING_BOND_OPTION_AD_SELECT);
	set_simple_option (device, "xmit_hash_policy", s_bond, NM_SETTING_BOND_OPTION_XMIT_HASH_POLICY);
	set_simple_option (device, "resend_igmp", s_bond, NM_SETTING_BOND_OPTION_RESEND_IGMP);

	if (   g_strcmp0 (mode, "4") == 0
	    || g_strcmp0 (mode, "802.3ad") == 0)
		set_simple_option (device, "lacp_rate", s_bond, NM_SETTING_BOND_OPTION_LACP_RATE);

	return NM_ACT_STAGE_RETURN_SUCCESS;
}