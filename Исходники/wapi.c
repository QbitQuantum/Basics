/*
    ========================================================================

    Routine Description:
        In kernel mode read parameters from file

    Arguments:
        src                     the location of the file.
        dest                        put the parameters to the destination.
        Length                  size to read.

    Return Value:
        None

    Note:

    ========================================================================
*/
void rtmp_read_wapi_parms_from_file(
		IN  PRTMP_ADAPTER pAd, 
		PSTRING tmpbuf, 
		PSTRING buffer)
{	
	UINT32					ip_addr;
#ifdef CONFIG_AP_SUPPORT	
	INT						apidx = 0;
#endif // CONFIG_AP_SUPPORT //

	PCOMMON_WAPI_INFO pInfo = &pAd->CommonCfg.comm_wapi_info;
	
	// wapi interface name
	if (RTMPGetKeyParameter("Wapiifname", tmpbuf, 32, buffer, TRUE))
	{
		if (strlen(tmpbuf) > 0)
		{
			NdisMoveMemory(pInfo->wapi_ifname, tmpbuf, strlen(tmpbuf));
			pInfo->wapi_ifname_len = strlen(tmpbuf); 
			
			DBGPRINT(RT_DEBUG_TRACE, ("Wapiifname=%s, len=%d\n", 
														pInfo->wapi_ifname, 
														pInfo->wapi_ifname_len));
		}
	}
	

	// WapiAsCertPath
	if (RTMPGetKeyParameter("WapiAsCertPath", tmpbuf, 128, buffer, TRUE))
	{
		if (strlen(tmpbuf) > 0)
		{
			NdisMoveMemory(pInfo->as_cert_path, tmpbuf, strlen(tmpbuf));
			pInfo->as_cert_path_len = strlen(tmpbuf); 
			
			DBGPRINT(RT_DEBUG_TRACE, ("WapiAsCertPath=%s, len=%d\n", 
														pInfo->as_cert_path, 
														pInfo->as_cert_path_len));
		}
	}

	// WapiUserCertPath
	if (RTMPGetKeyParameter("WapiUserCertPath", tmpbuf, 128, buffer, TRUE))
	{
		if (strlen(tmpbuf) > 0)
		{
			NdisMoveMemory(pInfo->user_cert_path, tmpbuf, strlen(tmpbuf));
			pInfo->user_cert_path_len = strlen(tmpbuf); 
			
			DBGPRINT(RT_DEBUG_TRACE, ("WapiUserCertPath=%s, len=%d\n", 
														pInfo->user_cert_path, 
														pInfo->user_cert_path_len));
		}
	}

	// WapiAsIpAddr
	if (RTMPGetKeyParameter("WapiAsIpAddr", tmpbuf, 32, buffer, TRUE))
	{
		if (rtinet_aton(tmpbuf, &ip_addr))
     	{
            pInfo->wapi_as_ip = ip_addr;  
			DBGPRINT(RT_DEBUG_TRACE, ("WapiAsIpAddr=%s(%x)\n", tmpbuf, pInfo->wapi_as_ip));
		}	    
	}

	// WapiAsPort
	if (RTMPGetKeyParameter("WapiAsPort", tmpbuf, 32, buffer, TRUE))
	{
		pInfo->wapi_as_port = simple_strtol(tmpbuf, 0, 10); 
		DBGPRINT(RT_DEBUG_TRACE, ("WapiAsPort=%d\n", pInfo->wapi_as_port));			   
	}

	// WapiUskRekeyMethod
	if (RTMPGetKeyParameter("WapiUskRekeyMethod", tmpbuf, 32, buffer, TRUE))
	{		
		if ((strcmp(tmpbuf, "TIME") == 0) || (strcmp(tmpbuf, "time") == 0))
			pAd->CommonCfg.wapi_usk_rekey_method = REKEY_METHOD_TIME;
		else if ((strcmp(tmpbuf, "PKT") == 0) || (strcmp(tmpbuf, "pkt") == 0))
			pAd->CommonCfg.wapi_usk_rekey_method = REKEY_METHOD_PKT;
		else
			pAd->CommonCfg.wapi_usk_rekey_method = REKEY_METHOD_DISABLE;

		DBGPRINT(RT_DEBUG_TRACE, ("WapiUskRekeyMethod=%d\n", pAd->CommonCfg.wapi_usk_rekey_method));			   
	}

	// WapiUskRekeyThreshold
	if (RTMPGetKeyParameter("WapiUskRekeyThreshold", tmpbuf, 32, buffer, TRUE))
	{			
		pAd->CommonCfg.wapi_usk_rekey_threshold = simple_strtol(tmpbuf, 0, 10); 
		DBGPRINT(RT_DEBUG_TRACE, ("WapiUskRekeyThreshold=%d\n", pAd->CommonCfg.wapi_usk_rekey_threshold));			   
	}

	// WapiMskRekeyMethod
	if (RTMPGetKeyParameter("WapiMskRekeyMethod", tmpbuf, 32, buffer, TRUE))
	{		
		if ((strcmp(tmpbuf, "TIME") == 0) || (strcmp(tmpbuf, "time") == 0))
			pAd->CommonCfg.wapi_msk_rekey_method = REKEY_METHOD_TIME;
		else if ((strcmp(tmpbuf, "PKT") == 0) || (strcmp(tmpbuf, "pkt") == 0))
			pAd->CommonCfg.wapi_msk_rekey_method = REKEY_METHOD_PKT;
		else
			pAd->CommonCfg.wapi_msk_rekey_method = REKEY_METHOD_DISABLE;

		DBGPRINT(RT_DEBUG_TRACE, ("WapiMskRekeyMethod=%d\n", pAd->CommonCfg.wapi_msk_rekey_method));			   
	}

	// WapiMskRekeyThreshold
	if (RTMPGetKeyParameter("WapiMskRekeyThreshold", tmpbuf, 32, buffer, TRUE))
	{
		pAd->CommonCfg.wapi_msk_rekey_threshold = simple_strtol(tmpbuf, 0, 10); 
		DBGPRINT(RT_DEBUG_TRACE, ("WapiMskRekeyThreshold=%d\n", pAd->CommonCfg.wapi_msk_rekey_threshold));			   
	}
	
#ifdef CONFIG_AP_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
	{						
		STRING tok_str[16];

		// WapiPskX		
		for (apidx = 0; apidx < pAd->ApCfg.BssidNum; apidx++)
		{
			snprintf(tok_str, sizeof(tok_str), "WapiPsk%d", apidx + 1);
			
			NdisZeroMemory(pAd->ApCfg.MBSSID[apidx].WAPIPassPhrase, 64);
			pAd->ApCfg.MBSSID[apidx].WAPIPassPhraseLen = 0;
			if(RTMPGetKeyParameter(tok_str, tmpbuf, 65, buffer, FALSE))
			{								    
			    if (strlen(tmpbuf) >= 8 && strlen(tmpbuf) <= 64)
			    {                                    
			        NdisMoveMemory(pAd->ApCfg.MBSSID[apidx].WAPIPassPhrase, tmpbuf, strlen(tmpbuf));
			        pAd->ApCfg.MBSSID[apidx].WAPIPassPhraseLen = strlen(tmpbuf);
   					DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) WapiPsk=(%s), len=%d\n", apidx, tmpbuf, strlen(tmpbuf)));						
			    }
				else
				{
					if (pAd->ApCfg.MBSSID[apidx].AuthMode == Ndis802_11AuthModeWAIPSK)
					{
						pAd->ApCfg.MBSSID[apidx].AuthMode = Ndis802_11AuthModeOpen;
						pAd->ApCfg.MBSSID[apidx].WepStatus = Ndis802_11EncryptionDisabled;
					}
					DBGPRINT(RT_DEBUG_ERROR, ("IF(ra%d) The length of WAPI PSKPassPhrase is invalid(len=%d). \n", apidx, strlen(tmpbuf)));
				}																			
			}
		}					
	}
