int main(int argc, char** argv)
{
	char	line[300];
	char action[16];
	int i;
	//printf("start.......:%s\n",argv[1]);
    #if 0
    if(strcmp(argv[1],"firewall"))
{
    printf("******************\n");
    for(i=0;i<argc;i++)
    {
        printf("%s ",argv[i]);
    }
    printf("\n***************\n");
 }
   #endif	
	
	
	if ( !apmib_init()) {
		printf("Initialize AP MIB failed !\n");
		return -1;
	}
	apmib_initialized = 1;
	memset(line,0x00,300);
	
	if(argv[1] && (strcmp(argv[1], "init")==0)){
#if defined(CONFIG_RTL_ULINKER)
  #if defined(CONFIG_RTL_ULINKER_WLAN_DELAY_INIT)
	int ulinker_auto = 0;
	apmib_get(MIB_ULINKER_AUTO,  (void *)&ulinker_auto);
	if (ulinker_auto == 0)
		system("echo \"wlan 1\" > /proc/wlan_init");
  #endif

	if (strcmp(argv[3], "all")==0) {
		ulinker_bootup();
	}

#elif defined(CONFIG_POCKET_ROUTER_SUPPORT)
	pocketAP_bootup();
#endif

#ifdef CONFIG_POCKET_AP_SUPPORT
		i=BRIDGE_MODE;
		apmib_set(MIB_OP_MODE,(void *)&i);
		apmib_get(MIB_DHCP, (void *)&i);	//for FC, dhcp server not allowed when client
		if( i > DHCP_CLIENT )	i=0;
		apmib_set(MIB_DHCP, (void *)&i);	//0:DHCP_DISABLED
		i = 0xc0a801fa;
		apmib_set(MIB_IP_ADDR, (void *)&i);	//for FC, default IP to 192.168.1.250
#endif
		setinit(argc,argv);

#if defined(CONFIG_RTL_ULINKER_WLAN_DELAY_INIT)
	if (ulinker_auto == 1)
		ulinker_wlan_init();
#endif
		return 0;
	} else if(argv[1] && (strcmp(argv[1], "br")==0)){
		for(i=0;i<argc;i++){
			if( i>2 )
				string_casecade(line, argv[i]);
		}
		setbridge(line);
	}
#ifdef   HOME_GATEWAY	
	else if(argv[1] && (strcmp(argv[1], "firewall")==0)){		
		if(argv[2] && (strcmp(argv[2], "Send_GARP")==0))	//it will be call by set_staticIP function
		{
			#ifdef SEND_GRATUITOUS_ARP
			sendArp();
			#endif
		}
		else
		{
			setFirewallIptablesRules(argc,argv);
		}
	}
	else if(argv[1] && (strcmp(argv[1], "wlanapp")==0)){
		for(i=0;i<argc;i++){
			if( i>2 )
				string_casecade(line, argv[i]);
			if(i==2)
				sprintf(action, "%s",argv[i]); 
		}
		setWlan_Applications(action, line);
	}else if(argv[1] && (strcmp(argv[1], "disc")==0)){
		sprintf(line, "%s", argv[2]);
#ifdef MULTI_PPPOE
		if(argv[3])
			wan_disconnect(line,argv[3]);
		else 
			wan_disconnect(line,"NOMULPPPOE");
#else
		wan_disconnect(line);
#endif
	}else if(argv[1] && 
		((strcmp(argv[1], "conn")==0)||(strcmp(argv[1], "renew")==0))){
		
		if(argc < 4){
			printf("sysconf conn Invalid agrments!\n");
			return 0;
		}
		sprintf(action, "%s",argv[3]);
		for(i=0;i<argc;i++){
				if( i>2 )
					string_casecade(line, argv[i]);
			}
		if((strcmp(argv[1], "renew")==0)&&!strcmp(argv[2],"dhcp") &&!wan_dhcpcNeedRenewConn(action,line))
		{
			return 0;
		}
			
#if defined(CONFIG_DYNAMIC_WAN_IP)
		if((!strcmp(argv[2], "dhcp"))&&(isFileExist(TEMP_WAN_CHECK))){
			RunSystemCmd(TEMP_WAN_DHCP_INFO, "echo", line, NULL_STR);
		}
#endif

#if defined(CONFIG_RTL_ULINKER)
	/* notice ulinker_process to reset domain name query */
	system("echo 1 > /var/ulinker_reset_domain");
#endif
		
#if defined(CONFIG_DOMAIN_NAME_QUERY_SUPPORT)
		if(!strcmp(action, "br0"))
			wan_connect_pocket(action, line);
		else
		wan_connect(action, line);
#else
		wan_connect(action, line);
#endif
	}else if(argv[1] && (strcmp(argv[1], "pppoe")==0)){
		Init_Internet(argc,argv);
	}else if(argv[1] && (strcmp(argv[1], "pptp")==0)){
		Init_Internet(argc,argv);
	}else if(argv[1] && (strcmp(argv[1], "l2tp")==0)){
		Init_Internet(argc,argv);
	}else if(argv[1] && (strcmp(argv[1], "setQos")==0)){
		Init_QoS(argc,argv);
	}else if(argv[1] && (strcmp(argv[1], "dhcpd")==0)){
		sprintf(action, "%s",argv[2]);
		start_lan_dhcpd(action);
	}
#if defined(CONFIG_DOMAIN_NAME_QUERY_SUPPORT)	
	else if(argv[1] && (strcmp(argv[1], "upnpd")==0)){
		if(argc < 4){
			printf("sysconf upnpd Invalid agrments!\n");
			return 0;
	}
		start_upnpd(atoi(argv[2]),atoi(argv[3]));
	} 
#endif	

//### add by sen_liu 2011.4.21 sync the system log update (enlarge from 1 pcs to 8 pcs) to	SDKv2.5 from kernel 2.4
#if defined(RINGLOG)
	else if(argv[1] && (strcmp(argv[1], "log")==0)){
		if (argc == 6 && !strcmp(argv[2], "-s") && !strcmp(argv[4], "-b"))
		{
			system("killall syslogd >/dev/null 2>&1");
			system("rm /var/log/log_split >/dev/null 2>&1");
			sprintf(line, "echo %s > /var/log/log_split", argv[5]);
			system(line);
			RunSystemCmd(NULL_FILE, "syslogd", "-L", "-s", argv[3], "-b", argv[5], NULL_STR);
			fprintf(stderr, "syslog will use %dKB for log(%s rotate, 1 original, %sKB for each).\n",
				atoi(argv[3]) * ((atoi(argv[5]))+1), argv[5], argv[3]);
		}
	/*
		else if (argc == 4 && !strcmp(argv[2], "-R"))
		{
			RunSystemCmd(NULL_FILE, "killall syslogd", NULL_STR);
			RunSystemCmd(NULL_FILE, "syslogd", "-L", "-R", argv[3], NULL_STR);
		}
	*/
		else
		{
			fprintf(stderr, "usage:\n");
			fprintf(stderr, "sysconf log -s size -b number-of-rotate-backup\n");
			//fprintf(stderr, "sysconf log -R IP\n");
		}
	}
#endif
//### end
	
#endif	
	
//#ifdef CONFIG_POCKET_ROUTER_SUPPORT
//	system("boa");
//#endif		
	return 0;
}