void HandleClientMsg(SSL_CLIENT_DATA* ssl_data, int epollfd)
{
	if(!ssl_data)
		return;
	SSL *ssl = ssl_data->ssl;
	char buffer[BUFF_LEN];
	int recvLen;
	bzero(buffer, BUFF_LEN);
	recvLen = SSL_recv(ssl, buffer, BUFF_LEN);
	if(recvLen <= 0 || strncmp(buffer, "quit", 4)==0)
	{
		printf("client quit!\n");
		SSL_Client_Leave(ssl_data, epollfd);
		return;
	}

	/*Parse the user cert request*/
	cJSON *root = cJSON_Parse(buffer);
	if(!root)	
	{
		HandleError(ssl, "JSON parse error!");
		goto end;
	}

	cJSON *child = root->child, *cmd=NULL, *attr=NULL;
	while(child)
	{
		if(0==strcmp(child->string, "cmd"))
			cmd = child;
		else if(0==strcmp(child->string, "attr"))
			attr = child;
		
		child = child->next;
	}

	printf("Receive from client %d: %s\n", SSL_get_fd(ssl_data->ssl), buffer);
	if(0==strcmp(cmd->valuestring, "get_cert"))
	{
		char *certFile = ProduceNewCertForUser(attr);	
		printf("certfile:%s;\n", certFile);
		fflush(NULL);
		
		/*Generate the response text*/
		char *resp = NULL;
		FILE *file = fopen(certFile, "r");
		if(!file)
		{
			HandleError(ssl, "Certificate generate failed with unknown error!\n");
		}else{
			fseek(file, 0L, SEEK_END);
			if(0==ftell(file))
			{
				HandleError(ssl, "Certificate generate failed with unknown error!\n");
				fclose(file);
				remove(certFile);
			}else{
				/*Calculate. Remove all the path prefix, leave the pure file name*/
				char *fileName = certFile, *ret=NULL;
				ret = strtok(certFile, "/");
				while(ret)
				{
					fileName = ret;
					ret = strtok(NULL, "/");
				}
				cJSON *resp_json = cJSON_CreateObject();
				cJSON_AddStringToObject(resp_json, "cmd", "sending_cert_next");
				cJSON *attr = cJSON_CreateObject();
				cJSON_AddItemToObject(resp_json, "attr", attr);
				cJSON_AddStringToObject(attr, "filename", fileName);
				char *resp = cJSON_Print(resp_json);
				cJSON_Delete(resp_json);
				SSL_send(ssl, resp, strlen(resp));
				free(resp);
				/*Next we must send the cert file to the client*/
				rewind(file);
				char buffer[512]={0};
				int len = 0, sendLen=0;
				while(!feof(file))
				{
					printf("Sending cert....\n");
					len = fread(buffer, sizeof(char), 511, file);
					if(len<=0)
						break;
					buffer[len] = '\0';
					sendLen = SSL_send(ssl, buffer, len);
					if(sendLen<len)
						break;
				}
				SSL_send(ssl, "!@done*#", 8);
				fclose(file);
			}
		}
		
		free(certFile);
	}else if(0==strcmp(cmd->valuestring, "pubkey_query"))
	{
		/*get the username*/
		char *username = NULL;
		if(0==strcmp(attr->child->string, "username"))
			username = attr->child->valuestring;

		if(!username)
		{
			HandleError(ssl, "You must specify the user name!");
			return;
		}
		/*Generate the response text*/
		char certFile[512];
		strcpy(certFile, "certs/client/");
		strcat(certFile, username);
		strcat(certFile, "Pub.pem");
		char *resp = NULL;
		FILE *file = fopen(certFile, "r");
		if(!file)
		{
			HandleError(ssl, "your requested file not exists!\n");
		}else{
			fseek(file, 0L, SEEK_END);
			if(0==ftell(file))
			{
				HandleError(ssl, "your requested file not exists!\n");
				fclose(file);
				remove(certFile);
			}else{
				/*Calculate. Remove all the path prefix, leave the pure file name*/
				char *fileName = basename(certFile), *ret=NULL;
				
				cJSON *resp_json = cJSON_CreateObject();
				cJSON_AddStringToObject(resp_json, "cmd", "sending_pubkey_next");
				cJSON *attr = cJSON_CreateObject();
				cJSON_AddItemToObject(resp_json, "attr", attr);
				cJSON_AddStringToObject(attr, "filename", fileName);
				char *resp = cJSON_Print(resp_json);
				cJSON_Delete(resp_json);
				SSL_send(ssl, resp, strlen(resp));
				free(resp);
				/*Next we must send the cert file to the client*/
				rewind(file);
				char buffer[512]={0};
				int len = 0, sendLen=0;
				while(!feof(file))
				{
					printf("Sending public key....\n");
					len = fread(buffer, sizeof(char), 511, file);
					if(len<=0)
						break;
					buffer[len] = '\0';
					sendLen = SSL_send(ssl, buffer, len);
					if(sendLen<len)
						break;
				}
				SSL_send(ssl, "!@done*#", 8);
				printf("Done.\n");
				fclose(file);
			}
		}
		
	}

end:
	cJSON_Delete(root);
}