#endif // CONFIG_AP_SUPPORT //

	
#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		// WapiPsk
		if (RTMPGetKeyParameter("WapiPsk", tmpbuf, 512, buffer, FALSE))
		{											                 										
		    NdisZeroMemory(pAd->StaCfg.WAPIPassPhrase, 64);
		    pAd->StaCfg.WAPIPassPhraseLen = 0;
		    if (strlen(tmpbuf) >= 8 && strlen(tmpbuf) <= 64)
		    {                                    
		        NdisMoveMemory(pAd->StaCfg.WAPIPassPhrase, tmpbuf, strlen(tmpbuf));
		        pAd->StaCfg.WAPIPassPhraseLen = strlen(tmpbuf);

				DBGPRINT(RT_DEBUG_TRACE, ("WapiPsk=(%s), len=%d\n", tmpbuf, strlen(tmpbuf)));						
		    }
			else
			{
				if (pAd->StaCfg.AuthMode == Ndis802_11AuthModeWAIPSK)
				{
					pAd->StaCfg.AuthMode = Ndis802_11AuthModeOpen;
					pAd->StaCfg.WepStatus = Ndis802_11EncryptionDisabled;
				}
				DBGPRINT(RT_DEBUG_ERROR, ("The length of WAPI PSKPassPhrase is invalid(len=%d). \n", strlen(tmpbuf)));
			}			      						 
		}
	}
