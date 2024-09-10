void CBanList::ServerResponded()
{

	if(m_bGotIPs == false) 
	{
		m_BanList.RemoveAll();

		const char *rconResp = m_pRcon->RconResponse();
		const char *cur = strstr(rconResp,"UserID filter list:")
								+ strlen("UserID filter list:");

		if( (unsigned int)cur == strlen("UserID filter list:")) 
			// if strstr returned NULL and we added a strlen to it...
		{
			cur=NULL;
		}
	// listid format:
	//	UserID filter list:
	// 1 23434 : 20.000 min

	// and on empty it produces:
	//	IP filter list: empty

		while(cur!=NULL) 
		{

			TokenLine banLine;
			cur++; // dodge the newline
			banLine.SetLine(cur); // need to add one here, to remove the "\n"
			if(banLine.CountToken() >= 4 ) 
			{
				Bans_t ban;

				memset(&ban,0x0,sizeof(Bans_t));
	
				v_strncpy(ban.name,banLine.GetToken(1),20);
				sscanf(banLine.GetToken(3),"%f",&ban.time);
				ban.type= ID;
				m_BanList.AddToTail(ban);
	
			}
			cur=strchr(cur,'\n');
		
		}
		
		m_bGotIPs=true;

		// now find out the list of banned ips
		m_pRcon->SendRcon("listip");
	} 
	else 
	{

	// listip format:
	//	IP filter list:
	//192.168.  1. 66 : 20.000 min

			const char *rconResp = m_pRcon->RconResponse();
		const char *cur = strstr(rconResp,"IP filter list:")
								+ strlen("IP filter list:");

		if( (unsigned int)cur == strlen("IP filter list:")) 
			// if strstr returned NULL and we added a strlen to it...
		{
			cur=NULL;
		}


		while(cur!=NULL) 
		{

			char tmpStr[512]; 
			Bans_t ban;
	
			cur++; // dodge past the newline
			v_strncpy(tmpStr,cur,512);

			memset(&ban,0x0,sizeof(Bans_t));
	
			if( strchr(tmpStr,':') != NULL )
			{
				char *time; 
				time = strchr(tmpStr,':')+1;
				tmpStr[strchr(tmpStr,':')-tmpStr]=0;
				
				v_strncpy(ban.name,tmpStr,20);
				unsigned int i=0;
				while(i<strlen(ban.name)) // strip all the white space out...
				{
					if( ban.name[i]==' ') 
					{
						strcpy(&ban.name[i],&ban.name[i+1]);
					} 
					else 
					{
						i++;
					}
				}

				sscanf(time,"%f",&ban.time);
				ban.type= IP;
				m_BanList.AddToTail(ban);
	
			}
			cur=strchr(cur,'\n');
		
		}
		
		m_bNewBanList=true;
		m_bIsRefreshing=false;




		// notify the UI of the new server info
		m_pResponseTarget->ServerResponded();
	}

}