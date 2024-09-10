int parse_args(int argc, char **argv, arguments_t *a) {

  int i;
  time_t systime;
  unsigned long long curr_time;
 
#ifndef _MSC_VER
  char *ep;
#endif

  unsigned int tmp_max_sb_len;
  unsigned int tmp_es_len;
  char *tmp_addr;
  unsigned char fec_enc;
  char *tmp_base_dir;
  char *tmp_repair;
  BOOL repair;
  unsigned long long tmp_tsi;
  unsigned long long duration;
  char *loss_ratio2;
  div_t div_max_k;
  div_t div_max_n;
 
  time(&systime);
  curr_time = systime + 2208988800U;
  
  tmp_tsi = DEF_TSI;					 /* transport session identifier */
  tmp_max_sb_len = 0;
  tmp_es_len = 0;
  tmp_addr = NULL;
  fec_enc = DEF_FEC;
  tmp_base_dir = NULL;
  tmp_repair = NULL;
  repair = FALSE;
  loss_ratio2 = NULL;
  duration = 0;

  a->toi = 0;							/* transport object identifier */
  a->cont = FALSE;					 /* continuous transmission */
  a->rx_automatic = FALSE;				 /* download files defined in IDT automatically */
  a->rx_object = FALSE;
  a->file_table_output = FALSE;
  a->log_fd = -1;
  a->complete_fdt = 0;
  a->send_session_close_packets = 1;
  a->name_incomplete_objects = FALSE;

#ifdef _MSC_VER
  a->open_file = FALSE;					 /* open received file automatically */
#endif

  memset(a->sdp_file, 0, MAX_PATH_LENGTH);
  memset(a->file_path, 0, MAX_PATH_LENGTH);  /* file(s) or directory to send */
  memset(a->fdt_file, 0, MAX_PATH_LENGTH);
  strcpy(a->fdt_file, DEF_FDT);				 /* fdt file (fdt based send) */
 
  a->alc_a.cc_id = DEF_CC;				/* congestion control */
  a->alc_a.mode = RECEIVER;				/* sender or receiver? */			
  a->alc_a.port = DEF_MCAST_PORT;				 /* local port number for base channel */
  a->alc_a.nb_channel = DEF_NB_CHANNEL;			 /* number of channels */
  a->alc_a.intface = NULL;					 /* interface */
  a->alc_a.intface_name = NULL;				 /* interface name/index for IPv6 multicast join */
  a->alc_a.addr_family = DEF_ADDR_FAMILY;
  a->alc_a.addr_type = 0;
  a->alc_a.es_len = DEF_SYMB_LENGTH;				 /* encoding symbol length */
  a->alc_a.max_sb_len = DEF_MAX_SB_LEN;			 /* source block length */
  a->alc_a.tx_rate = DEF_TX_RATE;				 /* transmission rate in kbit/s */
  a->alc_a.ttl = DEF_TTL;					 /* time to live  */
  a->alc_a.nb_tx = DEF_TX_NB;					 /* nb of time to send the file/directory */
  a->alc_a.simul_losses = FALSE;				 /* simulate packet losses */
  a->alc_a.loss_ratio1 = P_LOSS_WHEN_OK;
  a->alc_a.loss_ratio2 = P_LOSS_WHEN_LOSS;
  a->alc_a.fec_ratio = DEF_FEC_RATIO;				 /* FEC ratio percent */	
  a->alc_a.fec_enc_id = DEF_FEC_ENC_ID;			 /* FEC Encoding */
  a->alc_a.fec_inst_id = DEF_FEC_INST_ID; 
  a->alc_a.rx_memory_mode = 1;
  a->alc_a.verbosity = 1;  
  a->alc_a.use_fec_oti_ext_hdr = 0;				 /* include fec oti extension header to flute header */
  a->alc_a.encode_content = 0;				 /* encode content */
  a->alc_a.src_addr = NULL;
  a->alc_a.optimize_tx_rate = FALSE;
  a->alc_a.calculate_session_size = FALSE;
  a->alc_a.half_word = FALSE;
  a->alc_a.accept_expired_fdt_inst = FALSE;

#ifdef SSM
  a->alc_a.use_ssm = FALSE;					 /* use source specific multicast */
#endif
  
  if(strstr(argv[0], "repair_sender")) {
    a->alc_a.mode = SENDER;
    repair = TRUE;
  }
  else {
    a->alc_a.mode = RECEIVER;
  }

  for(i = 1; i < argc ; i++) {
    if(argv[i][0] == '-') {
      
      switch(argv[i][1])
	{
	case 'A':  /* automatic download */
	  if(strlen(argv[i]) > 2) {
	    return -1;
	  }
	  a->rx_automatic = TRUE;
	  break;
	case 'a':  /* address family */
	  if(strlen(argv[i]) > 3) {
	    if(!(strcmp(&argv[i][3], "IPv4"))) {
	      a->alc_a.addr_family = PF_INET;
	    }
	    else if(!(strcmp(&argv[i][3], "IPv6"))) {
	      a->alc_a.es_len = MAX_SYMB_LENGTH_IPv6_FEC_ID_0_3_130;
	      a->alc_a.addr_family = PF_INET6;
	    }
	  }
	  else {
	    return -1;
	  }
	  break;
	case 'B':  /* base directory for downloaded files */
	  if(strlen(argv[i]) > 3) {
	    tmp_base_dir = &argv[i][3];
	  }
	  else {
	    return -1;
	  }
	  break;
	case 'b':  /* rx_memory_mode */
	  if(strlen(argv[i]) > 3) {
	    a->alc_a.rx_memory_mode = (unsigned char)atoi(&argv[i][3]);

	    if(a->alc_a.rx_memory_mode > 2) {
	      printf("Possible values for option -b are: 0, 1, or 2\n");
	      fflush(stdout);
	      return -1;
	    }
	  }
	  else {                         
	    return -1;
	  }
	  break;
	case 'C':  /* Continuous transmission */
	  if(strlen(argv[i]) > 2) {
	    return -1;
	  }
	  a->cont = TRUE;
	  break;
	case 'c':  /* number of channels */
	  if(strlen(argv[i]) > 3) {
	    a->alc_a.nb_channel = (unsigned char)atoi(&argv[i][3]);
	    
	    if(a->alc_a.nb_channel > MAX_CHANNELS_IN_SESSION) {
	      printf("Channel number set to maximum value: %i\n", MAX_CHANNELS_IN_SESSION);
	      a->alc_a.nb_channel = MAX_CHANNELS_IN_SESSION;
	    }
	    else if(a->alc_a.nb_channel == 0) {
	      printf("Channel number set to 1\n");
	      a->alc_a.nb_channel = 1;
	    }
	  }
	  else {
	    return -1;
	  }
	  break;
	case 'D':  /* session duration time */
	  if(strlen(argv[i]) > 3) {
#ifdef _MSC_VER			  
	    duration = _atoi64(&argv[i][3]);
	    
	    if(duration > (unsigned long long)0xFFFFFFFFFFFFFFFF) {
	      printf("Duration: %I64u too big (max=%I64u)\n", duration, (unsigned long long)0xFFFFFFFFFFFFFFFF);
	      fflush(stdout);
	      return -1;
	    }
#else
	    duration = strtoull(&argv[i][3], &ep, 10);
	    
	    if(&argv[i][3] == '\0' || *ep != '\0') {
	      printf("Duration not a number\n");
	      fflush(stdout);
	      return -1;
	    }
	    
	    if(errno == ERANGE && duration == 0xFFFFFFFFFFFFFFFFULL) {
	      printf("Duration too big for unsigned long long (64 bits)\n");
	      fflush(stdout);
	      return -1;
	    }
#endif	
	  }
	  else {
	    return -1;
	  }
	  break;
	case 'd':  /* sdp file */
	  if(strlen(argv[i]) <= 3) {
		return -1;
	  }
	  else if(strlen(argv[i]) >= MAX_PATH_LENGTH) {
	    printf("\nFile path for SDP file too long\n");
		return -1;
	  }
	  else {
	    memset(a->sdp_file, 0, MAX_PATH_LENGTH);
	    strcpy(a->sdp_file, &argv[i][3]);
	  }
	  break;
	case 'E':  /* Accept Expired FDT Instances */
	  if(strlen(argv[i]) > 2) {
	    return -1;
	  }
	  a->alc_a.accept_expired_fdt_inst = TRUE;
	  break;
	case 'e':  /* Use fec oti extension header */
	  if(strlen(argv[i]) > 3) {
	    a->alc_a.use_fec_oti_ext_hdr = (unsigned char)atoi(&argv[i][3]);
	    
	    if(a->alc_a.use_fec_oti_ext_hdr > 1) {
	      printf("Possible values for option -e are: 0, or 1\n");
	      fflush(stdout);
	      return -1;
	    }
	  }
	  else {                         
	    return -1;
	  }
	  break;
	case 'F':  /* files or directories to send/receive */
	  if(strlen(argv[i]) <= 3) {
		return -1;
	  }
	  else if(strlen(argv[i]) >= MAX_PATH_LENGTH) {
	    printf("\nFile path for files or directories too long\n");
		return -1;
	  }
	  else {
	    memset(a->file_path, 0, MAX_PATH_LENGTH);
	    strcpy(a->file_path, &argv[i][3]);
	  }
	  memset(a->fdt_file, 0, MAX_PATH_LENGTH);
	  break;
	case 'f':  /* fdt based send */
	  if(strlen(argv[i]) <= 3) {
		return -1;
	  }
	  else if(strlen(argv[i]) >= MAX_PATH_LENGTH) {
	    printf("\nFile path for FDT file too long\n");
		return -1;
	  }
	  else {
	    memset(a->fdt_file, 0, MAX_PATH_LENGTH);
	    strcpy(a->fdt_file, &argv[i][3]);
	  }
	  memset(a->file_path, 0, MAX_PATH_LENGTH);
	  break;
	case 'G':  /* Calculate session size but do not send anything */
		if(strlen(argv[i]) > 2) {			
			return -1;			
		}	
		a->alc_a.calculate_session_size = TRUE;          
		break;
	case 'H':  /* use half-word */
	  if(strlen(argv[i]) > 2) {
	    return -1;
	  }
	  a->alc_a.half_word = TRUE;
	  break;
	case 'h':  /* help/usage */
	  return -1;
	  break;
	case 'I':  /* local interface name/index for IPv6 multicast join */
	  if(strlen(argv[i]) > 3) {
	    a->alc_a.intface_name = &argv[i][3];
	  }
	  else {
	    return -1;
	  }
	  break;
	case 'i':  /* local interface to use */
	  if(strlen(argv[i]) > 3) {
	    a->alc_a.intface = &argv[i][3];
	  }
	  else {
	    return -1;
	  }
	  break;
	//Malek El Khatib 14.05.2014
	//Start
	//User could customize name of output log file
	case 'J':  /* local interface to use */
		if(strlen(argv[i]) <= 3) {
			return -1;
		}
		else if(strlen(argv[i]) >= MAX_PATH_LENGTH) {
			printf("\nFile path for log file too long\n");
			return -1;
		}
		else {
			logFile=&argv[i][3];
		}
		break;
	//End
    case 'K':  /* 'repair_sender.conf' */
	  if(strlen(argv[i]) <= 3) {
		return -1;
	  }
	  else if(strlen(argv[i]) >= MAX_PATH_LENGTH) {
		printf("\nFile path for repair sender configuration file too long\n");
		return -1;
	  }
	  else {
		tmp_repair = &argv[i][3];
	  }
	  break;
	case 'k':  /* Complete FDT */
	  if(strlen(argv[i]) > 3) {
            a->complete_fdt = (unsigned short)atoi(&argv[i][3]);
          }
          else {
            return -1;
          }
          break;
	case 'L':  /* sbl length */
	  if(strlen(argv[i]) > 3) {
	    tmp_max_sb_len = (unsigned int)atoi(&argv[i][3]);
	  }
	  else {
	    return -1;
	  }
	  break;
	case 'l':  /*  encoding symbol length */
	  if(strlen(argv[i]) > 3) {
	    tmp_es_len = (unsigned short)atoi(&argv[i][3]);						
	  }
	  else {
	    return -1;
	  }
	  break;
#ifdef SSM
	case 'M':  /* use source specific multicast */
	  if(strlen(argv[i]) > 2) {
	    return -1;
	  }
	  a->alc_a.use_ssm = TRUE;
	  break;
	case 'm':  /* Multicast group for base channel */
	  if(strlen(argv[i]) > 3) {
	    tmp_addr = &argv[i][3];
	  }
	  else {
	    return -1;
	  }
	  break;
#endif
	case 'N':
	  if(strlen(argv[i]) > 2) {
	    return -1;
	  }
	  a->name_incomplete_objects = TRUE;
	  break;
	case 'n':  /* tx loops */
	  if(strlen(argv[i]) > 3) {
	    a->alc_a.nb_tx = (unsigned short)atoi(&argv[i][3]);
	  }
	  else {
	    return -1;
	  }
	  break;
#ifdef _MSC_VER
	case 'O':  /* automatic opening */
	  if(strlen(argv[i]) > 2) {
	    return -1;
	  }
	  a->open_file = TRUE;
	  break;
#endif
	case 'o':  /* toi */
	  if(strlen(argv[i]) > 3) {
#ifdef _MSC_VER			  
	    a->toi = _atoi64(&argv[i][3]);
	    
	    if(a->toi > (unsigned long long)0xFFFFFFFFFFFFFFFF) {
	      printf("TOI: %I64u too big (max=%I64u)\n", a->toi, (unsigned long long)0xFFFFFFFFFFFFFFFF);
	      fflush(stdout);
	      return -1;
	    }
#else	    
	    a->toi = strtoull(&argv[i][3], &ep, 10);
	    
	    if(&argv[i][3] == '\0' || *ep != '\0') {
	      printf("TOI not a number\n");
	      fflush(stdout);
	      return -1;
	    }
	    
	    if(errno == ERANGE && a->toi == 0xFFFFFFFFFFFFFFFFULL) {
	      printf("TOI too big for unsigned long long (64 bits)\n");
	      fflush(stdout);
	      return -1;
	    }
#endif
	    a->rx_object = 1;
	  }
	  else {
	    return -1;
	  }
	  break;
	case 'P':  /* simulate packet losses */
	  if(strlen(argv[i]) >= 2) {
	    a->alc_a.simul_losses = TRUE;
	  }
	  if(strlen(argv[i]) > 3) {
	    a->alc_a.loss_ratio1 = atof(strtok(&argv[i][3], ","));
	    loss_ratio2 = strtok(NULL, "\0");
	    if(loss_ratio2 == NULL) {
	      return -1;
	    }
	    a->alc_a.loss_ratio2 = atof(loss_ratio2);
	  }
	  if(strlen(argv[i]) == 3) {
	    return -1;
	  }
	  break;
	case 'p':  /* Port number for base channel*/
	  if(strlen(argv[i]) > 3) {
	    a->alc_a.port = &argv[i][3];

	    assert(atoi(a->alc_a.port) > 0);
	    assert(atoi(a->alc_a.port) <= 0xFFFF);
	  }
	  else {
	    return -1;
	  }
	  break;
	case 'q':  /* Send session close packets */
          if(strlen(argv[i]) > 3) {
            a->send_session_close_packets = atoi(&argv[i][3]);
          }
          else {
            return -1;
          }
          break;
	//Malek El Khatib 16.7.2014
	//Start
	case 'Q':  /* Send/Receive FDT after object */
	  if(strlen(argv[i]) > 2) {
	    return -1;
	  }
	  sendFDTAfterObj = TRUE;
	  break;
	//END
#ifdef USE_FILE_REPAIR
	case 'R':  /* 'apd.xml' or 'flute.conf' */
	  if(strlen(argv[i]) == 3) {
		return -1;
	  }
	  else if(strlen(argv[i]) >= MAX_PATH_LENGTH) {
		printf("\nFile path for repair configuration file too long\n");
		return -1;
	  }
	  else if(strlen(argv[i]) == 2) {
	    repair = TRUE;
	  }
	  else {
		repair = TRUE;
		tmp_repair = &argv[i][3];
	  }
	  break;
#endif
	case 'r':  /* Transmission rate in kbits/s */
	  if(strlen(argv[i]) > 3) {      
	    a->alc_a.tx_rate = (unsigned int)atoi(&argv[i][3]);
	  }
	  else {
	    return -1;
	  }
	  break;
	  
	case 'S':  /* sender */
	  if(strlen(argv[i]) > 2) {
	    return -1;
	  }
	  a->alc_a.mode = SENDER;
	  a->toi = FDT_TOI;
	  break;
	case 's':  /* first alc session identifier */
	  if(strlen(argv[i]) > 3) {
	    a->alc_a.src_addr = &argv[i][3];
	  }
	  else {
	    return -1;
	  }
	  break;
	case 'T':  /* ttl */
	  if(strlen(argv[i]) > 3) {
	    a->alc_a.ttl = (unsigned char)atoi(&argv[i][3]);
	  }
	  else {
	    return -1;
	  }
	  break;
	case 't':  /* second alc session identifier */
	  if(strlen(argv[i]) > 3) {
#ifdef _MSC_VER			  
	    tmp_tsi = _atoi64(&argv[i][3]);
#else	    
	    tmp_tsi = strtoull(&argv[i][3], &ep, 10);
	    
	    if(&argv[i][3] == '\0' || *ep != '\0') {                   
	      printf("TSI not a number\n");
	      fflush(stdout);
	      return -1;
	    }
	    
	    if(errno == ERANGE && tmp_tsi == 0xFFFFFFFFFFFFFFFFULL) {   
	      printf("TSI too big for unsigned long long (64 bits)\n");
	      fflush(stdout);
	      return -1;
	    }
#endif 
#ifdef _MSC_VER
	    if(tmp_tsi > (unsigned long long)0xFFFFFFFFFFFF) {
	      printf("TSI: %I64u too big (max=%I64u)\n", tmp_tsi, (unsigned long long)0xFFFFFFFFFFFF);
#else
	      if(tmp_tsi > 0xFFFFFFFFFFFFULL) {
		printf("TSI: %llu too big (max=%llu)\n", tmp_tsi, 0xFFFFFFFFFFFFULL);
#endif
		fflush(stdout);
		return -1;
	      }
	    }
	    else {
	      return -1;
	    }
	    break;
	  case 'U':  /* unicast address */                    
	    if(strlen(argv[i]) > 2) {
	      return -1;
	    }
	    a->alc_a.addr_type = 1;
	    break;
	  case 'V': /* redirect stderr and stdout into given file */
	    if (strlen(argv[i]) > 3) {
#ifdef _MSC_VER
	      a->log_fd = _open(&argv[i][3], _O_RDWR | _O_CREAT | _O_TRUNC, 0666);
#else 
	      a->log_fd = open(&argv[i][3], O_RDWR | O_CREAT | O_TRUNC, 0666);
#endif
	      
	      if(a->log_fd < 0) {
		
		printf("Log file: %s cannot be opened\n", &argv[i][3]);
		fflush(stdout);
		return -1;
	      }
	      
#ifdef _MSC_VER
	      _dup2(a->log_fd, _fileno(stdout));
	      _dup2(a->log_fd, _fileno(stderr));
#else
	      dup2(a->log_fd, fileno(stdout));
	      dup2(a->log_fd, fileno(stderr));
#endif
	    }
	    break;
	  case 'v':  /* verbosity level */
	    if(strlen(argv[i]) > 3) {
	      a->alc_a.verbosity = atoi(&argv[i][3]);
	      
	      if(a->alc_a.verbosity > 4) {
		printf("Possible values for option -v are: 0, 1, 2, 3, or 4\n");
		fflush(stdout);
		return -1;
	      }
	    }
	    else {
	      return -1;
	    }
	    break;
	  case 'W':  /* File table output */
	    if(strlen(argv[i]) > 2) {
	      return -1;
	    }
	    a->file_table_output = TRUE;
	    break;
	  case 'w':  /* congestion control */
	    if(strlen(argv[i]) > 3) {
	      a->alc_a.cc_id = (unsigned char)atoi(&argv[i][3]);
	      
	      if(a->alc_a.cc_id > 1) {
		printf("Possible values for option -w are: 0, or 1\n");
		fflush(stdout);
		return -1;
	      }
	    }
	    else {
	      return -1;
	    }
	    break;
	  case 'X':  /* FEC ratio percent */
	    if(strlen(argv[i]) > 3) {
	      a->alc_a.fec_ratio = (unsigned short)atoi(&argv[i][3]);
	    }
	    else {
	      return -1;
	    }
	    break;
	  case 'x':  /* fec encoding */
	    if(strlen(argv[i]) > 3) {
	      fec_enc = (unsigned char)atoi(&argv[i][3]);

	      if(fec_enc > 3) {
            printf("Possible values for option -x are: 0, 1, 2 or 3\n");
			fflush(stdout);
            return -1;
	      }
	    }
	    else {
	      return -1;
	    }
	    break;
		//Malek El Khatib 16.04.2014
		//START
		//Add file to indicate absolute sending times
	  case 'y':
		  if(strlen(argv[i]) <= 3) {
			  return -1;
		  }
		  else if(strlen(argv[i]) >= MAX_PATH_LENGTH) {
			  printf("\nFile path for input file too long\n");
			  return -1;
		  }
		  else {
			  sendingTimesFile=&argv[i][3];
		  }
		  break;
		//End
      //Indicate the number of es per packet. Zero indicates that file -y:str is used which determines the chunks to send at a time. Maximum data per packet will then be used
	  case 'Y':
		  if(strlen(argv[i]) > 3) {
			  numEncSymbPerPacket = strtoul(&argv[i][3], &ep, 10);
			  if(&argv[i][3] == '\0' || *ep != '\0') {                   
				  printf("Number of Encoding Symbols per packet is not a number or not a valid number\n");
				  fflush(stdout);
				  return -1;
			  }
		  }
		  else {
			  return -1;
		  }
		  break;
      //END
	  case 'Z':  /* optimize transmission rate (use more CPU) */
	    if(strlen(argv[i]) > 2) {
	      return -1;
	    }
	    a->alc_a.optimize_tx_rate = TRUE;
	    break;
	  case 'z':  /* encode content */
	    if(strlen(argv[i]) > 3) {
	      a->alc_a.encode_content = (unsigned char)atoi(&argv[i][3]);
	      
	      if(a->alc_a.encode_content > 3) {
		printf("Possible values for option -z are: 0, 1, 2 or 3\n");
		fflush(stdout);
		return -1;
	      }
	    }
	    else {
	      return -1;
	    }
	    break;
	  default:
	    return -1;
	    break;
	  }
	}
      else {
	return -1;
      }
    }
    
    if(tmp_addr == NULL) {
      if(a->alc_a.addr_family == PF_INET) {
	tmp_addr = DEF_MCAST_IPv4_ADDR;
      }
      else if(a->alc_a.addr_family == PF_INET6) {
	tmp_addr = DEF_MCAST_IPv6_ADDR;
      }
    }
    a->alc_a.addr = tmp_addr;
    
    if(fec_enc == 1) {
      a->alc_a.fec_enc_id = SIMPLE_XOR_FEC_ENC_ID;
      
      if(a->alc_a.addr_family == PF_INET) {
		a->alc_a.es_len = MAX_SYMB_LENGTH_IPv4_FEC_ID_2_128_129;
      }
      else if(a->alc_a.addr_family == PF_INET6) {
		a->alc_a.es_len = MAX_SYMB_LENGTH_IPv6_FEC_ID_2_128_129;
      }
    }
    else if(fec_enc == 2) {
      a->alc_a.fec_enc_id = SB_SYS_FEC_ENC_ID;
      a->alc_a.fec_inst_id = REED_SOL_FEC_INST_ID;
      
      if(a->alc_a.addr_family == PF_INET) {
		a->alc_a.es_len = MAX_SYMB_LENGTH_IPv4_FEC_ID_2_128_129;
      }
      else if(a->alc_a.addr_family == PF_INET6) {
		a->alc_a.es_len = MAX_SYMB_LENGTH_IPv6_FEC_ID_2_128_129;
      }
    }
    else if(fec_enc == 3) {
      a->alc_a.fec_enc_id = RS_FEC_ENC_ID;
    }
    
    if(a->alc_a.mode == RECEIVER) {
      a->alc_a.tsi = tmp_tsi;
      
      memset(a->alc_a.base_dir, 0, MAX_PATH_LENGTH);
      
      if(tmp_base_dir == NULL) {
	    strcpy(a->alc_a.base_dir, DEF_BASE_DIR);
      }
      else {
	    strcpy(a->alc_a.base_dir, tmp_base_dir);
      }
      
      a->alc_a.start_time = curr_time;

	  if(duration == 0) {
		  a->alc_a.stop_time = curr_time + DEF_RECEIVER_TIMEOUT;
	  }
	  else {
		  a->alc_a.stop_time = curr_time + duration;
	  }
      
#ifdef USE_FILE_REPAIR
      if(repair) {
	    memset(a->repair, 0, MAX_PATH_LENGTH);
	
	    if(tmp_repair == NULL) {
	      strcpy(a->repair, DEF_APD_CONF_FILE);
	    }
	    else {
	     strcpy(a->repair, tmp_repair);
	    }
      }
      else {
	    memset(a->repair, 0, MAX_PATH_LENGTH);
      }
#endif
      
    }
    else {
      if(((a->alc_a.half_word == FALSE) && (tmp_tsi > 0xFFFFFFFF))) {
	    printf("TSI too big for unsigned long (32 bits)\n");
	    fflush(stdout);
	    return -1;
      }
      else {
	    a->alc_a.tsi = tmp_tsi;
      }
      
      memset(a->alc_a.base_dir, 0, MAX_PATH_LENGTH);
      
      if(tmp_base_dir != NULL) {
	    strcpy(a->alc_a.base_dir, tmp_base_dir);
      }
      
      a->alc_a.start_time = curr_time;

	  if(duration == 0) {
        a->alc_a.stop_time = curr_time + DEF_SESSION_DURATION;
	  }
	  else {
        a->alc_a.stop_time = curr_time + duration;
	  }

#ifdef USE_FILE_REPAIR
      if(repair) {
	    memset(a->repair, 0, MAX_PATH_LENGTH);
	
	    if(tmp_repair == NULL) {
	      strcpy(a->repair, DEF_FLUTE_CONF_FILE);
	    }
	    else {
	     strcpy(a->repair, tmp_repair);
	    }
      }
      else {
	    memset(a->repair, 0, MAX_PATH_LENGTH);
      }
#else
      if(repair) {
	    memset(a->repair, 0, MAX_PATH_LENGTH);
	
	    if(tmp_repair == NULL) {
	      strcpy(a->repair, DEF_REPAIR_SENDER_CONF_FILE);
	    }
	    else {
	      strcpy(a->repair, tmp_repair);
	    }
      }
      else {
	    memset(a->repair, 0, MAX_PATH_LENGTH);
      }
#endif
    }
    
    if(tmp_max_sb_len != 0) {
      if(a->alc_a.fec_enc_id == COM_NO_C_FEC_ENC_ID) {
	
	if(tmp_max_sb_len > MAX_SB_LEN_NULL_FEC) {
	  printf("Maximum source block length set to maximum value: %i\n", MAX_SB_LEN_NULL_FEC);
	  fflush(stdout);
	  tmp_max_sb_len = MAX_SB_LEN_NULL_FEC;
	}
	a->alc_a.max_sb_len = tmp_max_sb_len;
      }
      
      else if(a->alc_a.fec_enc_id == SIMPLE_XOR_FEC_ENC_ID) {
	if(tmp_max_sb_len > MAX_SB_LEN_SIMPLE_XOR_FEC) {
	  printf("Maximum source block length set to maximum value: %i\n", MAX_SB_LEN_SIMPLE_XOR_FEC);
	  fflush(stdout);
	  tmp_max_sb_len = MAX_SB_LEN_SIMPLE_XOR_FEC;
	}
	a->alc_a.max_sb_len = tmp_max_sb_len;
      }
      
      else if(((a->alc_a.fec_enc_id == RS_FEC_ENC_ID) || ((a->alc_a.fec_enc_id == SB_SYS_FEC_ENC_ID)
	       && (a->alc_a.fec_inst_id == REED_SOL_FEC_INST_ID)))) {
	
	div_max_n = div((tmp_max_sb_len * (100 + a->alc_a.fec_ratio)), 100);
	
	if(div_max_n.quot > MAX_N_REED_SOLOMON) {
	  
	  div_max_k = div((MAX_N_REED_SOLOMON * 100), (100 + a->alc_a.fec_ratio));
	  
	  printf("Maximum source block length set to maximum value: %i\n", div_max_k.quot);
	  fflush(stdout);
	  tmp_max_sb_len = div_max_k.quot;
	}
	a->alc_a.max_sb_len = tmp_max_sb_len;
      }
    }
    
    if(tmp_es_len != 0) {
      if(a->alc_a.addr_family == PF_INET) {
	if(((a->alc_a.fec_enc_id == COM_NO_C_FEC_ENC_ID)
	    || (a->alc_a.fec_enc_id == RS_FEC_ENC_ID)
	    || (a->alc_a.fec_enc_id == COM_FEC_ENC_ID))) {
	  if(tmp_es_len > MAX_SYMB_LENGTH_IPv4_FEC_ID_0_3_130) {
	    printf("Encoding symbol length set to maximum value: %i\n",
		   MAX_SYMB_LENGTH_IPv4_FEC_ID_0_3_130);
	    fflush(stdout);
	    tmp_es_len = MAX_SYMB_LENGTH_IPv4_FEC_ID_0_3_130;
	  }
	}
	else if(((a->alc_a.fec_enc_id == SIMPLE_XOR_FEC_ENC_ID) ||
		 (a->alc_a.fec_enc_id == SB_LB_E_FEC_ENC_ID) ||
		 (a->alc_a.fec_enc_id == SB_SYS_FEC_ENC_ID))) {
	  if(tmp_es_len > MAX_SYMB_LENGTH_IPv4_FEC_ID_2_128_129) {
	    printf("Encoding symbol length set to maximum value: %i\n",
		   MAX_SYMB_LENGTH_IPv4_FEC_ID_2_128_129);
	    fflush(stdout);
	    tmp_es_len = MAX_SYMB_LENGTH_IPv4_FEC_ID_2_128_129;
	  }	
	}
      }
      else if(a->alc_a.addr_family == PF_INET6) {	
	if(((a->alc_a.fec_enc_id == COM_NO_C_FEC_ENC_ID)
	    || (a->alc_a.fec_enc_id == RS_FEC_ENC_ID)
	    || (a->alc_a.fec_enc_id == COM_FEC_ENC_ID))) {
	  if(tmp_es_len > MAX_SYMB_LENGTH_IPv6_FEC_ID_0_3_130) {
	    printf("Encoding symbol length set to maximum value: %i\n",
		   MAX_SYMB_LENGTH_IPv6_FEC_ID_0_3_130);
	    fflush(stdout);
	    tmp_es_len = MAX_SYMB_LENGTH_IPv6_FEC_ID_0_3_130;
	  }
	}
	else if(((a->alc_a.fec_enc_id == SIMPLE_XOR_FEC_ENC_ID) ||
		 (a->alc_a.fec_enc_id == SB_LB_E_FEC_ENC_ID) ||
		 (a->alc_a.fec_enc_id == SB_SYS_FEC_ENC_ID))) {
	  if(tmp_es_len > MAX_SYMB_LENGTH_IPv6_FEC_ID_2_128_129) {
	    printf("Encoding symbol length set to maximum value: %i\n",
		   MAX_SYMB_LENGTH_IPv6_FEC_ID_2_128_129);
	    fflush(stdout);
	    tmp_es_len = MAX_SYMB_LENGTH_IPv6_FEC_ID_2_128_129;
	  }	
	}
      }
      
      a->alc_a.es_len = tmp_es_len;
    }

    if(((((a->rx_automatic == TRUE) || (a->alc_a.mode == SENDER)))
	&& (a->file_table_output == TRUE))) {
      a->alc_a.verbosity = -1;
    }
    
    return 0;
  }