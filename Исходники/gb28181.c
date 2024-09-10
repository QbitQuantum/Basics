int gb28181_init_env(pSipEnv *env)
{
	TRACE("Init GB28181 env\n");
	//constly
	SYSCONF_t *sysconf = SYSCONF_dup();
	pSipEnv p = (pSipEnv)calloc(1,sizeof(sSipEnv));
	*env = p;
	char devip[20];
	SOCK_gethostname(devip);
	GB_ASSERT(*env,"Calloc env  Node failed\n");
	printf("calloc env hdr node %p\n",*env);
	SIP_ENV_insert(p,"Model",sysconf->ipcam.info.device_model);
	SIP_ENV_insert(p,"UserAgent",sysconf->ipcam.info.device_name);
	SIP_ENV_insert(p,"Firmware",sysconf->ipcam.info.software_version);
	SIP_ENV_insert(p,"MaxAlarm","1");
	SIP_ENV_insert(p,"MaxCamera","1");
	SIP_ENV_insert(p,"Manufacturer","JUAN");	

	// variable
	Gb28181Conf_t gb_conf;
	memset(&gb_conf, 0, sizeof(Gb28181Conf_t));
	gb28181_read_env(&gb_conf,sizeof(Gb28181Conf_t));
	if(strlen(gb_conf.SipServerId) > 0)
		//if(0)
	{
		TRACE("use the env in the flash,SipServerId:%s:%d\n",gb_conf.SipServerId,
				strlen(gb_conf.SipServerId));	
		SIP_ENV_insert(p,"Realm",gb_conf.LoginDomain);
		SIP_ENV_insert(p,"SipServerId",gb_conf.SipServerId);
		SIP_ENV_insert(p,"SipServerIp",gb_conf.SipServerIp);
		SIP_ENV_insert(p,"SipServerPort",ITOA(gb_conf.SipServerPort));
		SIP_ENV_insert(p,"UserId",gb_conf.UserId);
		SIP_ENV_insert(p,"UserPwd",gb_conf.UserPwd);
		SIP_ENV_insert(p,"DevPort",ITOA(GB28181_DEFAULT_DEV_PORT));
		SIP_ENV_insert(p,"DevIp",devip);
		SIP_ENV_insert(p,"AliveTime",ITOA(gb_conf.AliveTime));
		SIP_ENV_insert(p,"HeartBeatTime",ITOA(gb_conf.HeartBeatTime));
		SIP_ENV_insert(p,"Alarm1",gb_conf.AlarmId[0]);
		SIP_ENV_insert(p,"Video1",gb_conf.VideoId[0]);
	}
	else{ // use the default gb28181 env
		TRACE("NULL gb28181 env ,use default env\n");
		gb28181_write_env(&def_gb_conf,sizeof(Gb28181Conf_t));
		SIP_ENV_insert(p,"Realm",def_gb_conf.LoginDomain);
		SIP_ENV_insert(p,"SipServerId",def_gb_conf.SipServerId);
		SIP_ENV_insert(p,"SipServerIp",def_gb_conf.SipServerIp);
		SIP_ENV_insert(p,"SipServerPort",ITOA(def_gb_conf.SipServerPort));	
		SIP_ENV_insert(p,"UserId",def_gb_conf.UserId);
		SIP_ENV_insert(p,"UserPwd",def_gb_conf.UserPwd);
		SIP_ENV_insert(p,"DevIp",devip);
		SIP_ENV_insert(p,"DevPort",ITOA(GB28181_DEFAULT_DEV_PORT));
		SIP_ENV_insert(p,"AliveTime",ITOA(def_gb_conf.AliveTime));
		SIP_ENV_insert(p,"HeartBeatTime",ITOA(def_gb_conf.HeartBeatTime));
		SIP_ENV_insert(p,"Alarm1",def_gb_conf.AlarmId[0]);
		SIP_ENV_insert(p,"Video1",def_gb_conf.VideoId[0]);

	}
	return 0;
}