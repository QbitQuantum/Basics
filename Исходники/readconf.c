int
process_config_line(Options *options, const char *host,
		    char *line, const char *filename, int linenum,
		    int *activep)
{
	char *s, **charptr, *endofnumber, *keyword, *arg, *arg2;
	char **cpptr, fwdarg[256];
	u_int *uintptr, max_entries = 0;
	int negated, opcode, *intptr, value, value2, scale;
	LogLevel *log_level_ptr;
	long long orig, val64;
	size_t len;
	Forward fwd;

	/* Strip trailing whitespace */
	for (len = strlen(line) - 1; len > 0; len--) {
		if (strchr(WHITESPACE, line[len]) == NULL)
			break;
		line[len] = '\0';
	}

	s = line;
	/* Get the keyword. (Each line is supposed to begin with a keyword). */
	if ((keyword = strdelim(&s)) == NULL)
		return 0;
	/* Ignore leading whitespace. */
	if (*keyword == '\0')
		keyword = strdelim(&s);
	if (keyword == NULL || !*keyword || *keyword == '\n' || *keyword == '#')
		return 0;

	opcode = parse_token(keyword, filename, linenum);

	switch (opcode) {
	case oBadOption:
		/* don't panic, but count bad options */
		return -1;
		/* NOTREACHED */
	case oConnectTimeout:
		intptr = &options->connection_timeout;
parse_time:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%s line %d: missing time value.",
			    filename, linenum);
		if ((value = convtime(arg)) == -1)
			fatal("%s line %d: invalid time value.",
			    filename, linenum);
		if (*activep && *intptr == -1)
			*intptr = value;
		break;

	case oForwardAgent:
		intptr = &options->forward_agent;
parse_flag:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing yes/no argument.", filename, linenum);
		value = 0;	/* To avoid compiler warning... */
		if (strcmp(arg, "yes") == 0 || strcmp(arg, "true") == 0)
			value = 1;
		else if (strcmp(arg, "no") == 0 || strcmp(arg, "false") == 0)
			value = 0;
		else
			fatal("%.200s line %d: Bad yes/no argument.", filename, linenum);
		if (*activep && *intptr == -1)
			*intptr = value;
		break;

	case oForwardX11:
		intptr = &options->forward_x11;
		goto parse_flag;

	case oForwardX11Trusted:
		intptr = &options->forward_x11_trusted;
		goto parse_flag;
	
	case oForwardX11Timeout:
		intptr = &options->forward_x11_timeout;
		goto parse_time;

	case oGatewayPorts:
		intptr = &options->gateway_ports;
		goto parse_flag;

	case oExitOnForwardFailure:
		intptr = &options->exit_on_forward_failure;
		goto parse_flag;

	case oUsePrivilegedPort:
		intptr = &options->use_privileged_port;
		goto parse_flag;

	case oPasswordAuthentication:
		intptr = &options->password_authentication;
		goto parse_flag;

	case oZeroKnowledgePasswordAuthentication:
		intptr = &options->zero_knowledge_password_authentication;
		goto parse_flag;

	case oKbdInteractiveAuthentication:
		intptr = &options->kbd_interactive_authentication;
		goto parse_flag;

	case oKbdInteractiveDevices:
		charptr = &options->kbd_interactive_devices;
		goto parse_string;

	case oPubkeyAuthentication:
		intptr = &options->pubkey_authentication;
		goto parse_flag;

	case oRSAAuthentication:
		intptr = &options->rsa_authentication;
		goto parse_flag;

	case oRhostsRSAAuthentication:
		intptr = &options->rhosts_rsa_authentication;
		goto parse_flag;

	case oHostbasedAuthentication:
		intptr = &options->hostbased_authentication;
		goto parse_flag;

	case oChallengeResponseAuthentication:
		intptr = &options->challenge_response_authentication;
		goto parse_flag;

#if defined(KRB4) || defined(KRB5)
	case oKerberosAuthentication:
		intptr = &options->kerberos_authentication;
		goto parse_flag;
#endif
#if defined(AFS) || defined(KRB5)
	case oKerberosTgtPassing:
		intptr = &options->kerberos_tgt_passing;
		goto parse_flag;
#endif

	case oGssAuthentication:
		intptr = &options->gss_authentication;
		goto parse_flag;

#ifdef AFS
	case oAFSTokenPassing:
		intptr = &options->afs_token_passing;
 		goto parse_flag;
#endif

	case oGssDelegateCreds:
		intptr = &options->gss_deleg_creds;
		goto parse_flag;

	case oBatchMode:
		intptr = &options->batch_mode;
		goto parse_flag;

	case oCheckHostIP:
		intptr = &options->check_host_ip;
		goto parse_flag;

	case oNoneEnabled:
		intptr = &options->none_enabled;
		goto parse_flag;
 
	/* we check to see if the command comes from the */
	/* command line or not. If it does then enable it */
	/* otherwise fail. NONE should never be a default configuration */
	case oNoneSwitch:
		if(strcmp(filename,"command-line")==0)
		{		
		    intptr = &options->none_switch;
		    goto parse_flag;
		} else {
		    error("NoneSwitch is found in %.200s.\nYou may only use this configuration option from the command line", filename);
		    error("Continuing...");
		    debug("NoneSwitch directive found in %.200s.", filename);
		    return 0;
	        }

	case oHPNDisabled:
		intptr = &options->hpn_disabled;
		goto parse_flag;

	case oHPNBufferSize:
		intptr = &options->hpn_buffer_size;
		goto parse_int;

	case oTcpRcvBufPoll:
		intptr = &options->tcp_rcv_buf_poll;
		goto parse_flag;

	case oVerifyHostKeyDNS:
		intptr = &options->verify_host_key_dns;
		goto parse_yesnoask;

	case oStrictHostKeyChecking:
		intptr = &options->strict_host_key_checking;
parse_yesnoask:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing yes/no/ask argument.",
			    filename, linenum);
		value = 0;	/* To avoid compiler warning... */
		if (strcmp(arg, "yes") == 0 || strcmp(arg, "true") == 0)
			value = 1;
		else if (strcmp(arg, "no") == 0 || strcmp(arg, "false") == 0)
			value = 0;
		else if (strcmp(arg, "ask") == 0)
			value = 2;
		else
			fatal("%.200s line %d: Bad yes/no/ask argument.", filename, linenum);
		if (*activep && *intptr == -1)
			*intptr = value;
		break;

	case oCompression:
		intptr = &options->compression;
		goto parse_flag;

	case oTCPKeepAlive:
		intptr = &options->tcp_keep_alive;
		goto parse_flag;

	case oNoHostAuthenticationForLocalhost:
		intptr = &options->no_host_authentication_for_localhost;
		goto parse_flag;

	case oNumberOfPasswordPrompts:
		intptr = &options->number_of_password_prompts;
		goto parse_int;

	case oCompressionLevel:
		intptr = &options->compression_level;
		goto parse_int;

	case oRekeyLimit:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing argument.", filename, linenum);
		if (arg[0] < '0' || arg[0] > '9')
			fatal("%.200s line %d: Bad number.", filename, linenum);
		orig = val64 = strtoll(arg, &endofnumber, 10);
		if (arg == endofnumber)
			fatal("%.200s line %d: Bad number.", filename, linenum);
		switch (toupper((unsigned char)*endofnumber)) {
		case '\0':
			scale = 1;
			break;
		case 'K':
			scale = 1<<10;
			break;
		case 'M':
			scale = 1<<20;
			break;
		case 'G':
			scale = 1<<30;
			break;
		default:
			scale = 0;
			fatal("%.200s line %d: Invalid RekeyLimit suffix",
			    filename, linenum);
		}
		val64 *= scale;
		/* detect integer wrap and too-large limits */
		if ((val64 / scale) != orig || val64 > UINT_MAX)
			fatal("%.200s line %d: RekeyLimit too large",
			    filename, linenum);
		if (val64 < 16)
			fatal("%.200s line %d: RekeyLimit too small",
			    filename, linenum);
		if (*activep && options->rekey_limit == -1)
			options->rekey_limit = (u_int32_t)val64;
		break;

	case oIdentityFile:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing argument.", filename, linenum);
		if (*activep) {
			intptr = &options->num_identity_files;
			if (*intptr >= SSH_MAX_IDENTITY_FILES)
				fatal("%.200s line %d: Too many identity files specified (max %d).",
				    filename, linenum, SSH_MAX_IDENTITY_FILES);
			charptr = &options->identity_files[*intptr];
			*charptr = xstrdup(arg);
			*intptr = *intptr + 1;
		}
		break;

	case oXAuthLocation:
		charptr=&options->xauth_location;
		goto parse_string;

	case oUser:
		charptr = &options->user;
