int gtmsource_get_opt(void)
{
	char		*connect_parm_token_str, *connect_parm;
	char		*connect_parms_str, tmp_connect_parms_str[GTMSOURCE_CONN_PARMS_LEN + 1];
	char		secondary_sys[MAX_SECONDARY_LEN], *c, inst_name[MAX_FN_LEN + 1];
	char		statslog_val[SIZEOF("OFF")]; /* "ON" or "OFF" */
	char		update_val[SIZEOF("DISABLE")]; /* "ENABLE" or "DISABLE" */
	char		freeze_val[SIZEOF("OFF")]; /* "ON" or "OFF" */
	char		freeze_comment[SIZEOF(gtmsource_options.freeze_comment)];
	int		tries, index = 0, timeout_status, connect_parms_index, status, renegotiate_interval;
	struct hostent	*sec_hostentry;
	unsigned short	log_file_len, filter_cmd_len;
	unsigned short	secondary_len, inst_name_len, statslog_val_len, update_val_len, connect_parms_str_len;
	unsigned short	freeze_val_len, freeze_comment_len, tlsid_len;
	int		errcode;
	int		port_len;
	char		*ip_end;
	mstr		log_nam, trans_name;
	boolean_t	secondary, dotted_notation, log, log_interval_specified, connect_parms_badval, plaintext_fallback;

	memset((char *)&gtmsource_options, 0, SIZEOF(gtmsource_options));
	gtmsource_options.start = (CLI_PRESENT == cli_present("START"));
	gtmsource_options.shut_down = (CLI_PRESENT == cli_present("SHUTDOWN"));
	gtmsource_options.activate = (CLI_PRESENT == cli_present("ACTIVATE"));
	gtmsource_options.deactivate = (CLI_PRESENT == cli_present("DEACTIVATE"));
	gtmsource_options.checkhealth = (CLI_PRESENT == cli_present("CHECKHEALTH"));
	gtmsource_options.statslog = (CLI_PRESENT == cli_present("STATSLOG"));
	gtmsource_options.showbacklog = (CLI_PRESENT == cli_present("SHOWBACKLOG"));
	gtmsource_options.changelog = (CLI_PRESENT == cli_present("CHANGELOG"));
	gtmsource_options.stopsourcefilter = (CLI_PRESENT == cli_present("STOPSOURCEFILTER"));
	gtmsource_options.needrestart = (CLI_PRESENT == cli_present("NEEDRESTART"));
	gtmsource_options.losttncomplete = (CLI_PRESENT == cli_present("LOSTTNCOMPLETE"));
	gtmsource_options.jnlpool = (CLI_PRESENT == cli_present("JNLPOOL"));
	secondary = (CLI_PRESENT == cli_present("SECONDARY"));
	gtmsource_options.rootprimary = ROOTPRIMARY_UNSPECIFIED; /* to indicate unspecified state */
	if ((CLI_PRESENT == cli_present("ROOTPRIMARY")) || (CLI_PRESENT == cli_present("UPDOK")))
		gtmsource_options.rootprimary = ROOTPRIMARY_SPECIFIED;
	else if ((CLI_PRESENT == cli_present("PROPAGATEPRIMARY")) || (CLI_PRESENT == cli_present("UPDNOTOK")))
		gtmsource_options.rootprimary = PROPAGATEPRIMARY_SPECIFIED;
	else
	{	/* Neither ROOTPRIMARY (or UPDOK) nor PROPAGATEPRIMARY (or UPDNOTOK) specified. Assume default values.
		 * Assume ROOTPRIMARY for -START -SECONDARY (active source server start) and -ACTIVATE commands.
		 * Assume PROPAGATEPRIMARY for -START -PASSIVE (passive source server start) and -DEACTIVATE commands.
		 */
		if ((gtmsource_options.start && secondary) || gtmsource_options.activate)
			gtmsource_options.rootprimary = ROOTPRIMARY_SPECIFIED;
		if ((gtmsource_options.start && !secondary) || gtmsource_options.deactivate)
			gtmsource_options.rootprimary = PROPAGATEPRIMARY_SPECIFIED;
	}
	gtmsource_options.instsecondary = (CLI_PRESENT == cli_present("INSTSECONDARY"));
	if (gtmsource_options.instsecondary)
	{	/* -INSTSECONDARY is specified in the command line. */
		inst_name_len = SIZEOF(inst_name);;
		if (!cli_get_str("INSTSECONDARY", &inst_name[0], &inst_name_len))
		{
			util_out_print("Error parsing INSTSECONDARY qualifier", TRUE);
			return(-1);
		}
	} else
	{	/* Check if environment variable "gtm_repl_instsecondary" is defined.
		 * Do that only if any of the following qualifiers is present as these are the only ones that honour it.
		 * 	Mandatory : START, ACTIVATE, DEACTIVATE, STOPSOURCEFILTER, CHANGELOG, STATSLOG, NEEDRESTART,
		 *	Optional  : CHECKHEALTH, SHOWBACKLOG or SHUTDOWN
		 */
		if (gtmsource_options.start || gtmsource_options.activate || gtmsource_options.deactivate
			|| gtmsource_options.stopsourcefilter || gtmsource_options.changelog
			|| gtmsource_options.statslog || gtmsource_options.needrestart
			|| gtmsource_options.checkhealth || gtmsource_options.showbacklog || gtmsource_options.shut_down)
		{
			log_nam.addr = GTM_REPL_INSTSECONDARY;
			log_nam.len = SIZEOF(GTM_REPL_INSTSECONDARY) - 1;
			trans_name.addr = &inst_name[0];
			if (SS_NORMAL == (status = TRANS_LOG_NAME(&log_nam, &trans_name, inst_name, SIZEOF(inst_name),
									do_sendmsg_on_log2long)))
			{
				gtmsource_options.instsecondary = TRUE;
				inst_name_len = trans_name.len;
			} else if (!gtmsource_options.checkhealth && !gtmsource_options.showbacklog && !gtmsource_options.shut_down)
			{
				if (SS_LOG2LONG == status)
					gtm_putmsg_csa(CSA_ARG(NULL) VARLSTCNT(5) ERR_LOGTOOLONG, 3, log_nam.len, log_nam.addr,
						SIZEOF(inst_name) - 1);
				gtm_putmsg_csa(CSA_ARG(NULL) VARLSTCNT(1) ERR_REPLINSTSECUNDF);
				return (-1);
			}
		}
	}
	if (gtmsource_options.instsecondary)
	{	/* Secondary instance name specified either through -INSTSECONDARY or "gtm_repl_instsecondary" */
		inst_name[inst_name_len] = '\0';
		if ((MAX_INSTNAME_LEN <= inst_name_len) || (0 == inst_name_len))
		{
			gtm_putmsg_csa(CSA_ARG(NULL) VARLSTCNT(4) ERR_REPLINSTSECLEN, 2, inst_name_len, inst_name);
			return (-1);
		}
		assert((inst_name_len + 1) <= MAX_INSTNAME_LEN);
		memcpy(gtmsource_options.secondary_instname, inst_name, inst_name_len + 1);	/* copy terminating '\0' as well */
	}
	if (gtmsource_options.start || gtmsource_options.activate)
	{
		if (secondary)
		{
			secondary_len = MAX_SECONDARY_LEN;
			if (!cli_get_str("SECONDARY", secondary_sys, &secondary_len))
			{
				util_out_print("Error parsing SECONDARY qualifier", TRUE);
				return(-1);
			}
			/* Parse secondary_sys into secondary_host
			 * and secondary_port */
			c = secondary_sys;
			dotted_notation = TRUE;
			if ('[' == *c)
			{
				ip_end = strchr(++c, ']');
				if (NULL == ip_end || 0 == (index = ip_end - c))
				{
					util_out_print("Invalid IP address !AD", TRUE,
						LEN_AND_STR(secondary_sys));
					return(-1);
				}
				memcpy(gtmsource_options.secondary_host, c, index);
				gtmsource_options.secondary_host[index] = '\0';
				c = ip_end + 1;
			} else
			{
				while(*c && (':' != *c))
					gtmsource_options.secondary_host[index++] = *c++;
				gtmsource_options.secondary_host[index] = '\0';
			}
			if (':' != *c)
			{
				util_out_print("Secondary port number should be specified", TRUE);
				return(-1);
			}
			port_len = strlen(++c);
			errno = 0;
			if (((0 == (gtmsource_options.secondary_port = ATOI(c))) && (0 != errno))
				|| (0 >= gtmsource_options.secondary_port))
			{
				util_out_print("Error parsing secondary port number !AD", TRUE, LEN_AND_STR(c));
				return(-1);
			}
		}
		if (CLI_PRESENT == cli_present("CONNECTPARAMS"))
		{
			connect_parms_str_len = GTMSOURCE_CONN_PARMS_LEN + 1;
			if (!cli_get_str("CONNECTPARAMS", tmp_connect_parms_str, &connect_parms_str_len))
			{
				util_out_print("Error parsing CONNECTPARAMS qualifier", TRUE);
				return(-1);
			}
#ifdef VMS
			/* strip the quotes around the string. (DCL doesn't do it) */
			assert('"' == tmp_connect_parms_str[0]);
			assert('"' == tmp_connect_parms_str[connect_parms_str_len - 1]);
			connect_parms_str = &tmp_connect_parms_str[1];
			tmp_connect_parms_str[connect_parms_str_len - 1] = '\0';
#else
			connect_parms_str = &tmp_connect_parms_str[0];
#endif
			for (connect_parms_index =
					GTMSOURCE_CONN_HARD_TRIES_COUNT,
			     connect_parms_badval = FALSE,
			     connect_parm_token_str = connect_parms_str;
			     !connect_parms_badval &&
			     connect_parms_index < GTMSOURCE_CONN_PARMS_COUNT &&
			     (connect_parm = strtok(connect_parm_token_str,
						    GTMSOURCE_CONN_PARMS_DELIM))
			     		   != NULL;
			     connect_parms_index++,
			     connect_parm_token_str = NULL)

			{
				errno = 0;
				if ((0 == (gtmsource_options.connect_parms[connect_parms_index] = ATOI(connect_parm))
						&& 0 != errno) || 0 >= gtmsource_options.connect_parms[connect_parms_index])
					connect_parms_badval = TRUE;
			}
			if (connect_parms_badval)
			{
				util_out_print("Error parsing or invalid value parameter in CONNECTPARAMS", TRUE);
				return(-1);
			}
			if (GTMSOURCE_CONN_PARMS_COUNT != connect_parms_index)
			{
				util_out_print(
					"All CONNECTPARAMS - HARD TRIES, HARD TRIES PERIOD, "
					"SOFT TRIES PERIOD, "
					"ALERT TIME, HEARTBEAT INTERVAL, "
					"MAX HEARBEAT WAIT should be specified", TRUE);
				return(-1);
			}
		} else
		{
			gtmsource_options.connect_parms[GTMSOURCE_CONN_HARD_TRIES_COUNT] = REPL_CONN_HARD_TRIES_COUNT;
			gtmsource_options.connect_parms[GTMSOURCE_CONN_HARD_TRIES_PERIOD] = REPL_CONN_HARD_TRIES_PERIOD;
			gtmsource_options.connect_parms[GTMSOURCE_CONN_SOFT_TRIES_PERIOD] = REPL_CONN_SOFT_TRIES_PERIOD;
			gtmsource_options.connect_parms[GTMSOURCE_CONN_ALERT_PERIOD] = REPL_CONN_ALERT_ALERT_PERIOD;
			gtmsource_options.connect_parms[GTMSOURCE_CONN_HEARTBEAT_PERIOD] = REPL_CONN_HEARTBEAT_PERIOD;
			gtmsource_options.connect_parms[GTMSOURCE_CONN_HEARTBEAT_MAX_WAIT] = REPL_CONN_HEARTBEAT_MAX_WAIT;
		}
		if (gtmsource_options.connect_parms[GTMSOURCE_CONN_ALERT_PERIOD]<
				gtmsource_options.connect_parms[GTMSOURCE_CONN_SOFT_TRIES_PERIOD])
			gtmsource_options.connect_parms[GTMSOURCE_CONN_ALERT_PERIOD] =
				gtmsource_options.connect_parms[GTMSOURCE_CONN_SOFT_TRIES_PERIOD];
		if (gtmsource_options.connect_parms[GTMSOURCE_CONN_HEARTBEAT_MAX_WAIT] <
				gtmsource_options.connect_parms[GTMSOURCE_CONN_HEARTBEAT_PERIOD])
			gtmsource_options.connect_parms[GTMSOURCE_CONN_HEARTBEAT_MAX_WAIT] =
				gtmsource_options.connect_parms[GTMSOURCE_CONN_HEARTBEAT_PERIOD];
	}
	if (gtmsource_options.start || gtmsource_options.statslog || gtmsource_options.changelog || gtmsource_options.activate)
	{
		log = (cli_present("LOG") == CLI_PRESENT);
		log_interval_specified = (CLI_PRESENT == cli_present("LOG_INTERVAL"));
		if (log)
		{
			log_file_len = MAX_FN_LEN + 1;
			if (!cli_get_str("LOG", gtmsource_options.log_file, &log_file_len))
			{
				util_out_print("Error parsing LOG qualifier", TRUE);
				return(-1);
			}
		} else
			gtmsource_options.log_file[0] = '\0';
		gtmsource_options.src_log_interval = 0;
		if (log_interval_specified)
		{
			if (!cli_get_num("LOG_INTERVAL", (int4 *)&gtmsource_options.src_log_interval))
			{
				util_out_print("Error parsing LOG_INTERVAL qualifier", TRUE);
				return (-1);
			}
		}
		if (gtmsource_options.start && 0 == gtmsource_options.src_log_interval)
			gtmsource_options.src_log_interval = LOGTRNUM_INTERVAL;
		/* For changelog/activate, interval == 0 implies don't change log interval already established */
		/* We ignore interval specification for statslog, Vinaya 2005/02/07 */
	}
	if (gtmsource_options.start)
	{
		assert(secondary || CLI_PRESENT == cli_present("PASSIVE"));
		gtmsource_options.mode = ((secondary) ? GTMSOURCE_MODE_ACTIVE : GTMSOURCE_MODE_PASSIVE);
		if (CLI_PRESENT == cli_present("BUFFSIZE"))
		{
			if (!cli_get_int("BUFFSIZE", &gtmsource_options.buffsize))
			{
				util_out_print("Error parsing BUFFSIZE qualifier", TRUE);
				return(-1);
			}
			if (MIN_JNLPOOL_SIZE > gtmsource_options.buffsize)
				gtmsource_options.buffsize = MIN_JNLPOOL_SIZE;
		} else
			gtmsource_options.buffsize = DEFAULT_JNLPOOL_SIZE;
		/* Round up buffsize to the nearest (~JNL_WRT_END_MASK + 1) multiple */
		gtmsource_options.buffsize = ((gtmsource_options.buffsize + ~JNL_WRT_END_MASK) & JNL_WRT_END_MASK);
		if (CLI_PRESENT == cli_present("FILTER"))
		{
			filter_cmd_len = MAX_FILTER_CMD_LEN;
	    		if (!cli_get_str("FILTER", gtmsource_options.filter_cmd, &filter_cmd_len))
			{
				util_out_print("Error parsing FILTER qualifier", TRUE);
				return(-1);
			}
		} else
			gtmsource_options.filter_cmd[0] = '\0';
		/* Check if compression level is specified */
		if (CLI_PRESENT == cli_present("CMPLVL"))
		{
			if (!cli_get_int("CMPLVL", &gtmsource_options.cmplvl))
			{
				util_out_print("Error parsing CMPLVL qualifier", TRUE);
				return(-1);
			}
			if (GTM_CMPLVL_OUT_OF_RANGE(gtmsource_options.cmplvl))
				gtmsource_options.cmplvl = ZLIB_CMPLVL_MIN;	/* no compression in this case */
			/* CMPLVL qualifier should override any value specified in the environment variable gtm_zlib_cmp_level */
			gtm_zlib_cmp_level = gtmsource_options.cmplvl;
		} else
			gtmsource_options.cmplvl = ZLIB_CMPLVL_MIN;	/* no compression in this case */
		/* Check if SSL/TLS secure communication is requested. */
#		ifdef GTM_TLS
		if (CLI_PRESENT == cli_present("TLSID"))
		{
			tlsid_len = MAX_TLSID_LEN;
			if (!cli_get_str("TLSID", repl_tls.id, &tlsid_len))
			{
				util_out_print("Error parsing TLSID qualifier", TRUE);
				return -1;
			}
			assert(0 < tlsid_len);
			if (CLI_PRESENT == cli_present("RENEGOTIATE_INTERVAL"))
			{
				if (!cli_get_int("RENEGOTIATE_INTERVAL", &renegotiate_interval))
				{
					util_out_print("Error parsing RENEGOTIATE_INTERVAL qualifier", TRUE);
					return -1;
				}
				if (0 > renegotiate_interval)
				{
					util_out_print("Negative values are not allowed for RENEGOTIATE_INTERVAL qualifier", TRUE);
					return -1;
				} else if ((0 < renegotiate_interval) && (renegotiate_interval < MIN_RENEGOTIATE_TIMEOUT))
					renegotiate_interval = MIN_RENEGOTIATE_TIMEOUT;
				renegotiate_interval = renegotiate_interval * 60;	   /* Convert to seconds. */
			} else
				renegotiate_interval = DEFAULT_RENEGOTIATE_TIMEOUT * 60; /* Convert to seconds. */
			/* Convert renegotiate_interval to heartbeat units (# of 8 second intervals). */
			renegotiate_interval = DIVIDE_ROUND_UP(renegotiate_interval, HEARTBEAT_INTERVAL_IN_SECS);
			gtmsource_options.renegotiate_interval = renegotiate_interval;
			/* Check if plaintext-fallback mode is specified. Default option is NOPLAINTEXTFALLBACK. */
			if (CLI_PRESENT == (plaintext_fallback = cli_present("PLAINTEXTFALLBACK")))
				repl_tls.plaintext_fallback = (plaintext_fallback != CLI_NEGATED);
			else
				repl_tls.plaintext_fallback = FALSE;
			}
#		endif
	}
	if (gtmsource_options.shut_down)
	{
		if ((timeout_status = cli_present("TIMEOUT")) == CLI_PRESENT)
		{
			if (!cli_get_int("TIMEOUT", &gtmsource_options.shutdown_time))
			{
				util_out_print("Error parsing TIMEOUT qualifier", TRUE);
				return(-1);
			}
			if (DEFAULT_SHUTDOWN_TIMEOUT < gtmsource_options.shutdown_time || 0 > gtmsource_options.shutdown_time)
			{
				gtmsource_options.shutdown_time = DEFAULT_SHUTDOWN_TIMEOUT;
				util_out_print("shutdown TIMEOUT changed to !UL", TRUE, gtmsource_options.shutdown_time);
			}
		} else if (CLI_NEGATED == timeout_status)
			gtmsource_options.shutdown_time = -1;
		else /* TIMEOUT not specified */
			gtmsource_options.shutdown_time = DEFAULT_SHUTDOWN_TIMEOUT;
	}
	if (gtmsource_options.statslog)
	{
		statslog_val_len = 4; /* max(strlen("ON"), strlen("OFF")) + 1 */
		if (!cli_get_str("STATSLOG", statslog_val, &statslog_val_len))
		{
			util_out_print("Error parsing STATSLOG qualifier", TRUE);
			return(-1);
		}
		UNIX_ONLY(cli_strupper(statslog_val);)
		if (0 == STRCMP(statslog_val, "ON"))