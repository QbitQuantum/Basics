void
init_netsukuku(char **argv)
{
	xsrand();

	if (geteuid())
		fatal("Need root privileges");

	destroy_netsukuku_mutex = pid_saved = 0;
	sigterm_timestamp = sighup_timestamp = sigalrm_timestamp = 0;
	setzero(&me, sizeof(struct current_globals));

	if (is_ntkd_already_running())
		fatal("ntkd is already running. If it is not, remove \"%s\"",
			  server_opt.pid_file);
	else
		save_pid();

	my_family = server_opt.family;
	restricted_mode = server_opt.restricted;
	restricted_class =
		server_opt.restricted_class ? RESTRICTED_172 : RESTRICTED_10;

	/* Check if the DATA_DIR exists, if not create it */
	if (check_and_create_dir(DATA_DIR))
		fatal("Cannot access to the %s directory. Exiting.", DATA_DIR);

	/*
	 * Device initialization
	 */
	if (if_init_all(server_opt.ifs, server_opt.ifs_n,
					me.cur_ifs, &me.cur_ifs_n) < 0)
		fatal("Cannot initialize any network interfaces");

	/*
	 * ANDNA init
	 */
	if (!server_opt.disable_andna)
		andna_init();

	/*
	 * Initialize the Internet gateway stuff
	 */
	if (server_opt.my_upload_bw && server_opt.my_dnload_bw)
		me.my_bandwidth = bandwidth_in_8bit((server_opt.my_upload_bw +
											 server_opt.my_dnload_bw) / 2);
	init_internet_gateway_search();

	pkts_init(me.cur_ifs, me.cur_ifs_n, 0);
	qspn_init(FAMILY_LVLS);

	me.cur_erc = e_rnode_init(&me.cur_erc_counter);

	/* Radar init */
	rq_wait_idx_init(rq_wait_idx);
	first_init_radar();
	total_radars = 0;

	ntk_load_maps();

#if 0
	/* TODO: activate and test it !! */
	debug(DBG_NORMAL, "ACPT: Initializing the accept_tbl: \n"
		  "	max_connections: %d,\n"
		  "	max_accepts_per_host: %d,\n"
		  "	max_accept_per_host_time: %d",
		  server_opt.max_connections,
		  server_opt.max_accepts_per_host,
		  server_opt.max_accepts_per_host_time);
	init_accept_tbl(server_opt.max_connections,
					server_opt.max_accepts_per_host,
					server_opt.max_accepts_per_host_time);
#endif

	if (restricted_mode)
		loginfo("NetsukukuD is in restricted mode. "
				"Restricted class: %s",
				server_opt.
				restricted_class ? RESTRICTED_172_STR : RESTRICTED_10_STR);

	hook_init();
	rehook_init();

	me.uptime = time(0);
}