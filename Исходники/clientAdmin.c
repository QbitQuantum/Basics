/***************************************************************************
  Function: push_to_cloud
  Description: 
  Input: mt
            action_str
            old_str
            new_str
  Output: none
  Return: 0:receive status[1(if modifypassword) or 2(if modifyalias)]            
              positive:receive status[(-9,-10)(if modifypassword) or (-11,-12,-13)(if modifyalias)]
              negative:other error
  Others:  none
***************************************************************************/
static int push_to_cloud(modifyType mt, const char *action_str, const char *old_str, const char *new_str)
{
    cJSON *send_json, *receive_json, *status_json;
    char *json_send_out;
	char send_str[CA_PUSH_TO_CLOUD_LEN], receive_str[CA_PUSH_TO_CLOUD_LEN];
	int fd, nwrite, nread, re, nfd;
	struct sockaddr_in	servaddr;

	// Section1: prepare for push
    send_json = cJSON_CreateObject();
	if (!send_json) {
		CA_DEBUG("create send_json failed\n");
		return -1;
	}
	cJSON_AddStringToObject(send_json, "action", action_str);
	switch (mt) {
		case modifyPasswordType:
			cJSON_AddStringToObject(send_json, "old_password", old_str);
			cJSON_AddStringToObject(send_json, "new_password", new_str);
			break;
		case modifyAliasType:
			cJSON_AddStringToObject(send_json, "old_alias", old_str);
			cJSON_AddStringToObject(send_json, "new_alias", new_str);
			break;
		default:
			CA_DEBUG("undefined modifyType:%d\n", mt);
			cJSON_Delete(send_json);
			return -1;
	}
    if ( (json_send_out = cJSON_PrintUnformatted(send_json)) == 0 ) {
		CA_DEBUG("%d print send_json failed\n", mt);
		cJSON_Delete(send_json);
		return -1;
    }
	
    cJSON_Delete(send_json);	
    nwrite = snprintf(send_str, CA_PUSH_TO_CLOUD_LEN, "%s", json_send_out);
	nwrite += 1; // including the terminated null 
    free(json_send_out);

    // Section2: send and receive
    // reWrite the next line
	//fd = Tcp_connect("192.168.1.121", FEATURE_GDGL_CPROXY_CA_PUSH_PORT_STR);
	if ( (fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        CA_DEBUG("%d socket error\n", mt);
		return -2;
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(FEATURE_GDGL_CPROXY_CA_PUSH_PORT);
	//if ( (re = inet_pton(AF_INET, "192.168.1.238", &servaddr.sin_addr)) <= 0) {
	if ( (re = inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr)) <= 0) {
		CA_DEBUG("%d inet_pton error:%d\n", mt, re);
		close(fd);
		return -2;
	}	
	if ( connect(fd, (SA *) &servaddr, sizeof(servaddr)) < 0 ) {
		CA_DEBUG("%d connect error\n", mt);
		close(fd);
		return -2;
	}	
	
    if ( writen(fd, send_str, nwrite) != nwrite ) {
		CA_DEBUG("%d write error\n", mt);
		close(fd);
		return -2;
    }

    if ( (nfd = readable_timeo(fd, PUSH_TO_CLOUD_TIMEOUT)) < 0) {
		CA_DEBUG("%d readable_timeo error\n", mt);
		close(fd);
		return -2;
	}
	else if (nfd == 0) { //timeout, close connection
		CA_DEBUG("%d readable_timeo timeout\n", mt);
		close(fd);
		return -2;
	}

	while (1) {
	    if ( (nread = read(fd, receive_str, CA_PUSH_TO_CLOUD_LEN - 1)) < 0) {
			if (errno == EINTR) 
				continue;
			else {
		        CA_DEBUG("%d read error\n", mt);
		        close(fd);
		        return -2;
			}
	    }
		else if (nread == 0) {
			CA_DEBUG("%d closed by other end\n", mt);
		    close(fd);
		    return -2;
		}
		else
			break;
	}
	close(fd);
	receive_str[nread] = 0; // add the terminated null 
	CA_DEBUG("%d receive:\n%s\n", mt, receive_str);

	// Section3: parse result
	receive_json = cJSON_Parse(receive_str);
	if (!receive_json) {
		CA_DEBUG("%d receive_json parse Error before:%s\n", mt, cJSON_GetErrorPtr());
		return -3;
	}

   	status_json = cJSON_GetObjectItem(receive_json, "status");
	if (!status_json) {
		cJSON_Delete(receive_json);
		CA_DEBUG("%d receive no status\n", mt);
		return -3;
	}
    if (status_json->type != cJSON_Number) {		
		CA_DEBUG("%d receive status but not a number\n", mt);
		cJSON_Delete(receive_json);
		return -3;
	}
	switch (status_json->valueint) {
		case PUSH_TO_CLOUD_RESPONSE_JSON_PARSE_FAILED:
			CA_DEBUG("%d receive [json parse failed]\n", mt);
		    cJSON_Delete(receive_json);
		    return -3;

		case PUSH_TO_CLOUD_RESPONSE_REQ_HANDLER_INVALID:
			CA_DEBUG("%d receive [request handler invalid]\n", mt);
		    cJSON_Delete(receive_json);
		    return -3;

		case PUSH_TO_CLOUD_RESPONSE_INVALID_ACTION:
			CA_DEBUG("%d receive [invalid action]\n", mt);
		    cJSON_Delete(receive_json);
		    return -3;
			
		case PUSH_TO_CLOUD_RESPONSE_UNKNOWN_ACTION:
			CA_DEBUG("%d receive [unknown action]\n", mt);
		    cJSON_Delete(receive_json);
		    return -3;
									
		default:
			break;
	}
	if (mt == modifyPasswordType) {
	    switch (status_json->valueint) {
		    case PUSH_TO_CLOUD_RESPONSE_PASSWD_SUCCESS:
			    cJSON_Delete(receive_json);
	            return 0;

		    case PUSH_TO_CLOUD_RESPONSE_INVALID_OLD_PASSWD:
			    CA_DEBUG("%d receive [invalid old_password]\n", mt);
		        cJSON_Delete(receive_json);
		        return -3;

		    case PUSH_TO_CLOUD_RESPONSE_INVALID_NEW_PASSWD:
			    CA_DEBUG("%d receive [invalid new_password]\n", mt);
		        cJSON_Delete(receive_json);
		        return -3;
						
		    case PUSH_TO_CLOUD_RESPONSE_OLD_PASSWD_ERR:
			    CA_DEBUG("%d receive [old password not correct]\n", mt);
		        cJSON_Delete(receive_json);
		        return clientAdminPushToCloudOldPasswdErr;
			
		    case PUSH_TO_CLOUD_RESPONSE_PASSWD_SAME:
			    CA_DEBUG("%d receive [same passwords]\n", mt);
		        cJSON_Delete(receive_json);
		        return clientAdminPushToCloudPasswdSame;
						
		    default:
			    CA_DEBUG("%d receive unsupported status:[%d]\n", mt, status_json->valueint);
		        cJSON_Delete(receive_json);
		        return -3;
	    }
	}
	else if (mt == modifyAliasType) {
	    switch (status_json->valueint) {
		    case PUSH_TO_CLOUD_RESPONSE_ALIAS_SUCCESS:
			    cJSON_Delete(receive_json);
	            return 0;
			    				
		    case PUSH_TO_CLOUD_RESPONSE_INVALID_OLD_ALIAS:
			    CA_DEBUG("%d receive [invalid old_alias]\n", mt);
		        cJSON_Delete(receive_json);
		        return -3;

		    case PUSH_TO_CLOUD_RESPONSE_INVALID_NEW_ALIAS:
			    CA_DEBUG("%d receive [invalid new_alias]\n", mt);
		        cJSON_Delete(receive_json);
		        return -3;
						
		    case PUSH_TO_CLOUD_RESPONSE_OLD_ALIAS_NOT_EXIST:
			    CA_DEBUG("%d receive [old alias not exist]\n", mt);
		        cJSON_Delete(receive_json);
		        return clientAdminPushToCloudOldAliasNotExist;
			
		    case PUSH_TO_CLOUD_RESPONSE_NEW_ALIAS_EXIST:
			    CA_DEBUG("%d receive [new alias already exist]\n", mt);
		        cJSON_Delete(receive_json);
		        return clientAdminPushToCloudNewAliasExist;
			
		    case PUSH_TO_CLOUD_RESPONSE_ALIAS_SAME:
			    CA_DEBUG("%d receive [same aliases]\n", mt);
		        cJSON_Delete(receive_json);
		        return clientAdminPushToCloudAliasSame;
			
		    default:
			    CA_DEBUG("%d receive unsupported status:[%d]\n", mt, status_json->valueint);
		        cJSON_Delete(receive_json);
		        return -3;
	    }
	}
	else {
		CA_DEBUG("undefined modifyType:%d\n", mt);
		cJSON_Delete(receive_json);
		return -3;
	}
}