int
handle_SyslogServerIPAddr(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    
    switch(reqinfo->mode) {

        case MODE_GET:
		{
			//int acNTPConfig = 0;
			int ret = 0;
			ST_LOG_KEY logkey;

			memset(&logkey,0,sizeof(logkey));
			if(access(XML_FPATH,0)==0)
			{
				ret = find_log_node(XML_FPATH,NODE_DES,NODE_ATT,"sysip",NODE_CONTENT,&logkey);
				if(ret==0)
				{
					//INET_ATON(acNTPConfig, sname)
					//找到第一个ip地址。
					//char cmd_all[256];
					char get_ip[32];
					int ip_addr;


					//sprintf( cmd_all, LOG_CMD_FORMAT, logkey.key, "\\2","","" );
					//GET_CMD_STDOUT( get_ip, sizeof(get_ip), cmd_all );
					if(strcmp(logkey.key,"")!=0)
					{
						cut_up_ip( logkey.key,get_ip);
						INET_ATON(ip_addr,get_ip);

					}
					else
					{
						ip_addr=0;
					}
					snmp_set_var_typed_value(requests->requestvb, ASN_IPADDRESS,
												(u_char *)&ip_addr,
												sizeof(ip_addr));
				}	
				else
				{
					snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
												(u_char *)"UNKNOWN",
												strlen("UNKNOWN"));
				}
			}
			else
			{
				snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
											(u_char *)"UNKNOWN",
											strlen("UNKNOWN"));
			}
		 }
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
          
            break;

        case MODE_SET_RESERVE2:         
            break;

        case MODE_SET_FREE:
            /* XXX: free resources allocated in RESERVE1 and/or
               RESERVE2.  Something failed somewhere, and the states
               below won't be called. */
            break;

        case MODE_SET_ACTION:
		   {
				int ret = 0;
				ST_LOG_KEY logkey;

				memset(&logkey,0,sizeof(logkey));
				//ret=find_ntp_node(fpath,NTP_SERV,NODE_ATT,"1",NODE_VALUE,&sname);

				ret = find_log_node(XML_FPATH,NODE_DES,NODE_ATT,"sysip",NODE_CONTENT,&logkey);
				if(ret==0)
				{
					//找到第一个ip地址。
					//char cmd_all[256];
					char set_ip[32];
					int ip_addr;
					char cur_ip[32];
					char *temp;
					ST_SYS_ALL sysall;

					ip_addr = *requests->requestvb->val.integer;
					INET_NTOA( ip_addr, set_ip );
					//sprintf( cmd_all, LOG_CMD_FORMAT, logkey.key, "\\1",set_ip,"\\3" );
					//GET_CMD_STDOUT( logkey.key, sizeof(logkey.key), cmd_all );
					cut_up_ip( logkey.key,cur_ip);
					temp = replace_ip( logkey.key, cur_ip, set_ip);
					mod_log_node( XML_FPATH,NODE_DES,NODE_ATT,"sysip",NODE_CONTENT,temp);

					read_filter( XML_FPATH, NULL, &sysall);
					write_config( &sysall, CONF_FPATH);
					free(temp);
				}			
			}
            break;

        case MODE_SET_COMMIT:
          
            break;

        case MODE_SET_UNDO:
         
            break;

        default:
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}