//-----------------------------------------------------------------------------
//	process_options
//-----------------------------------------------------------------------------
int process_options(struct vpn_params *params, int argc, char *argv[])
{
    
    char* 		argv0 = argv[0];
    char* 		args = "dhnxi:";
    char		c;
        
    /* initialize generic portion */
	params->max_sessions = 0;
    params->debug = 0;
	params->log_verbose = 0;
    params->daemonize = 1;
    params->serverIDRef = 0;
    params->serverRef = 0;
    params->server_id = 0;
    params->server_type = -1;
    params->storeRef = 0;
    params->next_arg_index = 0;
    params->log_path[0] = 0;
    
    // Process command line arguments, if any
    while ((opterr == 1) && (c = getopt(argc, argv, args)) != EOF) {
        switch (c) {
            case 'h':
                usage (stdout, argv0);
                exit (0);
                
            case 'n':
                set_terminate();
                /* FALLTHRU */

            case 'd':
                params->debug = 1;
                break;

            case 'x':
                params->daemonize = 0;
                break ;
                
            case 'i':
                params->server_id = optarg;
                break ;
                    
            default:
                usage(stderr, argv0);
                return -1;
        }
    }
                    
	/* init ppp portion */
	ppp_process_options(params);
	
	/* init ipsec portion */
	ipsec_process_options(params);
	
    return 0;
}