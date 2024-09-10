void ACConfig(instance_parameter *ins_para,struct list *lpublic,struct list *lwcontrol,struct list *lwlan)
{
	int ret = 0; 
    int flag = 1;
	char *endptr = NULL; 
    char mtu[20] = { 0 };
    char log_stat[20] = { 0 };
    char log_size[20] = { 0 };
	char ap_static_state[5] = { 0 };
	int static_state = 0;
	char ac_exten_infor_switch[10] = { 0 };
	char neidead_inter[10] = { 0 };
	char asd_arp_listen_switch[10] = { 0 };
	char asd_log_level[10] = { 0 };
	char response_sta_probe_request[10] = { 0 };
	char trap_level[5] = { 0 };
	char warm_standby_type[10] = { 0 };
	char warm_standby_addr[20] = { 0 };
	char ip1[4] = { 0 };
	char ip2[4] = { 0 };
	char ip3[4] = { 0 };
	char ip4[4] = { 0 };
	char add_ac_listen_if[50] = { 0 };
	char del_ac_listen_if[50] = { 0 };
	char user_set_vlan[10] = { 0 };
	char country_code[5] = { 0 };
	char temp[100] = { 0 };
	char max_wlan_num[10] = { 0 };
	char max_wtp_num[10] = { 0 };
	char max_radio_num[10] = { 0 };

	/***********************set wid max mtu*****************************/	
    memset(mtu,0,sizeof(mtu));
	cgiFormStringNoNewlines("mtu",mtu,20);   
    if(strcmp(mtu,"")!=0)
  	{
		ret = config_wireless_max_mtu(ins_para->parameter,ins_para->connection,mtu);
		switch(ret)
		{
			case -1:ShowAlert(search(lwcontrol,"mtu_num"));
					flag = 0;
					break;
			case 1: break;
			case -2:ShowAlert(search(lpublic,"oper_fail"));
					flag = 0;
					break;
				
		}
    }


    /***********************set wid log switch*****************************/		
    memset(log_stat,0,sizeof(log_stat));
    cgiFormStringNoNewlines("log",log_stat,20); 
	if(strcmp(log_stat,"")!=0)	
	{
		ret = set_wid_log_switch_cmd(ins_para->parameter,ins_para->connection,log_stat);
		switch(ret)
		{
			case 1:break;
			case -1:ShowAlert(search(lpublic,"oper_fail"));
					flag = 0;
					break;
		}
	}


	/***********************set wid log switch*****************************/		
    memset(log_size,0,sizeof(log_size));
	cgiFormStringNoNewlines("log_size",log_size,20); 
	if(strcmp(log_size,"")!=0)	
 	{
		ret = set_wid_log_size_cmd(ins_para->parameter,ins_para->connection,log_size);
		switch(ret)
		{
			case -1:flag = 0;
				    ShowAlert(search(lwcontrol,"log_num"));
				    break;
			case 1:break;
			case -2:flag = 0;
					ShowAlert(search(lpublic,"oper_fail"));
					break;
		}
 	}

	/***********************set ap statistics switch*****************************/		
    memset(ap_static_state,0,sizeof(ap_static_state));
	cgiFormStringNoNewlines("ap_static_state",ap_static_state,5); 
	if(strcmp(ap_static_state,"")!=0)	
 	{
 		static_state = strtoul(ap_static_state,&endptr,10);
		ret = set_ap_statistics(ins_para->parameter,ins_para->connection,static_state);
		switch(ret)
		{
			case SNMPD_CONNECTION_ERROR:
			case 0:flag = 0;
				   ShowAlert(search(lwcontrol,"con_static_state_fail"));
				    break;
			case 1:break;
			case -1:flag = 0;
					ShowAlert(search(lpublic,"error"));
					break;
		}
 	}


	/***********************set all ap extension information switch*****************************/		
    memset(ac_exten_infor_switch,0,sizeof(ac_exten_infor_switch));
	cgiFormStringNoNewlines("ac_exten_infor_switch",ac_exten_infor_switch,10); 
	if(strcmp(ac_exten_infor_switch,"")!=0)	
 	{
		ret = set_ac_all_ap_extension_information_enable_cmd(ins_para->parameter,ins_para->connection,ac_exten_infor_switch);
		switch(ret)
		{
			case SNMPD_CONNECTION_ERROR:
			case 0:flag = 0;
				   ShowAlert(search(lwcontrol,"con_ac_exten_infor_switch_fail"));
				    break;
			case 1:break;
			case -1:flag = 0;
					ShowAlert(search(lpublic,"input_para_illegal"));
					break;
			case -2:flag = 0;
					ShowAlert(search(lpublic,"error"));
					break;
		}
 	}
	

	/***********************set neighbordead interval cmd func*****************************/		
    memset(neidead_inter,0,sizeof(neidead_inter));
	cgiFormStringNoNewlines("neidead_inter",neidead_inter,10); 
	if(strcmp(neidead_inter,"")!=0)	
 	{
		ret = set_neighbordead_interval_cmd_func(ins_para->parameter,ins_para->connection,neidead_inter);
		switch(ret)
		{
		 	case SNMPD_CONNECTION_ERROR:
			case 0:flag = 0;
				   ShowAlert(search(lwcontrol,"set_neidead_inter_fail"));
				   break;
			case 1:break;
			case -1:flag = 0;
					ShowAlert(search(lwcontrol,"neidead_inter_illegal"));
					break;
			case -2:flag = 0;
					ShowAlert(search(lpublic,"error"));
					break;
		}
 	}

	/***********************set asd sta arp listen cmd*****************************/		
    memset(asd_arp_listen_switch,0,sizeof(asd_arp_listen_switch));
	cgiFormStringNoNewlines("asd_arp_listen_switch",asd_arp_listen_switch,10); 
	if(strcmp(asd_arp_listen_switch,"")!=0)	
 	{
		ret = set_asd_sta_arp_listen_cmd(ins_para->parameter,ins_para->connection,"listen",asd_arp_listen_switch);
		switch(ret)
		{
		 	case SNMPD_CONNECTION_ERROR:
			case 0:flag = 0;
				   ShowAlert(search(lwcontrol,"set_asd_arp_listen_switch_fail"));
				   break;
			case 1:break;
			case -1:flag = 0;
					ShowAlert(search(lpublic,"input_para_illegal"));
					break;
		}
 	}

	/***********************set asd daemonlog level cmd*****************************/
    memset(asd_log_level,0,sizeof(asd_log_level));
    cgiFormStringNoNewlines("asd_log_level",asd_log_level,10); 
	if(strcmp(asd_log_level,"")!=0)	
	{
		ret = set_asd_daemonlog_level_cmd(ins_para->parameter,ins_para->connection,asd_log_level);
		switch(ret)
		{
			case SNMPD_CONNECTION_ERROR:
			case 0:flag = 0;
				   ShowAlert(search(lwcontrol,"set_asd_log_level_fail"));
				   break;
			case 1:break;
			case -1:flag = 0;
					ShowAlert(search(lpublic,"input_para_illegal"));
					break;
			case -2:flag = 0;
					ShowAlert(search(lpublic,"error"));
					break;
		}
	}

	/***********************set wlan not response sta probe request cmd*****************************/
	memset(response_sta_probe_request,0,sizeof(response_sta_probe_request));
	cgiFormStringNoNewlines("response_sta_probe_request",response_sta_probe_request,10);
	if(strcmp(response_sta_probe_request,"") != 0)
	{
		ret=set_wlan_not_response_sta_probe_request_cmd(ins_para->parameter,ins_para->connection,0,response_sta_probe_request);
																				/*返回0表示失败，返回1表示成功*/
																				/*返回-1表示input patameter only with 'enable' or 'disable'*/
																				/*返回-2表示WLAN ID非法，返回-3表示wlan does not exist*/
																				/*返回-4表示wlan is enable, please disable it first*/
																				/*返回-5表示you want to some wlan, and the operation of the wlan was not successful*/
																				/*返回-6表示error*/
																			    /*返回SNMPD_CONNECTION_ERROR表示connection error*/
		switch(ret)
		{
			case SNMPD_CONNECTION_ERROR:
			case -5:
			case 0:ShowAlert(search(lwlan,"set_response_sta_probe_request_fail"));
				   flag=0;
				   break;
			case 1:break;
			case -1:ShowAlert(search(lpublic,"input_para_illegal"));
					flag=0;
					break; 
			case -2:{
				      memset(temp,0,sizeof(temp));
				      strncpy(temp,search(lwlan,"wlan_id_illegal1"),sizeof(temp)-1);
				      memset(max_wlan_num,0,sizeof(max_wlan_num));
				      snprintf(max_wlan_num,sizeof(max_wlan_num)-1,"%d",WLAN_NUM-1);
				      strncat(temp,max_wlan_num,sizeof(temp)-strlen(temp)-1);
				      strncat(temp,search(lwlan,"wlan_id_illegal2"),sizeof(temp)-strlen(temp)-1);
				      ShowAlert(temp);
					  flag=0;
				      break;
				    }
			case -3:ShowAlert(search(lwlan,"wlan_not_exist"));
					flag=0;
					break; 
			case -4:ShowAlert(search(lwlan,"dis_wlan"));
					flag=0;
					break; 
			case -6:ShowAlert(search(lpublic,"error"));
					flag=0;
					break;
		}
	}

	/***********************set wid trap open func*****************************/
	memset(trap_level,0,sizeof(trap_level));
	cgiFormStringNoNewlines("trap_level",trap_level,5);
	if(strcmp(trap_level,"") != 0)
	{
		ret=set_wid_trap_open_func(ins_para->parameter,ins_para->connection,trap_level);
																	/*返回1表示成功，返回0表示失败，返回-1表示error*/
																	/*返回SNMPD_CONNECTION_ERROR表示connection error*/
		switch(ret)
		{
			case SNMPD_CONNECTION_ERROR:
			case 0:ShowAlert(search(lwlan,"set_trap_level_fail"));
				   flag=0;
				   break;
			case 1:break;
			case -1:ShowAlert(search(lpublic,"error"));
					flag=0;
					break;
			case -2:ShowAlert(search(lpublic,"input_para_illegal"));
					flag=0;
					break;
		}
	}


	/***********************set ac master ipaddr cmd*****************************/
	memset(warm_standby_type,0,sizeof(warm_standby_type));
	cgiFormStringNoNewlines("warm_standby_type",warm_standby_type,10);
	memset(warm_standby_addr,0,sizeof(warm_standby_addr));                                 
    memset(ip1,0,sizeof(ip1));
    cgiFormStringNoNewlines("ip1",ip1,4);	
    strncat(warm_standby_addr,ip1,sizeof(warm_standby_addr)-strlen(warm_standby_addr)-1);
    strncat(warm_standby_addr,".",sizeof(warm_standby_addr)-strlen(warm_standby_addr)-1);
    memset(ip2,0,sizeof(ip2));
    cgiFormStringNoNewlines("ip2",ip2,4); 
    strncat(warm_standby_addr,ip2,sizeof(warm_standby_addr)-strlen(warm_standby_addr)-1);	
    strncat(warm_standby_addr,".",sizeof(warm_standby_addr)-strlen(warm_standby_addr)-1);
    memset(ip3,0,sizeof(ip3));
    cgiFormStringNoNewlines("ip3",ip3,4); 
    strncat(warm_standby_addr,ip3,sizeof(warm_standby_addr)-strlen(warm_standby_addr)-1);	
    strncat(warm_standby_addr,".",sizeof(warm_standby_addr)-strlen(warm_standby_addr)-1);
    memset(ip4,0,sizeof(ip4));
    cgiFormStringNoNewlines("ip4",ip4,4);
    strncat(warm_standby_addr,ip4,sizeof(warm_standby_addr)-strlen(warm_standby_addr)-1);
	if((strcmp(warm_standby_type,"") != 0)&&(strcmp(warm_standby_type,"...") != 0))
	{
		ret=set_ac_master_ipaddr_cmd(ins_para->parameter,ins_para->connection,warm_standby_type,warm_standby_addr);
																	/*返回0表示失败，返回1表示成功*/
																	/*返回-1表示invalid input,input should be master or bakup*/
																	/*返回-2表示unknown ip format，返回-3表示more if have this ip*/
																	/*返回-4表示no if has this ip，返回-5表示please disable it first*/
																	/*返回-6表示no interface binding this ip*/
																	/*返回-7表示this ip has not been added or has already been deleted*/
																	/*返回-8表示error*/
																	/*返回SNMPD_CONNECTION_ERROR表示connection error*/
		switch(ret)
		{
			case SNMPD_CONNECTION_ERROR:
			case 0:ShowAlert(search(lwcontrol,"set_warm_standby_addr_fail"));
				   flag=0;
				   break;
			case 1:break;
			case -1:ShowAlert(search(lpublic,"input_para_illegal"));
					flag=0;
					break;
			case -2:ShowAlert(search(lpublic,"unknown_ip_format"));
					flag=0;
					break;
			case -3:ShowAlert(search(lwcontrol,"more_if_have_ip"));
					flag=0;
					break;
			case -4:ShowAlert(search(lwcontrol,"no_if_has_ip"));
					flag=0;
					break;
			case -5:ShowAlert(search(lwcontrol,"disable_it_first"));
					flag=0;
					break;
			case -6:ShowAlert(search(lwcontrol,"no_if_bind_ip"));
					flag=0;
					break;
			case -7:ShowAlert(search(lwcontrol,"this_ip_has_deleted"));
					flag=0;
					break;
			case -8:ShowAlert(search(lpublic,"error"));
					flag=0;
					break;
		}
	}

	/***********************set wirelesscontrol listen l3 interface cmd*****************************/
	memset(add_ac_listen_if,0,sizeof(add_ac_listen_if));
	cgiFormStringNoNewlines("add_ac_listen_if",add_ac_listen_if,50);
	if(strcmp(add_ac_listen_if,"") != 0)
	{
		ret=set_wirelesscontrol_listen_l3_interface_cmd(ins_para->parameter,ins_para->connection,"add",add_ac_listen_if);
																	/*返回0表示失败，返回1表示成功*/
																	/*返回-1表示interface name is too long,should be no more than 15*/
																	/*返回-2表示input patameter only with 'add'or 'del'*/
																	/*返回-3表示 auto ap login switch is enable,you should disable it first*/
																	/*返回-4表示interface error, no index or interface down*/
																	/*返回-5表示this interface has not been added or has already been deleted*/
																	/*返回-6表示interface is down，返回-7表示interface is no flags*/
																	/*返回-8表示tinterface is no index，返回-9表示interface is no local interface, permission denial*/
																	/*返回-10表示interface is other hansi listen*/
																	/*返回SNMPD_CONNECTION_ERROR表示connection error*/
		switch(ret)
		{
			case SNMPD_CONNECTION_ERROR:
			case 0:ShowAlert(search(lwcontrol,"add_ac_listen_if_fail"));
				   flag=0;
				   break;
			case 1:break;
			case -1:ShowAlert(search(lpublic,"interface_too_long"));
					flag=0;
					break;
			case -2:ShowAlert(search(lpublic,"input_para_illegal"));
					flag=0;
					break;
			case -3:ShowAlert(search(lwlan,"disable_auto_ap_switch"));
					flag=0;
					break;
			case -4:{
				 	  memset(temp,0,sizeof(temp));
			          strncpy(temp,search(lpublic,"inter"),sizeof(temp)-1);
				      strncat(temp,add_ac_listen_if,sizeof(temp)-strlen(temp)-1);
				      strncat(temp,search(lpublic,"inter_err_noindex_isdown"),sizeof(temp)-strlen(temp)-1);
			          ShowAlert(temp);
					  flag=0;
					  break;
				    }
			case -5:ShowAlert(search(lwcontrol,"this_ip_has_deleted"));
					flag=0;
					break;
			case -6:ShowAlert(search(lwlan,"inter_is_down"));
					flag=0;
					break;
			case -7:ShowAlert(search(lwlan,"inter_is_no_flag"));
					flag=0;
					break;
			case -8:ShowAlert(search(lwlan,"inter_is_no_index"));
					flag=0;
					break;
			case -9:ShowAlert(search(lpublic,"no_local_interface"));
					flag=0;
					break;
			case -10:ShowAlert(search(lwlan,"interface_bind_in_other_hansi"));
					 flag=0;
					 break;
		}
	}

	
	/***********************set wirelesscontrol listen l3 interface cmd*****************************/
	memset(del_ac_listen_if,0,sizeof(del_ac_listen_if));
	cgiFormStringNoNewlines("del_ac_listen_if",del_ac_listen_if,50);
	if(strcmp(del_ac_listen_if,"") != 0)
	{
		ret=set_wirelesscontrol_listen_l3_interface_cmd(ins_para->parameter,ins_para->connection,"del",del_ac_listen_if);
																	/*返回0表示失败，返回1表示成功*/
																	/*返回-1表示interface name is too long,should be no more than 15*/
																	/*返回-2表示input patameter only with 'add'or 'del'*/
																	/*返回-3表示 auto ap login switch is enable,you should disable it first*/
																	/*返回-4表示interface error, no index or interface down*/
																	/*返回-5表示this interface has not been added or has already been deleted*/
																	/*返回-6表示interface is down，返回-7表示interface is no flags*/
																	/*返回-8表示tinterface is no index，返回-9表示interface is no local interface, permission denial*/
																	/*返回-10表示interface is other hansi listen*/
																	/*返回SNMPD_CONNECTION_ERROR表示connection error*/
		switch(ret)
		{
			case SNMPD_CONNECTION_ERROR:
			case 0:ShowAlert(search(lwcontrol,"add_ac_listen_if_fail"));
				   flag=0;
				   break;
			case 1:break;
			case -1:ShowAlert(search(lpublic,"interface_too_long"));
					flag=0;
					break;
			case -2:ShowAlert(search(lpublic,"input_para_illegal"));
					flag=0;
					break;
			case -3:ShowAlert(search(lwlan,"disable_auto_ap_switch"));
					flag=0;
					break;
			case -4:{
					  memset(temp,0,sizeof(temp));
					  strncpy(temp,search(lpublic,"inter"),sizeof(temp)-1);
					  strncat(temp,add_ac_listen_if,sizeof(temp)-strlen(temp)-1);
					  strncat(temp,search(lpublic,"inter_err_noindex_isdown"),sizeof(temp)-strlen(temp)-1);
					  ShowAlert(temp);
					  flag=0;
					  break;
					}
			case -5:ShowAlert(search(lwcontrol,"this_ip_has_deleted"));
					flag=0;
					break;
			case -6:ShowAlert(search(lwlan,"inter_is_down"));
					flag=0;
					break;
			case -7:ShowAlert(search(lwlan,"inter_is_no_flag"));
					flag=0;
					break;
			case -8:ShowAlert(search(lwlan,"inter_is_no_index"));
					flag=0;
					break;
			case -9:ShowAlert(search(lpublic,"no_local_interface"));
					flag=0;
					break;
			case -10:ShowAlert(search(lwlan,"interface_bind_in_other_hansi"));
					 flag=0;
					 break;
		}
	}

	/***********************set vlan switch cmd*****************************/
	memset(user_set_vlan,0,sizeof(user_set_vlan));
	cgiFormStringNoNewlines("user_set_vlan",user_set_vlan,10);
	if(strcmp(user_set_vlan,"") != 0)
	{
		ret=set_vlan_switch_cmd(ins_para->parameter,ins_para->connection,user_set_vlan);
																			/*返回0表示失败，返回1表示成功*/
																			/*返回-1表示error*/
																			/*返回SNMPD_CONNECTION_ERROR表示connection error*/
		switch(ret)
		{
			case SNMPD_CONNECTION_ERROR:
			case 0:ShowAlert(search(lwcontrol,"con_user_set_vlan_fail"));
				   flag=0;
				   break;
			case 1:break;
			case -1:ShowAlert(search(lpublic,"error"));
					flag=0;
					break;
		}
	}

	/***********************set system country code func*****************************/
	memset(country_code,0,sizeof(country_code));
	cgiFormStringNoNewlines("country_code",country_code,5);
	if(strcmp(country_code,"") != 0)
	{
		ret=set_system_country_code_func(ins_para->parameter,ins_para->connection,0,0,country_code);
																			/*返回0表示失败，返回1表示成功，返回-1表示input country code should be capital letters*/
																			/*返回-2表示input country code error，返回-3表示system country code is already Country_code, no need to change*/
																			/*返回-4表示system country code error，返回-5表示WTP ID非法，返回-6表示Radio ID非法*/
																			/*返回SNMPD_CONNECTION_ERROR表示connection error*/
		switch(ret)
		{
			case SNMPD_CONNECTION_ERROR:
			case 0:ShowAlert(search(lwcontrol,"con_country_code_fail"));
				   flag=0;
				   break;
			case 1:break;
			case -1:
			case -2:ShowAlert(search(lpublic,"input_para_illegal"));
					flag=0;
					break;
			case -3:{
					  memset(temp,0,sizeof(temp));
					  strncpy(temp,search(lwcontrol,"country_code_no_need_change1"),sizeof(temp)-1);
					  strncat(temp,country_code,sizeof(temp)-strlen(temp)-1);
					  strncat(temp,search(lwcontrol,"country_code_no_need_change2"),sizeof(temp)-strlen(temp)-1);
					  ShowAlert(temp);
					  flag=0;
					  break;
					}
			case -4:ShowAlert(search(lpublic,"sys_err"));
					flag=0;
					break;
			case -5:{
					  memset(temp,0,sizeof(temp));
					  strncpy(temp,search(lwlan,"wtp_id_illegal1"),sizeof(temp)-1);
					  memset(max_wtp_num,0,sizeof(max_wtp_num));
					  snprintf(max_wtp_num,sizeof(max_wtp_num)-1,"%d",WTP_NUM-1);
					  strncat(temp,max_wtp_num,sizeof(temp)-strlen(temp)-1);
					  strncat(temp,search(lwlan,"wtp_id_illegal2"),sizeof(temp)-strlen(temp)-1);
					  ShowAlert(temp);
					  flag = 0;
					  break;
				    }
			case -6:{					  
		              memset(temp,0,sizeof(temp));
					  strncpy(temp,search(lwlan,"radio_id_illegal1"),sizeof(temp)-1);
					  memset(max_radio_num,0,sizeof(max_radio_num));
					  snprintf(max_radio_num,sizeof(max_radio_num)-1,"%d",G_RADIO_NUM-1);
					  strncat(temp,max_radio_num,sizeof(temp)-strlen(temp)-1);
					  strncat(temp,search(lwlan,"radio_id_illegal2"),sizeof(temp)-strlen(temp)-1);
				  	  ShowAlert(temp);
					  flag=0;
					  break;
					}
		}
	}

    if(flag == 1)
  	{
		ShowAlert(search(lpublic,"oper_succ"));
  	}
}