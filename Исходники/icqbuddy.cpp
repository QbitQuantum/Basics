bool SnacIcqBuddy::process(unsigned short subtype, ICQBuffer* buf, unsigned short seq)
{
    switch (subtype)
	{
    case ICQ_SNACxBDY_RIGHTSxGRANTED:
        log(L_DEBUG, "Buddy rights granted");
        break;
    case ICQ_SNACxBDY_USEROFFLINE:
		{
			Contact *contact;
			QString screen = buf->unpackScreen();
            log(L_DEBUG, "Buddy offline: %s", qPrintable(screen));
			ICQUserData *data = m_client->findContact(screen, NULL, false, contact);
			if(!data)
				break;
            if(data->getStatus() != ICQ_STATUS_OFFLINE)
			{
				m_client->setOffline(data);
				StatusMessage *m = new StatusMessage;
				m->setContact(contact->id());
				m->setClient(m_client->dataName(data));
				m->setStatus(STATUS_OFFLINE);
				m->setFlags(MESSAGE_RECEIVED);
				EventMessageReceived e(m);
				if(!e.process())
					delete m;
			}
			else
			{
				// hack for trillian
				EventContact e(contact, EventContact::eOnline);
				e.process();
			}
			break;
		}
    case ICQ_SNACxBDY_USERONLINE:
		{
            Contact *contact;
            QString screen = buf->unpackScreen();
            log(L_DEBUG, "Buddy online: %s", qPrintable(screen));
			ICQUserData *data = m_client->findContact(screen, NULL, false, contact);
			if(data)
			{
				bool bChanged     = false;
				bool bAwayChanged = false;
                unsigned long prevStatus = data->getStatus();

				unsigned short level, len;
				(*buf) >> level >> len;
				data->setWarningLevel(level);

				TlvList tlv((*buf));
				Tlv* tlvClass = tlv(TLV_USER_CLASS);
				if(tlvClass)
				{
					unsigned short userClass = *tlvClass;
                    if(userClass != data->getClass())
					{
                        if ((userClass & CLASS_AWAY) != (data->getClass() & CLASS_AWAY))
						{
                            data->setStatusTime((unsigned long)time(NULL));
							bAwayChanged = true;
						}
                        data->setClass(userClass);
						bChanged = true;
					}
                    if(data->getUin() == 0)
					{
						if (userClass & CLASS_AWAY)
						{
							m_client->fetchAwayMessage(data);
						}
						else
						{
                            data->setAutoReply(QString::null);
						}
					}
				}

				// Status TLV
				Tlv *tlvStatus = tlv(TLV_USER_STATUS);
				if(tlvStatus)
				{
					uint32_t status = *tlvStatus;
                    if (status != data->getStatus())
					{
                        data->setStatus(status);
						if ((status & 0xFF) == 0)
                            data->setAutoReply(QString::null);
                        data->setStatusTime((unsigned long)time(NULL));
					}
				}
                else if(data->getStatus() == ICQ_STATUS_OFFLINE)
				{
                    data->setStatus(ICQ_STATUS_ONLINE);
                    data->setStatusTime((unsigned long)time(NULL));
				}

				// Online time TLV
				Tlv *tlvOnlineTime = tlv(TLV_USER_SIGNON_TIME);
				if(tlvOnlineTime)
				{
					uint32_t OnlineTime = *tlvOnlineTime;
					if(OnlineTime != data->getOnlineTime())
					{
						data->setOnlineTime(OnlineTime);
						bChanged = true;
					}
				}
				Tlv *tlvNATime = tlv(0x0004);
				if(tlvNATime)
				{
					unsigned short na_time = *tlvNATime;
					unsigned long StatusTime = (unsigned long)time(NULL) - na_time * 60;
                    if(StatusTime != data->getStatusTime())
					{
                        data->setStatusTime(StatusTime);
						bChanged = true;
					}
				}

				// IP TLV
				Tlv *tlvIP = tlv(TLV_USER_EXT_IP);
                unsigned long oldip = data->getIP();
                data->setIP(htonl((uint32_t)(*tlvIP)));
				if(tlvIP)
                    bChanged |= oldip != data->getIP();

				// short caps tlv
				Tlv *tlvCapShort = tlv(TLV_USER_NEWCAPS);
				if(tlvCapShort)
				{
                    data->setCaps(0);
                    data->setCaps2(0);

					ICQBuffer info(*tlvCapShort);

					for (; info.readPos() < (unsigned)info.size(); )
					{
						unsigned char shortcap[2];
						info.unpack((char*)shortcap, sizeof(shortcap));
						for (unsigned i = 0;; i++)
						{
							if (!memcmp(m_client->capabilities[i],"\x00\x00\x00\x00", 4)) {
                                    log(L_DEBUG, "%lu unknown cap %s", data->getUin(),
                                        makeCapStr(shortcap, sizeof(shortcap)).toLatin1().data());
								break;
							}
							// we don't go through all caps, only the starting with 0x09
							if (*m_client->capabilities[i] != '\x09')
								continue;
							if(!memcmp(&m_client->capabilities[i][2], shortcap, sizeof(shortcap)))
							{
                                m_client->setCap(data, (cap_id_t)i);
								break;
							}
						}
					}
				}
				// normal cap tlv
				Tlv *tlvCapability = tlv(TLV_USER_CAPS);
				if (tlvCapability)
				{
					if(!tlvCapShort)
					{
                        data->setCaps(0);
                        data->setCaps2(0);
					}
					ICQBuffer info(*tlvCapability);
					for(; info.readPos() < (unsigned)info.size(); )
					{
						capability cap;
						info.unpack((char*)cap, sizeof(capability));
						for(unsigned i = 0;; i++)
						{
							unsigned size = sizeof(capability);
							if (i == CAP_SIMOLD)
								size--;

							if (!memcmp(m_client->capabilities[i], "\x00\x00\x00\x00", 4)) 
							{
                                log( L_DEBUG, "%lu unknown cap %s", data->getUin(), qPrintable(makeCapStr( cap, size )) );
								break;
							}
                            if (i == CAP_MICQ || i == CAP_LICQ || i == CAP_SIM || i == CAP_KOPETE || i == CAP_QIP2010)
								size -= 4;
                            if (i == CAP_ANDRQ)
								size -= 7;
                            if (i == CAP_MIRANDA)
								size -= 8;
							if ((i == CAP_JIMM))
								size -= 11;
							if (i == CAP_ICQJP)
								size -= (16 - 4);

							if (!memcmp(cap, m_client->capabilities[i], size))
							{
								if (i == CAP_SIMOLD)
								{
									unsigned char build = cap[sizeof(capability)-1];
                                    if (build && (build == 0x92 || build < (1 << 6))) continue;
                                    data->setBuild(build);
								}
                                if (i == CAP_MICQ || i == CAP_LICQ || i == CAP_SIM || i == CAP_KOPETE)
								{
									unsigned char *p = (unsigned char*)cap;
									p += 12;
                                    data->setBuild((p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3]);
								}
                                if (i == CAP_ANDRQ)
								{
									unsigned char *p = (unsigned char*)cap;
									p += 9;
                                    data->setBuild((p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3]);
								}
                                if (i == CAP_MIRANDA)
								{
									unsigned char *p = (unsigned char*)cap;
									p += 8;
                                    data->setBuild((p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3]);
								}
                                if (i == CAP_JIMM)
								{
									char *p = (char*)cap;
									p += 5;
									const QString str = QString::fromAscii(p, 10);
									const QStringList sl = str.split('.');
									unsigned char maj = 0, min = 0;
									unsigned short rev = 0;
									if(sl.count() > 0)
										maj = sl[0].toUShort();
									if(sl.count() > 1)
										min = sl[1].toUShort();
									if(sl.count() > 2)
										rev = sl[2].toUShort();

                                    data->setBuild((maj << 24) + (min << 16) + rev);
								}
								if (i == CAP_ICQJP)
								{
                                    log(L_DEBUG, "%lu ICQJP cap is set", data->getUin());
                                    data->setBuild(cap[0x4] << 0x18 | cap[0x5] << 0x10 |
                                        cap[0x6] << 8 | cap[0x7]);
								}
								m_client->setCap(data, (cap_id_t)i);
								break;
							}
						}
					}
				}

				// buddy info
				Tlv *tlvBuddy = tlv(TLV_USER_BUDDYINFO);
				if (tlvBuddy)
				{
                    QByteArray ba = data->getBuddyHash();
					unsigned short iconID;
					unsigned char iconFlags, hashSize;
					ICQBuffer info(*tlvBuddy);
					QByteArray hash;
					QString fname = m_client->pictureFile(data);
					QFileInfo fi(fname);

					info >> iconID >> iconFlags >> hashSize;
					hash.resize(hashSize);
					info.unpack(hash.data(), hashSize);
                    if(data->getBuddyID() != iconID ||
							ba != hash ||
							!fi.exists() || fi.size() == 0) {
                        data->setBuddyID(iconID);
                        data->setBuddyHash(hash);
						m_client->requestBuddy(data);
					}
				}

				unsigned long infoUpdateTime = 0;
				unsigned long pluginInfoTime = 0;
				unsigned long pluginStatusTime = 0;

				// Direct connection info
				Tlv *tlvDirect = tlv(TLV_USER_DC_INFO);
				if(tlvDirect)
				{
					ICQBuffer info(*tlvDirect);
					unsigned long  realIP;
					unsigned short port;
					char mode, version, junk;
					info >> realIP;
					info.incReadPos(2);
					info >> port;
					if (realIP == 0x7F000001)
						realIP = 0;
                    unsigned long oldip = data->getRealIP();
                    data->setRealIP(htonl(realIP));
                    bChanged |= oldip != data->getRealIP();
                    data->setPort(port);
					unsigned long DCcookie;
					info >> mode >> junk >> version >> DCcookie;
                    data->setDCcookie(DCcookie);
					info.incReadPos(8);
					info
						>> infoUpdateTime
						>> pluginInfoTime
						>> pluginStatusTime;
                    if (mode == MODE_DENIED || mode != MODE_DIRECT && mode != MODE_INDIRECT)
                        mode = MODE_INDIRECT;
                    data->setMode(mode);
                    data->setVersion(version);
				}

				Tlv *tlvPlugin = tlv(0x0011);
                if(tlvPlugin && data->getUin())
				{
					ICQBuffer info(*tlvPlugin);
					char type;
					unsigned long time;
					info >> type;
					info.unpack(time);
					plugin p;
					unsigned plugin_index;
					unsigned long plugin_status;
					switch (type){
						case 1:
                            m_client->addFullInfoRequest(data->getUin());
							break;
						case 2:
                            if (!m_client->getInvisible() && data->getInvisibleId() == 0 || m_client->getInvisible() && data->getVisibleId()){
								info.incReadPos(6);
								info.unpack((char*)p, sizeof(p));
                                data->setPluginInfoTime(time);
								for (plugin_index = 0; plugin_index < PLUGIN_NULL; plugin_index++)
									if (!memcmp(p, m_client->plugins[plugin_index], sizeof(p)))
										break;
								switch (plugin_index)
								{
									case PLUGIN_PHONEBOOK:
										log(L_DEBUG, "Updated phonebook");
                                        m_client->addPluginInfoRequest(data->getUin(), plugin_index);
										break;
									case PLUGIN_PICTURE:
										log(L_DEBUG, "Updated picture");
										// when buddyID -> new avatar support, no need to ask for old picture plugin
                                        if(data->getBuddyID() == 0 || data->getBuddyHash().size() != 16) {
                                            data->setBuddyID(0);
                                            m_client->addPluginInfoRequest(data->getUin(), plugin_index);
										}
										break;
									case PLUGIN_QUERYxINFO:
										log(L_DEBUG, "Updated info plugin list");
                                        m_client->addPluginInfoRequest(data->getUin(), plugin_index);
										break;
									default:
										if (plugin_index >= PLUGIN_NULL)
											log(L_WARN, "Unknown plugin sign (%04X %04X)",
													type, plugin_index);
								}
							}
							break;
						case 3:
							info.incReadPos(6);
							info.unpack((char*)p, sizeof(p));
							info.incReadPos(1);
							info.unpack(plugin_status);
                            data->setPluginStatusTime(time);
							for (plugin_index = 0; plugin_index < PLUGIN_NULL; plugin_index++)
								if (!memcmp(p, m_client->plugins[plugin_index], sizeof(p)))
									break;
							switch (plugin_index){
								case PLUGIN_FOLLOWME:
                                    if (data->getFollowMe() == plugin_status)
										break;
                                    data->setFollowMe(plugin_status);
									bChanged = true;
									break;
								case PLUGIN_FILESERVER:
                                    if ((data->getSharedFiles() != 0) == (plugin_status != 0))
										break;
                                    data->setSharedFiles(plugin_status != 0);
									bChanged = true;
									break;
								case PLUGIN_ICQPHONE:
                                    if (data->getICQPhone() == plugin_status)
										break;
                                    data->setICQPhone(plugin_status);
									bChanged = true;
									break;
								default:
									if (plugin_index >= PLUGIN_NULL)
										log(L_WARN, "Unknown plugin sign (%04X %04X)", type, plugin_index);
							}
							break;

					}
				}
				else
				{
                    data->setInfoUpdateTime(infoUpdateTime);
                    data->setPluginInfoTime(pluginInfoTime);
                    data->setPluginStatusTime(pluginStatusTime);
                    if (    !m_client->getDisableAutoUpdate() 
                        && (!m_client->getInvisible() || data->getVisibleId())
                        && (m_client->getInvisible()  || data->getInvisibleId() == 0))
                    {
						if (infoUpdateTime == 0)
							infoUpdateTime = 1;
                        if (infoUpdateTime != data->getInfoFetchTime())
                            m_client->addFullInfoRequest(data->getUin());
                        if (   data->getPluginInfoTime() != data->getPluginInfoFetchTime() 
                            && data->getPluginInfoTime())
                            m_client->addPluginInfoRequest(data->getUin(), PLUGIN_QUERYxINFO);
                        if (   data->getPluginInfoTime() != data->getPluginInfoFetchTime() 
                            || data->getPluginStatusTime() != data->getPluginStatusFetchTime()){
                            if (data->getSharedFiles())
                            {
                                data->setSharedFiles(false);
								bChanged = true;
							}
                            if (data->getFollowMe())
                            {
                                data->setFollowMe(0);
								bChanged = true;
							}
                            if (data->getICQPhone())
                            {
                                data->setICQPhone(0);
								bChanged = true;
							}
                            if (data->getPluginStatusTime())
                                m_client->addPluginInfoRequest(data->getUin(), PLUGIN_QUERYxSTATUS);
						}
					}
				}
                if (data->getInvisible())
                {
                    data->setInvisible(false);
					bChanged = true;
				}
                if (bChanged)
                    EventContact(contact, EventContact::eChanged).process();
                if (data->getStatus() != prevStatus || bAwayChanged){
					unsigned status = STATUS_OFFLINE;
                    if ((data->getStatus() & 0xFFFF) != ICQ_STATUS_OFFLINE)
                    {
						status = STATUS_ONLINE;
                        if (data->getStatus() & ICQ_STATUS_DND)
                            status = STATUS_DND;
                        else if (data->getStatus() & ICQ_STATUS_OCCUPIED)
                            status = STATUS_OCCUPIED;
                        else if (data->getStatus() & ICQ_STATUS_NA)
                            status = STATUS_NA;
                        else if (data->getStatus() & ICQ_STATUS_AWAY)
                            status = STATUS_AWAY;
                        else if (data->getStatus() & ICQ_STATUS_FFC)
                            status = STATUS_FFC;
					}
                    if((status == STATUS_ONLINE) && (data->getClass() & CLASS_AWAY))
						status = STATUS_AWAY;
					StatusMessage *m = new StatusMessage();
					m->setContact(contact->id());
					m->setClient(m_client->dataName(data));
					m->setStatus(status);
					m->setFlags(MESSAGE_RECEIVED);
					EventMessageReceived e(m);
					if(!e.process())
						delete m;
                    if (    !contact->getIgnore() 
                        && (data->getClass() & CLASS_AWAY) == 0 
                        && ((data->getStatus() & 0xFF) == ICQ_STATUS_ONLINE && (prevStatus & 0xFF) != ICQ_STATUS_ONLINE || bAwayChanged) 
                        && ((prevStatus & 0xFFFF) != ICQ_STATUS_OFFLINE || data->getOnlineTime() > m_client->data.owner.getOnlineTime())
                        )
                    {
						EventContact e(contact, EventContact::eOnline);
						e.process();
					}
                    if (    !m_client->getDisableAutoReplyUpdate() 
                        && (data->getStatus() & 0xFF) != ICQ_STATUS_ONLINE 
                        && (!m_client->getInvisible() || data->getVisibleId()) 
                        && (m_client->getInvisible() || data->getInvisibleId() == 0)
                        )
                        m_client->addPluginInfoRequest(data->getUin(), PLUGIN_AR);
				}
			}
			break;
		}