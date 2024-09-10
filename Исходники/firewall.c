void add_self_to_firewall(void)
{
	if(!IsUserAnAdmin())
	{
		log_printf(LOG_ERROR, "Cannot add firewall exception, not running as an administrator");
		return;
	}
	
	CoInitialize(NULL);
	
	/* We need to go deeper. */
	
	INetFwMgr *fw_mgr;
	HRESULT err = CoCreateInstance(&CLSID_NetFwMgr_s, NULL, CLSCTX_INPROC_SERVER, &IID_INetFwMgr_s, (void**)(&fw_mgr));
	if(err == S_OK)
	{
		INetFwPolicy *fw_policy;
		if((err = INetFwMgr_get_LocalPolicy(fw_mgr, &fw_policy)) == S_OK)
		{
			INetFwProfile *fw_profile;
			if((err = INetFwPolicy_get_CurrentProfile(fw_policy, &fw_profile)) == S_OK)
			{
				INetFwAuthorizedApplications *fw_apps;
				if((err = INetFwProfile_get_AuthorizedApplications(fw_profile, &fw_apps)) == S_OK)
				{
					/* Create an instance of INetFwAuthorizedApplication and
					 * put the current executable in it.
					*/
					
					INetFwAuthorizedApplication *this_exe;
					if((err = CoCreateInstance(&CLSID_NetFwAuthorizedApplication_s, NULL, CLSCTX_INPROC_SERVER, &IID_INetFwAuthorizedApplication_s, (void**)(&this_exe))) == S_OK)
					{
						if(_fill_this_exe(this_exe))
						{
							/* Add the new INetFwAuthorizedApplication
							 * to the active profile.
							*/
							
							if((err = INetFwAuthorizedApplications_Add(fw_apps, this_exe)) != S_OK)
							{
								log_printf(LOG_ERROR, "Could not add firewall exception (error %u)", (unsigned int)(err));
							}
						}
						
						INetFwAuthorizedApplication_Release(this_exe);
					}
					else{
						log_printf(LOG_ERROR, "Could not create INetFwAuthorizedApplication (error %u)", (unsigned int)(err));
					}
					
					INetFwAuthorizedApplications_Release(fw_apps);
				}
				else{
					log_printf(LOG_ERROR, "Could not get INetFwAuthorizedApplications object (error %u)", (unsigned int)(err));
				}
				
				INetFwProfile_Release(fw_profile);
			}
			else{
				log_printf(LOG_ERROR, "Could not get INetFwProfile object (error %u)", (unsigned int)(err));
			}
			
			INetFwPolicy_Release(fw_policy);
		}
		else{
			log_printf(LOG_ERROR, "Could not get INetFwPolicy object (error %u)", (unsigned int)(err));
		}
		
		INetFwMgr_Release(fw_mgr);
	}
	else{
		log_printf(LOG_ERROR, "Could not create INetFwMgr object (error %u)", (unsigned int)(err));
	}
	
	CoUninitialize();
}