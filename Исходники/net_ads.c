static int net_ads_printer_publish(int argc, const char **argv)
{
        ADS_STRUCT *ads;
        ADS_STATUS rc;
	const char *servername, *printername;
	struct cli_state *cli;
	struct in_addr 		server_ip;
	NTSTATUS nt_status;
	TALLOC_CTX *mem_ctx = talloc_init("net_ads_printer_publish");
	ADS_MODLIST mods = ads_init_mods(mem_ctx);
	char *prt_dn, *srv_dn, **srv_cn;
	void *res = NULL;

	if (!(ads = ads_startup())) {
		return -1;
	}

	if (argc < 1) {
		return net_ads_printer_usage(argc, argv);
	}
	
	printername = argv[0];

	if (argc == 2) {
		servername = argv[1];
	} else {
		servername = global_myname();
	}
		
	/* Get printer data from SPOOLSS */

	resolve_name(servername, &server_ip, 0x20);

	nt_status = cli_full_connection(&cli, global_myname(), servername, 
					&server_ip, 0,
					"IPC$", "IPC",  
					opt_user_name, opt_workgroup,
					opt_password ? opt_password : "", 
					CLI_FULL_CONNECTION_USE_KERBEROS, 
					Undefined, NULL);

	if (NT_STATUS_IS_ERR(nt_status)) {
		d_printf("Unable to open a connnection to %s to obtain data "
			 "for %s\n", servername, printername);
		ads_destroy(&ads);
		return -1;
	}

	/* Publish on AD server */

	ads_find_machine_acct(ads, &res, servername);

	if (ads_count_replies(ads, res) == 0) {
		d_printf("Could not find machine account for server %s\n", 
			 servername);
		ads_destroy(&ads);
		return -1;
	}

	srv_dn = ldap_get_dn(ads->ld, res);
	srv_cn = ldap_explode_dn(srv_dn, 1);

	asprintf(&prt_dn, "cn=%s-%s,%s", srv_cn[0], printername, srv_dn);

	cli_nt_session_open(cli, PI_SPOOLSS);
	get_remote_printer_publishing_data(cli, mem_ctx, &mods, printername);

        rc = ads_add_printer_entry(ads, prt_dn, mem_ctx, &mods);
        if (!ADS_ERR_OK(rc)) {
                d_printf("ads_publish_printer: %s\n", ads_errstr(rc));
		ads_destroy(&ads);
                return -1;
        }
 
        d_printf("published printer\n");
	ads_destroy(&ads);
 
	return 0;
}