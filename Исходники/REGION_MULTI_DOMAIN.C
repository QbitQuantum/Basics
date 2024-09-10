main()
{
	longword seq,ping_who,tmp_seq,time_out;
	char	buffer[100];


	brdInit();				//initialize board for this demo
	seq=0;

	sock_init();			// Initialize wifi interface

   // Make sure wifi IF is down to do ifconfig's functions
	printf("\nBringing interface down (disassociate)...\n");
   ifdown(IF_WIFI0);
   while (ifpending(IF_WIFI0) != IF_DOWN) {
     	printf(".");
     	tcp_tick(NULL);
   }
	printf("...Done.\n");

   // Enable 802.11d country information capability
   // Note: Access Point must have 802.11d enabled with proper country selected
   ifconfig(IF_WIFI0, IFS_WIFI_MULTI_DOMAIN, 1, IFS_END);

   // Startup the  wireless interface here...
	printf("Bringing interface back up (associate)...\n");
   ifup(IF_WIFI0);
   while (ifpending(IF_WIFI0) == IF_COMING_UP) {
      tcp_tick(NULL);
   }
	printf("...Done.\n");
	if (ifpending(IF_WIFI0) != IF_UP) {
		printf("Unfortunately, it failed to associate :-(\n");
		exit(1);
	}
   // End of regional setting section, from this point on do standard tcp/ip
   // protocol.


   /*
   // Here is where we gather the statistics...
	// Note that if you get a compile error here, it is because you are not running
	// this sample on a Wifi-equipped board.

	/* Print who we are... */
	printf( "My IP address is %s\n\n", inet_ntoa(buffer, gethostid()) );

	/*
	 *		Get the binary ip address for the target of our
	 *		pinging.
	 */

#ifdef PING_WHO
	/* Ping a specific IP addr: */
	ping_who=resolve(PING_WHO);
	if(ping_who==0) {
		printf("ERROR: unable to resolve %s\n",PING_WHO);
		exit(2);
	}
#else
	/* Examine our configuration, and ping the default router: */
	tmp_seq = ifconfig( IF_ANY, IFG_ROUTER_DEFAULT, & ping_who, IFS_END );
	if( tmp_seq != 0 ) {
		printf( "ERROR: ifconfig() failed --> %d\n", (int) tmp_seq );
		exit(2);
	}
	if(ping_who==0) {
		printf("ERROR: unable to resolve IFG_ROUTER_DEFAULT\n");
		exit(2);
	}
#endif

	for(;;) {
		/*
		 *		It is important to call tcp_tick here because
		 *		ping packets will not get processed otherwise.
		 *
		 */

		tcp_tick(NULL);

		/*
		 *		Send one ping every PING_DELAY ms.
		 */

		costate {
			waitfor(DelayMs(PING_DELAY));
			pingoutled(LEDON);					// flash transmit LED
			waitfor(DelayMs(50));
			pingoutled(LEDOFF);
			_ping(ping_who,seq++);
		}

		/*
		 *		Has a ping come in?  time_out!=0xfffffff->yes.
		 */

		costate {
			time_out=_chk_ping(ping_who,&tmp_seq);
			if(time_out!=0xffffffff) {

#ifdef VERBOSE
				printf("received ping:  %ld\n", tmp_seq);
#endif

				pinginled(LEDON);					// flash receive LED
				waitfor(DelayMs(50));
				pinginled(LEDOFF);
#if RCM5600W_SERIES
				waitfor(DelayMs(250));
				pinginled(LEDON);					// flash receive LED again
				waitfor(DelayMs(50));
				pinginled(LEDOFF);
#endif
			}
		}
	}
}