parse_string:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing argument.",
			    filename, linenum);
		if (*activep && *charptr == NULL)
			*charptr = xstrdup(arg);
		break;

	case oGlobalKnownHostsFile:
		cpptr = (char **)&options->system_hostfiles;
		uintptr = &options->num_system_hostfiles;
		max_entries = SSH_MAX_HOSTS_FILES;
parse_char_array:
		if (*activep && *uintptr == 0) {
			while ((arg = strdelim(&s)) != NULL && *arg != '\0') {
				if ((*uintptr) >= max_entries)
					fatal("%s line %d: "
					    "too many authorized keys files.",
					    filename, linenum);
				cpptr[(*uintptr)++] = xstrdup(arg);
			}
		}
		return 0;

	case oUserKnownHostsFile:
		cpptr = (char **)&options->user_hostfiles;
		uintptr = &options->num_user_hostfiles;
		max_entries = SSH_MAX_HOSTS_FILES;
		goto parse_char_array;

	case oHostName:
		charptr = &options->hostname;
		goto parse_string;

	case oHostKeyAlias:
		charptr = &options->host_key_alias;
		goto parse_string;

	case oPreferredAuthentications:
		charptr = &options->preferred_authentications;
		goto parse_string;

	case oBindAddress:
		charptr = &options->bind_address;
		goto parse_string;

	case oPKCS11Provider:
		charptr = &options->pkcs11_provider;
		goto parse_string;

	case oProxyCommand:
		charptr = &options->proxy_command;
