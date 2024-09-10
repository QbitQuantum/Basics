int main(int argc, char **argv, char **env){
#else
int main(int argc, char **argv){
#endif
	int result;
	int error=FALSE;
	char *buffer=NULL;
	int display_license=FALSE;
	int display_help=FALSE;
	int c=0;
	struct tm *tm;
	time_t now;
	char datestring[256];



#ifdef HAVE_GETOPT_H
	int option_index=0;
	static struct option long_options[]=
	{
		{"help",no_argument,0,'h'},
		{"version",no_argument,0,'V'},
		{"license",no_argument,0,'V'},
		{"verify-config",no_argument,0,'v'},
		{"daemon",no_argument,0,'d'},
		{"test-scheduling",no_argument,0,'s'},
		{"dont-verify-objects",no_argument,0,'o'},
		{"dont-verify-paths",no_argument,0,'x'},
		{"precache-objects",no_argument,0,'p'},
		{"use-precached-objects",no_argument,0,'u'},
		{0,0,0,0}
	};
#endif

	/* make sure we have the correct number of command line arguments */
	if(argc<2)
		error=TRUE;


	/* get all command line arguments */
	while(1){

#ifdef HAVE_GETOPT_H
		c=getopt_long(argc,argv,"+hVvdsoxpu",long_options,&option_index);
#else
		c=getopt(argc,argv,"+hVvdsoxpu");
#endif

		if(c==-1 || c==EOF)
			break;

		switch(c){
			
		case '?': /* usage */
		case 'h':
			display_help=TRUE;
			break;

		case 'V': /* version */
			display_license=TRUE;
			break;

		case 'v': /* verify */
			verify_config=TRUE;
			break;

		case 's': /* scheduling check */
			test_scheduling=TRUE;
			break;

		case 'd': /* daemon mode */
			daemon_mode=TRUE;
			break;

		case 'o': /* don't verify objects */
			/*
			verify_object_relationships=FALSE;
			*/
			break;

		case 'x': /* don't verify circular paths */
			verify_circular_paths=FALSE;
			break;

		case 'p': /* precache object config */
			precache_objects=TRUE;
			break;

		case 'u': /* use precached object config */
			use_precached_objects=TRUE;
			break;

		default:
			break;
		        }

	        }

	/* make sure we have the right combination of arguments */
	if(precache_objects==TRUE && (test_scheduling==FALSE && verify_config==FALSE)){
		error=TRUE;
		display_help=TRUE;
	        }

#ifdef DEBUG_MEMORY
	mtrace();
#endif

	if(daemon_mode==FALSE){
		printf("\nNagios Core %s\n",PROGRAM_VERSION);
		printf("Copyright (c) 2009 Nagios Core Development Team and Community Contributors\n");
		printf("Copyright (c) 1999-2009 Ethan Galstad\n");
		printf("Last Modified: %s\n",PROGRAM_MODIFICATION_DATE);
		printf("License: GPL\n\n");
		printf("Website: http://www.nagios.org\n");
	        }

	/* just display the license */
	if(display_license==TRUE){

		printf("This program is free software; you can redistribute it and/or modify\n");
		printf("it under the terms of the GNU General Public License version 2 as\n");
		printf("published by the Free Software Foundation.\n\n");
		printf("This program is distributed in the hope that it will be useful,\n");
		printf("but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
		printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
		printf("GNU General Public License for more details.\n\n");
		printf("You should have received a copy of the GNU General Public License\n");
		printf("along with this program; if not, write to the Free Software\n");
		printf("Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.\n\n");

		exit(OK);
	        }

	/* make sure we got the main config file on the command line... */
	if(optind>=argc)
		error=TRUE;

	/* if there are no command line options (or if we encountered an error), print usage */
	if(error==TRUE || display_help==TRUE){

		printf("Usage: %s [options] <main_config_file>\n",argv[0]);
		printf("\n");
		printf("Options:\n");
		printf("\n");
		printf("  -v, --verify-config          Verify all configuration data\n");
		printf("  -s, --test-scheduling        Shows projected/recommended check scheduling and other\n");
		printf("                               diagnostic info based on the current configuration files.\n");
		/*printf("  -o, --dont-verify-objects    Don't verify object relationships - USE WITH CAUTION!\n");*/
		printf("  -x, --dont-verify-paths      Don't check for circular object paths - USE WITH CAUTION!\n");
		printf("  -p, --precache-objects       Precache object configuration - use with -v or -s options\n");
		printf("  -u, --use-precached-objects  Use precached object config file\n");
		printf("  -d, --daemon                 Starts Nagios in daemon mode, instead of as a foreground process\n");
		printf("\n");
		printf("Visit the Nagios website at http://www.nagios.org/ for bug fixes, new\n");
		printf("releases, online documentation, FAQs, information on subscribing to\n");
		printf("the mailing lists, and commercial support options for Nagios.\n");
		printf("\n");

		exit(ERROR);
		}


	/* config file is last argument specified */
	config_file=(char *)strdup(argv[optind]);
	if(config_file==NULL){
		printf("Error allocating memory.\n");
		exit(ERROR);
	        }

	/* make sure the config file uses an absolute path */
	if(config_file[0]!='/'){

		/* save the name of the config file */
		buffer=(char *)strdup(config_file);

		/* reallocate a larger chunk of memory */
		config_file=(char *)realloc(config_file,MAX_FILENAME_LENGTH);
		if(config_file==NULL){
			printf("Error allocating memory.\n");
			exit(ERROR);
		        }

		/* get absolute path of current working directory */
		getcwd(config_file,MAX_FILENAME_LENGTH);

		/* append a forward slash */
		strncat(config_file,"/",1);
		config_file[MAX_FILENAME_LENGTH-1]='\x0';

		/* append the config file to the path */
		strncat(config_file,buffer,MAX_FILENAME_LENGTH-strlen(config_file)-1);
		config_file[MAX_FILENAME_LENGTH-1]='\x0';

		my_free(buffer);
	        }


	/* we're just verifying the configuration... */
	if(verify_config==TRUE){

		/* reset program variables */
		reset_variables();

		printf("Reading configuration data...\n");

		/* read in the configuration files (main config file, resource and object config files) */
		if((result=read_main_config_file(config_file))==OK){

			printf("   Read main config file okay...\n");

			/* drop privileges */
			if((result=drop_privileges(nagios_user,nagios_group))==ERROR)
				printf("   Failed to drop privileges.  Aborting.");
			else{
				/* read object config files */
				if((result=read_all_object_data(config_file))==OK)
					printf("   Read object config files okay...\n");
				else
					printf("   Error processing object config files!\n");
				}
		        }
		else
			printf("   Error processing main config file!\n\n");

		printf("\n");

		/* there was a problem reading the config files */
		if(result!=OK){

			/* if the config filename looks fishy, warn the user */
			if(!strstr(config_file,"nagios.cfg")){
				printf("\n***> The name of the main configuration file looks suspicious...\n");
				printf("\n");
				printf("     Make sure you are specifying the name of the MAIN configuration file on\n");
				printf("     the command line and not the name of another configuration file.  The\n");
				printf("     main configuration file is typically '/usr/local/nagios/etc/nagios.cfg'\n");
	                        }

			printf("\n***> One or more problems was encountered while processing the config files...\n");
			printf("\n");
			printf("     Check your configuration file(s) to ensure that they contain valid\n");
			printf("     directives and data defintions.  If you are upgrading from a previous\n");
			printf("     version of Nagios, you should be aware that some variables/definitions\n");
			printf("     may have been removed or modified in this version.  Make sure to read\n");
			printf("     the HTML documentation regarding the config files, as well as the\n");
			printf("     'Whats New' section to find out what has changed.\n\n");
		        }

		/* the config files were okay, so run the pre-flight check */
		else{

			printf("Running pre-flight check on configuration data...\n\n");

			/* run the pre-flight check to make sure things look okay... */
			result=pre_flight_check();

			if(result==OK)
				printf("\nThings look okay - No serious problems were detected during the pre-flight check\n");
			else{
				printf("\n***> One or more problems was encountered while running the pre-flight check...\n");
				printf("\n");
				printf("     Check your configuration file(s) to ensure that they contain valid\n");
				printf("     directives and data defintions.  If you are upgrading from a previous\n");
				printf("     version of Nagios, you should be aware that some variables/definitions\n");
				printf("     may have been removed or modified in this version.  Make sure to read\n");
				printf("     the HTML documentation regarding the config files, as well as the\n");
				printf("     'Whats New' section to find out what has changed.\n\n");
			        }
		        }

		/* clean up after ourselves */
		cleanup();

		/* free config_file */
		my_free(config_file);

		/* exit */
		exit(result);
	        }


	/* we're just testing scheduling... */
	else if(test_scheduling==TRUE){

		/* reset program variables */
		reset_variables();

		/* read in the configuration files (main config file and all host config files) */
		result=read_main_config_file(config_file);

		/* drop privileges */
		if(result==OK)
			if((result=drop_privileges(nagios_user,nagios_group))==ERROR)
				printf("Failed to drop privileges.  Aborting.");

		/* read object config files */
		if(result==OK)
			result=read_all_object_data(config_file);

		/* read initial service and host state information */
		if(result==OK){
			initialize_retention_data(config_file);
			read_initial_state_information();
			}

		if(result!=OK)
			printf("***> One or more problems was encountered while reading configuration data...\n");

		/* run the pre-flight check to make sure everything looks okay */
		if(result==OK){
			if((result=pre_flight_check())!=OK)
				printf("***> One or more problems was encountered while running the pre-flight check...\n");
			}

		if(result==OK){

			/* initialize the event timing loop */
			init_timing_loop();

			/* display scheduling information */
			display_scheduling_info();

			if(precache_objects==TRUE){
				printf("\n");
				printf("OBJECT PRECACHING\n");
				printf("-----------------\n");
				printf("Object config files were precached.\n");
				}
		        }

#undef TEST_TIMEPERIODS
#ifdef TEST_TIMEPERIODS
		/* DO SOME TIMEPERIOD TESTING - ADDED 08/11/2009 */
		time_t now, pref_time, valid_time;
		timeperiod *tp;
		tp=find_timeperiod("247_exclusion");
		time(&now);
		pref_time=now;
		get_next_valid_time(pref_time,&valid_time,tp);
		printf("=====\n");
		printf("CURRENT:   %lu = %s",(unsigned long)now,ctime(&now));
		printf("PREFERRED: %lu = %s",(unsigned long)pref_time,ctime(&pref_time));
		printf("NEXT:      %lu = %s",(unsigned long)valid_time,ctime(&valid_time));
		printf("=====\n");
#endif

		/* clean up after ourselves */
		cleanup();

		/* exit */
		exit(result);
	        }


	/* else start to monitor things... */
	else{

		/* keep monitoring things until we get a shutdown command */
		do{

			/* reset program variables */
			reset_variables();

			/* get PID */
			nagios_pid=(int)getpid();

			/* read in the configuration files (main and resource config files) */
			result=read_main_config_file(config_file);

			/* NOTE 11/06/07 EG moved to after we read config files, as user may have overridden timezone offset */
			/* get program (re)start time and save as macro */
			program_start=time(NULL);
			my_free(macro_x[MACRO_PROCESSSTARTTIME]);
			asprintf(&macro_x[MACRO_PROCESSSTARTTIME],"%lu",(unsigned long)program_start);

			/* open debug log */
			open_debug_log();

			/* drop privileges */
			if(drop_privileges(nagios_user,nagios_group)==ERROR){

				logit(NSLOG_PROCESS_INFO | NSLOG_RUNTIME_ERROR | NSLOG_CONFIG_ERROR,TRUE,"Failed to drop privileges.  Aborting.");

				cleanup();
				exit(ERROR);
			        }

#ifdef USE_EVENT_BROKER
			/* initialize modules */
			neb_init_modules();
			neb_init_callback_list();
#endif

			/* this must be logged after we read config data, as user may have changed location of main log file */
			logit(NSLOG_PROCESS_INFO,TRUE,"Nagios %s starting... (PID=%d)\n",PROGRAM_VERSION,(int)getpid());

			/* log the local time - may be different than clock time due to timezone offset */
			now=time(NULL);
			tm=localtime(&now);
			strftime(datestring,sizeof(datestring),"%a %b %d %H:%M:%S %Z %Y",tm);
			asprintf(&buffer,"Local time is %s\n",datestring);
			write_to_logs_and_console(buffer,NSLOG_PROCESS_INFO,TRUE);
			my_free(buffer);

			/* write log version/info */
			write_log_file_info(NULL);

#ifdef USE_EVENT_BROKER
			/* load modules */
			neb_load_all_modules();

			/* send program data to broker */
			broker_program_state(NEBTYPE_PROCESS_PRELAUNCH,NEBFLAG_NONE,NEBATTR_NONE,NULL);
#endif

			/* read in all object config data */
			if(result==OK)
				result=read_all_object_data(config_file);

			/* there was a problem reading the config files */
			if(result!=OK)
				logit(NSLOG_PROCESS_INFO | NSLOG_RUNTIME_ERROR | NSLOG_CONFIG_ERROR,TRUE,"Bailing out due to one or more errors encountered in the configuration files. Run Nagios from the command line with the -v option to verify your config before restarting. (PID=%d)",(int)getpid());

			else{

				/* run the pre-flight check to make sure everything looks okay*/
				if((result=pre_flight_check())!=OK)
					logit(NSLOG_PROCESS_INFO | NSLOG_RUNTIME_ERROR | NSLOG_VERIFICATION_ERROR,TRUE,"Bailing out due to errors encountered while running the pre-flight check.  Run Nagios from the command line with the -v option to verify your config before restarting. (PID=%d)\n",(int)getpid());
				}

			/* an error occurred that prevented us from (re)starting */
			if(result!=OK){
				
				/* if we were restarting, we need to cleanup from the previous run */
				if(sigrestart==TRUE){

					/* clean up the status data */
					cleanup_status_data(config_file,TRUE);

					/* shutdown the external command worker thread */
					shutdown_command_file_worker_thread();

					/* close and delete the external command file FIFO */
					close_command_file();

					/* cleanup embedded perl interpreter */
					if(embedded_perl_initialized==TRUE)
						deinit_embedded_perl();
					}

#ifdef USE_EVENT_BROKER
				/* send program data to broker */
				broker_program_state(NEBTYPE_PROCESS_SHUTDOWN,NEBFLAG_PROCESS_INITIATED,NEBATTR_SHUTDOWN_ABNORMAL,NULL);
#endif
				cleanup();
				exit(ERROR);
				}



			/* initialize embedded Perl interpreter */
			/* NOTE 02/15/08 embedded Perl must be initialized if compiled in, regardless of whether or not its enabled in the config file */
			/* It compiled it, but not initialized, Nagios will segfault in readdir() calls, as libperl takes this function over */
			if(embedded_perl_initialized==FALSE){
/*				if(enable_embedded_perl==TRUE){*/
#ifdef EMBEDDEDPERL
				init_embedded_perl(env);
#else
				init_embedded_perl(NULL);
#endif
				embedded_perl_initialized=TRUE;
/*					}*/
			        }

		        /* handle signals (interrupts) */
			setup_sighandler();


#ifdef USE_EVENT_BROKER
			/* send program data to broker */
			broker_program_state(NEBTYPE_PROCESS_START,NEBFLAG_NONE,NEBATTR_NONE,NULL);
#endif

			/* enter daemon mode (unless we're restarting...) */
			if(daemon_mode==TRUE && sigrestart==FALSE){

				result=daemon_init();

				/* we had an error daemonizing, so bail... */
				if(result==ERROR){
					logit(NSLOG_PROCESS_INFO | NSLOG_RUNTIME_ERROR,TRUE,"Bailing out due to failure to daemonize. (PID=%d)",(int)getpid());

#ifdef USE_EVENT_BROKER
					/* send program data to broker */
					broker_program_state(NEBTYPE_PROCESS_SHUTDOWN,NEBFLAG_PROCESS_INITIATED,NEBATTR_SHUTDOWN_ABNORMAL,NULL);
#endif
					cleanup();
					exit(ERROR);
					}

				asprintf(&buffer,"Finished daemonizing... (New PID=%d)\n",(int)getpid());
				write_to_all_logs(buffer,NSLOG_PROCESS_INFO);
				my_free(buffer);

				/* get new PID */
				nagios_pid=(int)getpid();
			        }

			/* open the command file (named pipe) for reading */
			result=open_command_file();
			if(result!=OK){

				logit(NSLOG_PROCESS_INFO | NSLOG_RUNTIME_ERROR,TRUE,"Bailing out due to errors encountered while trying to initialize the external command file... (PID=%d)\n",(int)getpid());

#ifdef USE_EVENT_BROKER
				/* send program data to broker */
				broker_program_state(NEBTYPE_PROCESS_SHUTDOWN,NEBFLAG_PROCESS_INITIATED,NEBATTR_SHUTDOWN_ABNORMAL,NULL);
#endif
				cleanup();
				exit(ERROR);
		                }

		        /* initialize status data unless we're starting */
			if(sigrestart==FALSE)
				initialize_status_data(config_file);

			/* read initial service and host state information  */
			initialize_retention_data(config_file);
			read_initial_state_information();

			/* initialize comment data */
			initialize_comment_data(config_file);
			
			/* initialize scheduled downtime data */
			initialize_downtime_data(config_file);
			
			/* initialize performance data */
			initialize_performance_data(config_file);

		        /* initialize the event timing loop */
			init_timing_loop();
			
			/* initialize check statistics */
			init_check_stats();

			/* check for updates */
			check_for_nagios_updates(FALSE,TRUE);

			/* update all status data (with retained information) */
			update_all_status_data();

			/* log initial host and service state */
			log_host_states(INITIAL_STATES,NULL);
			log_service_states(INITIAL_STATES,NULL);

			/* reset the restart flag */
			sigrestart=FALSE;

#ifdef USE_EVENT_BROKER
			/* send program data to broker */
			broker_program_state(NEBTYPE_PROCESS_EVENTLOOPSTART,NEBFLAG_NONE,NEBATTR_NONE,NULL);
#endif

			/* get event start time and save as macro */
			event_start=time(NULL);
			my_free(macro_x[MACRO_EVENTSTARTTIME]);
			asprintf(&macro_x[MACRO_EVENTSTARTTIME],"%lu",(unsigned long)event_start);

		        /***** start monitoring all services *****/
			/* (doesn't return until a restart or shutdown signal is encountered) */
			event_execution_loop();

			/* 03/01/2007 EG Moved from sighandler() to prevent FUTEX locking problems under NPTL */
			/* 03/21/2007 EG SIGSEGV signals are still logged in sighandler() so we don't loose them */
			/* did we catch a signal? */
			if(caught_signal==TRUE){

				if(sig_id==SIGHUP)
					asprintf(&buffer,"Caught SIGHUP, restarting...\n");
				else if(sig_id!=SIGSEGV)
					asprintf(&buffer,"Caught SIG%s, shutting down...\n",sigs[sig_id]);

				write_to_all_logs(buffer,NSLOG_PROCESS_INFO);
				my_free(buffer);
				}

#ifdef USE_EVENT_BROKER
			/* send program data to broker */
			broker_program_state(NEBTYPE_PROCESS_EVENTLOOPEND,NEBFLAG_NONE,NEBATTR_NONE,NULL);
			if(sigshutdown==TRUE)
				broker_program_state(NEBTYPE_PROCESS_SHUTDOWN,NEBFLAG_USER_INITIATED,NEBATTR_SHUTDOWN_NORMAL,NULL);
			else if(sigrestart==TRUE)
				broker_program_state(NEBTYPE_PROCESS_RESTART,NEBFLAG_USER_INITIATED,NEBATTR_RESTART_NORMAL,NULL);
#endif

			/* save service and host state information */
			save_state_information(FALSE);
			cleanup_retention_data(config_file);

			/* clean up performance data */
			cleanup_performance_data(config_file);

			/* clean up the scheduled downtime data */
			cleanup_downtime_data(config_file);

			/* clean up the comment data */
			cleanup_comment_data(config_file);

			/* clean up the status data unless we're restarting */
			if(sigrestart==FALSE)
				cleanup_status_data(config_file,TRUE);

			/* close and delete the external command file FIFO unless we're restarting */
			if(sigrestart==FALSE){
				shutdown_command_file_worker_thread();
				close_command_file();
				}

			/* cleanup embedded perl interpreter */
			if(sigrestart==FALSE)
				deinit_embedded_perl();

			/* shutdown stuff... */
			if(sigshutdown==TRUE){

				/* make sure lock file has been removed - it may not have been if we received a shutdown command */
				if(daemon_mode==TRUE)
					unlink(lock_file);

				/* log a shutdown message */
				logit(NSLOG_PROCESS_INFO,TRUE,"Successfully shutdown... (PID=%d)\n",(int)getpid());
 			        }

			/* clean up after ourselves */
			cleanup();

			/* close debug log */
			close_debug_log();

	                }while(sigrestart==TRUE && sigshutdown==FALSE);

		/* free misc memory */
		my_free(config_file);
	        }

	return OK;
	}