//DecodeXml
int CParseDevice::DecodeXml(const char *xml, int sock_fd)
{
	if (NULL == xml)
	{
		printf("ERROR:Empty xml message...\n");
		return -1;
	}
	TiXmlDocument *handle = new TiXmlDocument();
	TiXmlPrinter *printer = new TiXmlPrinter();
	handle->Parse(xml);
	TiXmlNode* EnvelopeNode = handle->FirstChild("Envelope");
	const char * EnvelopeType = EnvelopeNode->ToElement()->Attribute("type");
	if(EnvelopeType != NULL){
		if(!strcmp(EnvelopeType,"r_pregister")){
			cms_fd = sock_fd;
			return  0;
		}
		if (cms_fd == sock_fd){
			if(!strcmp(EnvelopeType,"getrtspuri")){
				EnvelopeNode->ToElement()->SetAttribute("type","r_getrtspuri");
				TiXmlNode* profileNode = EnvelopeNode->FirstChildElement("profile"); 
				int count = 0;
				while(profileNode){
					DeviceInfo devInfo;
					memset(&devInfo, 0, sizeof(devInfo));
					const char* szXmlValue = NULL;
					TiXmlNode* profile = profileNode->FirstChildElement("deviceip");
					if(profile != NULL){
						szXmlValue = profile->ToElement()->GetText();
						devInfo.m_nId = rtspcount++;
						int a[4];
						sscanf(szXmlValue, "%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
						char ipbuffer[32];
						sprintf(ipbuffer, "%xx%xx%xx%x%c",a[0],     a[1], a[2], a[3], (char)(count +103 ));
						strncpy(devInfo.m_szIdname, ipbuffer, strlen(ipbuffer));
					}
					profile = profileNode->FirstChildElement("token");
					if(profile != NULL){
						szXmlValue = profile->ToElement()->GetText();
					}
					profile = profileNode->FirstChildElement("sourceuri");
					if(profile != NULL){
						szXmlValue = profile->ToElement()->GetText();
						if(szXmlValue != NULL)
							strncpy(devInfo.m_szSourceUrl, szXmlValue, sizeof(devInfo.m_szSourceUrl));
					}

					//Add Device
					if(strcmp(devInfo.m_szSourceUrl,"") != 0){
						if (success != AddDevice(devInfo)){
							printf("ERROR:Add new ProxySession:%s Falied!",devInfo.m_szSourceUrl);
							TiXmlText *DestContent = new TiXmlText("None");
							TiXmlElement *DestElement = new TiXmlElement("desturi");
							DestElement->LinkEndChild(DestContent);
							profileNode->ToElement()->LinkEndChild(DestElement);
						}else{
							char desturl[500];
							memset(desturl,0,strlen(desturl));
							sprintf(desturl, "rtsp://%s:8554/%s", server_addr, devInfo.m_szIdname);
							printf("INFO:Add new ProxySession:%s\nProxy this Session from %s\n",devInfo.m_szSourceUrl,desturl);
							TiXmlText *DestContent = new TiXmlText(desturl);
							TiXmlElement *DestElement = new TiXmlElement("desturi");
							DestElement->LinkEndChild(DestContent);
							profileNode->ToElement()->LinkEndChild(DestElement);
						}
					}

					profileNode = profileNode->NextSiblingElement("profile");
					count++;
				}   
				handle->Accept( printer );  
				if (send ( sock_fd, printer->CStr() , strlen(const_cast<char *>(printer->CStr())), 0) == - 1) { 
                    				perror ( "ERROR:Send error\n" ); 
                    				return -1;
                			} 
                			delete handle;
                			delete printer;
				return 0; 
			}
		}
	}
	return -1;
 }