parse_command:
		if (s == NULL)
			fatal("%.200s line %d: Missing argument.", filename, linenum);
		len = strspn(s, WHITESPACE "=");
		if (*activep && *charptr == NULL)
			*charptr = xstrdup(s + len);
		return 0;

	case oPort:
		intptr = &options->port;
parse_int:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing argument.", filename, linenum);
		if (arg[0] < '0' || arg[0] > '9')
			fatal("%.200s line %d: Bad number.", filename, linenum);

		/* Octal, decimal, or hex format? */
		value = strtol(arg, &endofnumber, 0);
		if (arg == endofnumber)
			fatal("%.200s line %d: Bad number.", filename, linenum);
		if (*activep && *intptr == -1)
			*intptr = value;
		break;

	case oConnectionAttempts:
		intptr = &options->connection_attempts;
		goto parse_int;

	case oTcpRcvBuf:
		intptr = &options->tcp_rcv_buf;
		goto parse_int;

	case oCipher:
		intptr = &options->cipher;
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing argument.", filename, linenum);
		value = cipher_number(arg);
		if (value == -1)
			fatal("%.200s line %d: Bad cipher '%s'.",
			    filename, linenum, arg ? arg : "<NONE>");
		if (*activep && *intptr == -1)
			*intptr = value;
		break;

	case oCiphers:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing argument.", filename, linenum);
		if (!ciphers_valid(arg))
			fatal("%.200s line %d: Bad SSH2 cipher spec '%s'.",
			    filename, linenum, arg ? arg : "<NONE>");
		if (*activep && options->ciphers == NULL)
			options->ciphers = xstrdup(arg);
		break;

	case oMacs:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing argument.", filename, linenum);
		if (!mac_valid(arg))
			fatal("%.200s line %d: Bad SSH2 Mac spec '%s'.",
			    filename, linenum, arg ? arg : "<NONE>");
		if (*activep && options->macs == NULL)
			options->macs = xstrdup(arg);
		break;

	case oKexAlgorithms:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing argument.",
			    filename, linenum);
		if (!kex_names_valid(arg))
			fatal("%.200s line %d: Bad SSH2 KexAlgorithms '%s'.",
			    filename, linenum, arg ? arg : "<NONE>");
		if (*activep && options->kex_algorithms == NULL)
			options->kex_algorithms = xstrdup(arg);
		break;

	case oHostKeyAlgorithms:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing argument.", filename, linenum);
		if (!key_names_valid2(arg))
			fatal("%.200s line %d: Bad protocol 2 host key algorithms '%s'.",
			    filename, linenum, arg ? arg : "<NONE>");
		if (*activep && options->hostkeyalgorithms == NULL)
			options->hostkeyalgorithms = xstrdup(arg);
		break;

	case oProtocol:
		intptr = &options->protocol;
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing argument.", filename, linenum);
		value = proto_spec(arg);
		if (value == SSH_PROTO_UNKNOWN)
			fatal("%.200s line %d: Bad protocol spec '%s'.",
			    filename, linenum, arg ? arg : "<NONE>");
		if (*activep && *intptr == SSH_PROTO_UNKNOWN)
			*intptr = value;
		break;

	case oLogLevel:
		log_level_ptr = &options->log_level;
		arg = strdelim(&s);
		value = log_level_number(arg);
		if (value == SYSLOG_LEVEL_NOT_SET)
			fatal("%.200s line %d: unsupported log level '%s'",
			    filename, linenum, arg ? arg : "<NONE>");
		if (*activep && *log_level_ptr == SYSLOG_LEVEL_NOT_SET)
			*log_level_ptr = (LogLevel) value;
		break;

	case oLocalForward:
	case oRemoteForward:
	case oDynamicForward:
		arg = strdelim(&s);
		if (arg == NULL || *arg == '\0')
			fatal("%.200s line %d: Missing port argument.",
			    filename, linenum);

		if (opcode == oLocalForward ||
		    opcode == oRemoteForward) {
			arg2 = strdelim(&s);
			if (arg2 == NULL || *arg2 == '\0')
				fatal("%.200s line %d: Missing target argument.",
				    filename, linenum);

			/* construct a string for parse_forward */
			snprintf(fwdarg, sizeof(fwdarg), "%s:%s", arg, arg2);
		} else if (opcode == oDynamicForward) {
			strlcpy(fwdarg, arg, sizeof(fwdarg));
		}

		if (parse_forward(&fwd, fwdarg,
		    opcode == oDynamicForward ? 1 : 0,
		    opcode == oRemoteForward ? 1 : 0) == 0)
			fatal("%.200s line %d: Bad forwarding specification.",
			    filename, linenum);

		if (*activep) {
			if (opcode == oLocalForward ||
			    opcode == oDynamicForward)
				add_local_forward(options, &fwd);
			else if (opcode == oRemoteForward)
				add_remote_forward(options, &fwd);
		}
		break;

	case oClearAllForwardings:
		intptr = &options->clear_forwardings;
		goto parse_flag;

	case oHost:
		*activep = 0;
		arg2 = NULL;
		while ((arg = strdelim(&s)) != NULL && *arg != '\0') {
			negated = *arg == '!';
			if (negated)
				arg++;
			if (match_pattern(host, arg)) {
				if (negated) {
					debug("%.200s line %d: Skipping Host "
					    "block because of negated match "
					    "for %.100s", filename, linenum,
					    arg);
					*activep = 0;
					break;
				}
				if (!*activep)
					arg2 = arg; /* logged below */
				*activep = 1;
			}
		}
		if (*activep)
			debug("%.200s line %d: Applying options for %.100s",
			    filename, linenum, arg2);
		/* Avoid garbage check below, as strdelim is done. */
		return 0;

	case oEscapeChar:
		intptr = &options->escape_char;
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing argument.", filename, linenum);
		value = 0;	/* To avoid compiler warning... */
		if (arg[0] == '^' && arg[2] == 0 &&
		    (u_char) arg[1] >= 64 && (u_char) arg[1] < 128)
			value = (u_char) arg[1] & 31;
		else if (strlen(arg) == 1)
			value = (u_char) arg[0];
		else if (strcmp(arg, "none") == 0)
			value = SSH_ESCAPECHAR_NONE;
		else {
			fatal("%.200s line %d: Bad escape character.",
			    filename, linenum);
			/* NOTREACHED */
			value = 0;	/* Avoid compiler warning. */
		}
		if (*activep && *intptr == -1)
			*intptr = value;
		break;

	case oAddressFamily:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%s line %d: missing address family.",
			    filename, linenum);
		intptr = &options->address_family;
		value = 0;	/* To avoid compiler warning... */
		if (strcasecmp(arg, "inet") == 0)
			value = AF_INET;
		else if (strcasecmp(arg, "inet6") == 0)
			value = AF_INET6;
		else if (strcasecmp(arg, "any") == 0)
			value = AF_UNSPEC;
		else
			fatal("Unsupported AddressFamily \"%s\"", arg);
		if (*activep && *intptr == -1)
			*intptr = value;
		break;

	case oEnableSSHKeysign:
		intptr = &options->enable_ssh_keysign;
		goto parse_flag;

	case oIdentitiesOnly:
		intptr = &options->identities_only;
		goto parse_flag;

	case oServerAliveInterval:
		intptr = &options->server_alive_interval;
		goto parse_time;

	case oServerAliveCountMax:
		intptr = &options->server_alive_count_max;
		goto parse_int;

	case oSendEnv:
		while ((arg = strdelim(&s)) != NULL && *arg != '\0') {
			if (strchr(arg, '=') != NULL)
				fatal("%s line %d: Invalid environment name.",
				    filename, linenum);
			if (!*activep)
				continue;
			if (options->num_send_env >= MAX_SEND_ENV)
				fatal("%s line %d: too many send env.",
				    filename, linenum);
			options->send_env[options->num_send_env++] =
			    xstrdup(arg);
		}
		break;

	case oControlPath:
		charptr = &options->control_path;
		goto parse_string;

	case oControlMaster:
		intptr = &options->control_master;
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing ControlMaster argument.",
			    filename, linenum);
		value = 0;	/* To avoid compiler warning... */
		if (strcmp(arg, "yes") == 0 || strcmp(arg, "true") == 0)
			value = SSHCTL_MASTER_YES;
		else if (strcmp(arg, "no") == 0 || strcmp(arg, "false") == 0)
			value = SSHCTL_MASTER_NO;
		else if (strcmp(arg, "auto") == 0)
			value = SSHCTL_MASTER_AUTO;
		else if (strcmp(arg, "ask") == 0)
			value = SSHCTL_MASTER_ASK;
		else if (strcmp(arg, "autoask") == 0)
			value = SSHCTL_MASTER_AUTO_ASK;
		else
			fatal("%.200s line %d: Bad ControlMaster argument.",
			    filename, linenum);
		if (*activep && *intptr == -1)
			*intptr = value;
		break;

	case oControlPersist:
		/* no/false/yes/true, or a time spec */
		intptr = &options->control_persist;
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing ControlPersist"
			    " argument.", filename, linenum);
		value = 0;
		value2 = 0;	/* timeout */
		if (strcmp(arg, "no") == 0 || strcmp(arg, "false") == 0)
			value = 0;
		else if (strcmp(arg, "yes") == 0 || strcmp(arg, "true") == 0)
			value = 1;
		else if ((value2 = convtime(arg)) >= 0)
			value = 1;
		else
			fatal("%.200s line %d: Bad ControlPersist argument.",
			    filename, linenum);
		if (*activep && *intptr == -1) {
			*intptr = value;
			options->control_persist_timeout = value2;
		}
		break;

	case oHashKnownHosts:
		intptr = &options->hash_known_hosts;
		goto parse_flag;

	case oTunnel:
		intptr = &options->tun_open;
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%s line %d: Missing yes/point-to-point/"
			    "ethernet/no argument.", filename, linenum);
		value = 0;	/* silence compiler */
		if (strcasecmp(arg, "ethernet") == 0)
			value = SSH_TUNMODE_ETHERNET;
		else if (strcasecmp(arg, "point-to-point") == 0)
			value = SSH_TUNMODE_POINTOPOINT;
		else if (strcasecmp(arg, "yes") == 0)
			value = SSH_TUNMODE_DEFAULT;
		else if (strcasecmp(arg, "no") == 0)
			value = SSH_TUNMODE_NO;
		else
			fatal("%s line %d: Bad yes/point-to-point/ethernet/"
			    "no argument: %s", filename, linenum, arg);
		if (*activep)
			*intptr = value;
		break;

	case oTunnelDevice:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%.200s line %d: Missing argument.", filename, linenum);
		value = a2tun(arg, &value2);
		if (value == SSH_TUNID_ERR)
			fatal("%.200s line %d: Bad tun device.", filename, linenum);
		if (*activep) {
			options->tun_local = value;
			options->tun_remote = value2;
		}
		break;

	case oLocalCommand:
		charptr = &options->local_command;
		goto parse_command;

	case oPermitLocalCommand:
		intptr = &options->permit_local_command;
		goto parse_flag;

	case oVisualHostKey:
		intptr = &options->visual_host_key;
		goto parse_flag;

	case oIPQoS:
		arg = strdelim(&s);
		if ((value = parse_ipqos(arg)) == -1)
			fatal("%s line %d: Bad IPQoS value: %s",
			    filename, linenum, arg);
		arg = strdelim(&s);
		if (arg == NULL)
			value2 = value;
		else if ((value2 = parse_ipqos(arg)) == -1)
			fatal("%s line %d: Bad IPQoS value: %s",
			    filename, linenum, arg);
		if (*activep) {
			options->ip_qos_interactive = value;
			options->ip_qos_bulk = value2;
		}
		break;

	case oUseRoaming:
		intptr = &options->use_roaming;
		goto parse_flag;

	case oRequestTTY:
		arg = strdelim(&s);
		if (!arg || *arg == '\0')
			fatal("%s line %d: missing argument.",
			    filename, linenum);
		intptr = &options->request_tty;
		if (strcasecmp(arg, "yes") == 0)
			value = REQUEST_TTY_YES;
		else if (strcasecmp(arg, "no") == 0)
			value = REQUEST_TTY_NO;
		else if (strcasecmp(arg, "force") == 0)
			value = REQUEST_TTY_FORCE;
		else if (strcasecmp(arg, "auto") == 0)
			value = REQUEST_TTY_AUTO;
		else
			fatal("Unsupported RequestTTY \"%s\"", arg);
		if (*activep && *intptr == -1)
			*intptr = value;
		break;

	case oDeprecated:
		debug("%s line %d: Deprecated option \"%s\"",
		    filename, linenum, keyword);
		return 0;

	case oUnsupported:
		error("%s line %d: Unsupported option \"%s\"",
		    filename, linenum, keyword);
		return 0;

	default:
		fatal("process_config_line: Unimplemented opcode %d", opcode);
	}

	/* Check that there is no garbage at end of line. */
	if ((arg = strdelim(&s)) != NULL && *arg != '\0') {
		fatal("%.200s line %d: garbage at end of line; \"%.200s\".",
		    filename, linenum, arg);
	}
	return 0;
}