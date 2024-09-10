void* serve_client(void* info)
{
	int sfd_client, connection_id, x;
	struct packet shp;
	char lpwd[LENBUFFER];
	struct client_info* ci = (struct client_info*) info;
	sfd_client = ci->sfd;
	connection_id = ci->cid;
	
	while(1)
	{
		if(recv_packet_ret(sfd_client, &shp) < 0)
		{
			fprintf(stderr, "client ID(%d) closed/terminated. closing connection.\n", connection_id);
			break;
		}

		if(shp.type == TERM)
			break;

		if(shp.conid == -1)
			shp.conid = connection_id;
		
		if(shp.type == REQU)
		{
			switch(shp.comid)
			{
				case PWD:
					if(!getcwd(lpwd, sizeof lpwd))
						er("getcwd()", 0);
					command_pwd(sfd_client, &shp, lpwd);
					break;
				case CD:
					if((x = chdir(shp.buffer)) == -1)
						fprintf(stderr, "Wrong path.\n");
					command_cd(sfd_client, &shp, x == -1 ? "fail" : "success");
					break;
				case MKDIR:
					command_mkdir(sfd_client, &shp);
					break;
				case LS:
					if(!getcwd(lpwd, sizeof lpwd))
						er("getcwd()", 0);
					command_ls(sfd_client, &shp, lpwd);
					break;
				case GET:
					command_get(sfd_client, &shp);
					break;
				case PUT:
					command_put(sfd_client, &shp);
					break;
				case RGET:
					if(!getcwd(lpwd, sizeof lpwd))
						er("getcwd()", 0);
					command_rget(sfd_client, &shp);
					send_EOT(sfd_client, &shp);
					if((x = chdir(lpwd)) == -1)
						fprintf(stderr, "Wrong path.\n");
					break;
				default:
					// print error
					break;
			}
		}
		else
		{
			//show error, send TERM and break
			fprintf(stderr, "packet incomprihensible. closing connection.\n");
			send_TERM(sfd_client, &shp);
			break;
		}
	}

	close(sfd_client);
	fflush(stdout);
	return NULL;
}