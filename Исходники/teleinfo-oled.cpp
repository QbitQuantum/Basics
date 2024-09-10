/* ======================================================================
Function: main
Purpose : Main entry Point
Input 	: -
Output	: -
Comments: 
====================================================================== */
int main(int argc, char **argv)
{
	struct sockaddr_in server;
	struct sigaction exit_action;
	int length, flags;
  int n;
	unsigned char c;
	char	rcv_buff[TELEINFO_BUFSIZE];
	int		rcv_idx;
  char time_str[200];
  time_t t;
  struct tm *tmp;
	int frame_ok ;

	rcv_idx = 0;
	g_fd_teleinfo = 0; 
	g_exit_pgm = false;
	
	bzero(rcv_buff, TELEINFO_BUFSIZE);

	parse_args(argc, argv);

	// Set up the structure to specify the exit action.
	exit_action.sa_handler = isr_handler;
	sigemptyset (&exit_action.sa_mask);
	exit_action.sa_flags = 0;
	sigaction (SIGTERM, &exit_action, NULL);
	sigaction (SIGINT, &exit_action, NULL); 

	// Grab teleinfo frame from network
	if (opts.mode == MODE_NET )
	{
		// Init Sockets
		g_tlf_sock=socket(AF_INET, SOCK_DGRAM, 0);
		
		if (g_tlf_sock < 0) 
			fatal( "Error Opening Socket %d: %s\n",g_tlf_sock, strerror (errno));
		else
		{
			if (opts.verbose)
				log_syslog(stderr, "Opened Socket\n");
		}
		
		flags = fcntl(g_tlf_sock,F_GETFL,0);
		fcntl(g_tlf_sock, F_SETFL, flags | O_NONBLOCK);

		length = sizeof(server);
		bzero(&server,length);
		
		server.sin_family=AF_INET;
		server.sin_addr.s_addr=INADDR_ANY;
		server.sin_port=htons(opts.netport);
		
		if ( bind(g_tlf_sock,(struct sockaddr *)&server,length) < 0 ) 
			fatal("Error Binding Socket %d : %s\n", g_tlf_sock, strerror (errno));
		else
		{
			if (opts.verbose)
				log_syslog(stderr, "Binded on port %d\n",opts.netport);
		}

		if (opts.verbose)
			log_syslog(stdout, "Network Init succeded\n");
		
	}

	// Grab teleinfo frame from serial device
	if (opts.mode == MODE_SERIAL)
	{
		if ( (g_fd_teleinfo = tlf_init_serial()) >0 )
		{
			if (opts.verbose)
				log_syslog(stdout, "Serial device %s Init succeded\n", opts.port);
		}
	}
	
	 // SPI
	if (display.oled_is_spi_proto(opts.oled))
	{
		// SPI change parameters to fit to your LCD
		if ( !display.init(OLED_SPI_DC,OLED_SPI_RESET,OLED_SPI_CS, opts.oled) )
			exit(EXIT_FAILURE);
	}
	else
	{
		// I2C change parameters to fit to your LCD
		if ( !display.init(OLED_I2C_RESET,opts.oled) )
			exit(EXIT_FAILURE);
	}

	display.begin();
	display.clearDisplay();
	
	// show 
  display.display(); 

 	log_syslog(stdout, "Inits succeded, entering Main loop\n");
 	
  if (opts.daemon)
  {
	 	log_syslog(stdout, "Starting as a daemon\n");
  	daemonize();
  }
	

	// Do while not end
	while ( ! g_exit_pgm ) 
	{
		// by default no frame
		frame_ok = false;
	
		// Grab from network
		if (opts.mode == MODE_NET )
		{
			// Get frame from network
			frame_ok =  tlf_get_frame(true);
		}
		else
		{
			// loop from serial port until frame ok
			while ( ! frame_ok)
			{
				// Read from serial port
				n = read(g_fd_teleinfo, &c, 1);
			
				if (n == 0)
					fatal("nothing to read");
				else if (errno == EINTR  )
					break;
				else if ( n < 0 )
					fatal("read failed: %s", strerror(errno));

				//log_syslog(stdout, "%c", c);
				//printf("%c",c);

				// What we received ?
				switch (c)
				{
					// start of frame ???
					case  STX:
						// Clear buffer, begin to store in it
						rcv_idx = 0;
						bzero(rcv_buff, TELEINFO_BUFSIZE);
						rcv_buff[rcv_idx++]=c;
					break;
						
					// End of frame ?
					case  ETX:
						// We had STX ?
						if ( rcv_idx )
						{
							// Store in buffer and proceed
							rcv_buff[rcv_idx++]=c;
							
							// clear the end of buffer (paranoia inside)
							bzero(&rcv_buff[rcv_idx], TELEINFO_BUFSIZE-rcv_idx);
							
							// Is this frame valid ?
							if ( (length = tlf_check_frame(rcv_buff)) > 0 )
							{
								frame_ok = true;
							}
						}
						// May be begin of the program or other problem.
						else
						{
							rcv_idx = 0;
							bzero(rcv_buff, TELEINFO_BUFSIZE);
						}
					break;
					
					// other char ?
					default:
					{
						// If we are in a frame, store data recceived
						if (rcv_idx)
						{
							// If buffer is not full
							if ( rcv_idx < TELEINFO_BUFSIZE)
							{
								// Store data recceived
								rcv_buff[rcv_idx++]=c;
							}
							else
							{
								// clear buffer & restart
								rcv_idx=0;
								bzero(rcv_buff, TELEINFO_BUFSIZE);
							}
						}
					}
					break;
				}
			}
		} // while not frame ok from serial
		
		// here we received a frame, even serial or from network
		// If frame  ok
		if ( frame_ok )
		{
			//char oled_buff[1024];
			int percent=0;
			
			t = time(NULL);
			tmp = localtime(&t);
			if (tmp) 
			{
				if (strftime(time_str, sizeof(time_str), "%d %b %Y %T" , tmp) == 0) 
					strcpy( time_str, "No Time");
			}

			// good full frame received, do whatever you want here
			//fprintf(stdout, "==========================\nTeleinfo Frame of %d char\n%s\n==========================%s\n",
			//								strlen(rcv_buff), time_str, rcv_buff );

			//sprintf( oled_buff, "Creuses %09lu\nPleines %09lu\n%d W   %d \n%s\n",
			//					g_values.hchp, g_values.hchc, g_values.papp, (100*g_values.iinst)/g_values.isousc, time_str);
			//fprintf(stdout, oled_buff);
			
			display.clearDisplay();   // clears the screen and buffer	display.setTextSize(1);
			display.setTextColor(WHITE);
			display.setCursor(0,0);

			// Percent of total power 
			percent = (100.0 * g_values.iinst) / g_values.isousc ;

			
			if (display.height() == 32 )
			{
				if (g_values.ptec == PTEC_HP )
					display.setTextColor(BLACK, WHITE); // 'inverted' text
			
				display.print("Pleines ");
				display.printf("%09ld\n", g_values.hchp);
				display.setTextColor(WHITE); // normaltext
				
				if (g_values.ptec == PTEC_HC )
					display.setTextColor(BLACK, WHITE); // 'inverted' text
					
				display.print("Creuses ");
				display.printf("%09ld\n", g_values.hchc);
				display.setTextColor(WHITE); // normaltext

				// Calculate Bargraph display
				
				//display.setTextColor(BLACK, WHITE); // 'inverted' text
				//skip seconds
				time_str[17] = 0x00;
				display.printf("%d W %d%%  %3d A\n%s", g_values.papp, percent, g_values.iinst, time_str);
				display.drawVerticalBargraph(114,0,12,32,1, percent);
				display.display();
				display.setTextColor(BLACK, WHITE); // 'inverted' text
			}
			else
			{
				if (g_values.ptec == PTEC_HP )
					display.setTextColor(BLACK, WHITE); // 'inverted' text
			
				display.setTextSize(2); 

				display.printf("%09ld\n", g_values.hchp);
				display.setTextColor(WHITE); // normaltext
				
				if (g_values.ptec == PTEC_HC )
					display.setTextColor(BLACK, WHITE); // 'inverted' text
					
				display.printf("%09ld\n", g_values.hchc);
				display.setTextColor(WHITE); // normaltext

				
				//display.setTextColor(BLACK, WHITE); // 'inverted' text
				display.setTextSize(1); 
				display.printf("%d W %d%%  %3d A\n", g_values.papp, percent, g_values.iinst);
				display.printf("%s", time_str);

				// Calculate Bargraph display
				// Percent of total power 
				display.drawHorizontalBargraph(0, 49,128,14,1, percent);

				display.display();
				display.setTextColor(BLACK, WHITE); // 'inverted' text
			}

		}

		// We want to display results ?
		if (opts.verbose)
		{
			if ( (n = write(STDOUT_FILENO, &c, 1)) <= 0 )
				fatal("write to stdout failed: %s", strerror(errno));
		}
	}
	

  log_syslog(stderr, "Program terminated\n");
  
  clean_exit(EXIT_SUCCESS);
  
  // avoid compiler warning
  return (0);
}