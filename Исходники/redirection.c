int rdp_redirection_apply_settings(rdpRdp* rdp)
{
	rdpSettings* settings = rdp->settings;
	rdpRedirection* redirection = rdp->redirection;

	settings->RedirectionFlags = redirection->flags;
	settings->RedirectedSessionId = redirection->sessionID;

	if (settings->RedirectionFlags & LB_LOAD_BALANCE_INFO)
	{
		/* LoadBalanceInfo may not contain a null terminator */
		free(settings->LoadBalanceInfo);
		settings->LoadBalanceInfoLength = redirection->LoadBalanceInfoLength;
		settings->LoadBalanceInfo = (BYTE*) malloc(settings->LoadBalanceInfoLength);

		if (!settings->LoadBalanceInfo)
			return -1;

		CopyMemory(settings->LoadBalanceInfo, redirection->LoadBalanceInfo, settings->LoadBalanceInfoLength);
	}
	else
	{
		/**
		 * Free previous LoadBalanceInfo, if any, otherwise it may end up
		 * being reused for the redirected session, which is not what we want.
		 */
		free(settings->LoadBalanceInfo);
		settings->LoadBalanceInfo = NULL;
		settings->LoadBalanceInfoLength = 0;
	}

	if (settings->RedirectionFlags & LB_TARGET_FQDN)
	{
		free(settings->RedirectionTargetFQDN);
		settings->RedirectionTargetFQDN = _strdup(redirection->TargetFQDN);
		if (!settings->RedirectionTargetFQDN)
			return -1;
	}
	else if (settings->RedirectionFlags & LB_TARGET_NET_ADDRESS)
	{
		free(settings->TargetNetAddress);
		settings->TargetNetAddress = _strdup(redirection->TargetNetAddress);
		if (!settings->TargetNetAddress)
			return -1;
	}
	else if (settings->RedirectionFlags & LB_TARGET_NETBIOS_NAME)
	{
		free(settings->RedirectionTargetNetBiosName);
		settings->RedirectionTargetNetBiosName = _strdup(redirection->TargetNetBiosName);
		if (!settings->RedirectionTargetNetBiosName)
			return -1;
	}

	if (settings->RedirectionFlags & LB_USERNAME)
	{
		free(settings->RedirectionUsername);
		settings->RedirectionUsername = _strdup(redirection->Username);
		if (!settings->RedirectionUsername)
			return -1;
	}

	if (settings->RedirectionFlags & LB_DOMAIN)
	{
		free(settings->RedirectionDomain);
		settings->RedirectionDomain = _strdup(redirection->Domain);
		if (!settings->RedirectionDomain)
			return -1;
	}

	if (settings->RedirectionFlags & LB_PASSWORD)
	{
		/* Password may be a cookie without a null terminator */
		free(settings->RedirectionPassword);
		settings->RedirectionPasswordLength = redirection->PasswordLength;
		settings->RedirectionPassword = (BYTE*) malloc(settings->RedirectionPasswordLength);
		if (!settings->RedirectionPassword)
			return -1;
		CopyMemory(settings->RedirectionPassword, redirection->Password, settings->RedirectionPasswordLength);
	}

	if (settings->RedirectionFlags & LB_CLIENT_TSV_URL)
	{
		/* TsvUrl may not contain a null terminator */
		free(settings->RedirectionTsvUrl);
		settings->RedirectionTsvUrlLength = redirection->TsvUrlLength;
		settings->RedirectionTsvUrl = (BYTE*) malloc(settings->RedirectionTsvUrlLength);
		if (!settings->RedirectionTsvUrl)
			return -1;
		CopyMemory(settings->RedirectionTsvUrl, redirection->TsvUrl, settings->RedirectionTsvUrlLength);
	}

	if (settings->RedirectionFlags & LB_TARGET_NET_ADDRESSES)
	{
		UINT32 i;
		freerdp_target_net_addresses_free(settings);
		settings->TargetNetAddressCount = redirection->TargetNetAddressesCount;
		settings->TargetNetAddresses = (char**) malloc(sizeof(char*) * settings->TargetNetAddressCount);
		if (!settings->TargetNetAddresses)
		{
			settings->TargetNetAddressCount = 0;
			return -1;
		}

		for (i = 0; i < settings->TargetNetAddressCount; i++)
		{
			settings->TargetNetAddresses[i] = _strdup(redirection->TargetNetAddresses[i]);
			if (!settings->TargetNetAddresses[i])
			{
				for (--i; i >= 0; --i)
					free(settings->TargetNetAddresses[i]);
				return -1;
			}
		}
	}

	return 0;
}