#endif // CONFIG_STA_SUPPORT //													

	// WapiPskType
	if (RTMPGetKeyParameter("WapiPskType", tmpbuf, 32, buffer, TRUE))
	{		
		INT	err;

#ifdef CONFIG_AP_SUPPORT
		IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
		{
			PSTRING macptr;
			
			for (apidx = 0, macptr = rstrtok(tmpbuf,";"); macptr; macptr = rstrtok(NULL,";"), apidx++)
		    {
				err = 0;
			
				if (apidx >= pAd->ApCfg.BssidNum)
					break;

				// HEX
				if(simple_strtol(macptr, 0, 10) == 0)
				{
					pAd->ApCfg.MBSSID[apidx].WapiPskType = HEX_MODE;
		
					if (pAd->ApCfg.MBSSID[apidx].WAPIPassPhraseLen % 2 != 0)
					{
						err = 1;
						DBGPRINT(RT_DEBUG_ERROR, ("I/F(ra%d) The WAPI-PSK key length MUST be even in Hex mode\n", apidx));						
					}						
				}
				// ASCII
				else	
				{
					pAd->ApCfg.MBSSID[apidx].WapiPskType = ASCII_MODE;
				}
				
				if (err)
				{
					pAd->ApCfg.MBSSID[apidx].AuthMode = Ndis802_11AuthModeOpen;
					pAd->ApCfg.MBSSID[apidx].WepStatus = Ndis802_11EncryptionDisabled;
				}
				else
					DBGPRINT(RT_DEBUG_TRACE, ("I/F(ra%d) WapiPskType=%s\n", apidx, (pAd->ApCfg.MBSSID[apidx].WapiPskType == HEX_MODE) ? "HEX" : "ASCII"));
		    }
		}
#endif // CONFIG_AP_SUPPORT //

#ifdef CONFIG_STA_SUPPORT
		IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
		{
			err = 0;
		
			// HEX
			if(simple_strtol(tmpbuf, 0, 10) == 0)  
			{
				pAd->StaCfg.WapiPskType = HEX_MODE;
	
				if (pAd->StaCfg.WAPIPassPhraseLen % 2 != 0)
				{
					err = 1;
					DBGPRINT(RT_DEBUG_ERROR, ("The WAPI-PSK key length MUST be even in Hex mode\n"));						
				}
			}
			// ASCII
			else 
			{
				pAd->StaCfg.WapiPskType = ASCII_MODE;
			}

			if (err)
			{
				pAd->StaCfg.AuthMode = Ndis802_11AuthModeOpen;
				pAd->StaCfg.WepStatus = Ndis802_11EncryptionDisabled;
			}
			else
				DBGPRINT(RT_DEBUG_TRACE, ("WapiPskType=%s\n", (pAd->StaCfg.WapiPskType == HEX_MODE) ? "HEX" : "ASCII"));
		}
#endif // CONFIG_STA_SUPPORT //
				
	}