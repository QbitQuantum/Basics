int main(int argc, char *argv[], char *envp[])
{
	int i;
	struct line_list l, options, request_list;
	char msg[SMALLBUFFER], *s;

	Init_line_list(&l);
	Init_line_list(&options);
	Init_line_list(&request_list);

	/* set signal handlers */
	(void) plp_signal (SIGHUP, cleanup_HUP);
	(void) plp_signal (SIGINT, cleanup_INT);
	(void) plp_signal (SIGQUIT, cleanup_QUIT);
	(void) plp_signal (SIGTERM, cleanup_TERM);
	(void) signal(SIGCHLD, SIG_DFL);
	(void) signal(SIGPIPE, SIG_IGN);

	/*
	 * set up the user state
	 */

	Status_line_count = 1;

#ifndef NODEBUG
	Debug = 0;
#endif

	Displayformat = REQ_DLONG;

	Initialize(argc, argv, envp, 'T' );
	Setup_configuration();
	Get_parms(argc, argv );      /* scan input args */
	if( A_flag && !getenv( "AUTH" ) ){
		FPRINTF(STDERR,"lpstat: requested authenticated transfer (-A) and AUTH environment variable not set");
		usage();
	}

	/* set up configuration */
	Get_printer();
	Fix_Rm_Rp_info(0,0);
	Get_all_printcap_entries();

	/* check on printing scheduler is running */
	if( t_flag ){
		All_printers = 1;
		r_flag = d_flag = p_flag = o_flag = 1;
		s_flag = 0;
	}
	if( s_flag ){
		/* a_flag = 1; */
		r_flag = 1;
		d_flag = 1;
		v_flag = 1;
		All_printers = 1;
	}

	if( All_printers ){
		Merge_line_list( &request_list, &All_line_list,0,0,0);
	}
	Merge_line_list( &request_list, &Printer_list,0,0,0);
	Check_max(&options,2);
	if( options.count ){
		for( i = options.count; i > 0 ; --i ){
			options.list[i] = options.list[i-1];
		}
		options.list[0] = safestrdup(Logname_DYN,__FILE__,__LINE__);
		++options.count;
	}
	options.list[options.count] = 0;

	if( Found_flag == 0 ){
		if( request_list.count == 0 ){
			Split(&request_list,Printer_DYN,", ",1,0,1,1,0,0);
		}
		o_flag = 1;
		flag_count = 1;
	}
#ifdef ORIGINAL_DEBUG//JY@1020
	if(DEBUGL1)Dump_line_list("lpstat - printer request list", &request_list);
	if(DEBUGL1)Dump_line_list("lpstat - options", &options);
#endif

	if( r_flag ){
		Write_fd_str(1,"scheduler is running\n");
	}
	if( d_flag ){
		if( Printer_DYN == 0 ){
			Write_fd_str(1,"no system default destination\n");
		} else {
			SNPRINTF(msg,sizeof(msg))
				"system default destination: %s\n", Printer_DYN);
			Write_fd_str(1,msg);
		}
	}
	if( v_flag ){
		for( i = 0; i < request_list.count; ++i ){
			Set_DYN(&Printer_DYN,request_list.list[i] );
			Fix_Rm_Rp_info(0,0);
			SNPRINTF(msg,sizeof(msg)) "system for %s: %s\n", Printer_DYN, RemoteHost_DYN);
			Write_fd_str(1,msg);
		}
	}

	/* see if additional status required */

	Free_line_list( &Printer_list );

	for( i = 0; i < request_list.count; ++i ){
		s = request_list.list[i];
		Set_DYN(&Printer_DYN,s );
		Show_status(options.list, 0);
	}

	Free_line_list( &Printer_list );
	if( flag_count ){
		for( i = 0; i < request_list.count; ++i ){
			s = request_list.list[i];
			Set_DYN(&Printer_DYN,s );
			Show_status(options.list, 1);
		}
	}

	DEBUG1("lpstat: done");
	Remove_tempfiles();
	DEBUG1("lpstat: tempfiles removed");

	Errorcode = 0;
	DEBUG1("lpstat: cleaning up");
	return(0);
}