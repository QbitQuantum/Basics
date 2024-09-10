bool P1MeterBase::MatchLine()
{
	if ((strlen((const char*)&l_buffer)<1)||(l_buffer[0]==0x0a))
		return true; //null value (startup)
	uint8_t i;
	uint8_t found=0;
	Match *t;
	char value[20]="";
	std::string vString;

	for(i=0;(i<sizeof(matchlist)/sizeof(Match))&(!found);i++)
	{
		t = &matchlist[i];
		switch(t->matchtype)
		{
		case ID:
			// start of data
			if(strncmp(t->key, (const char*)&l_buffer, strlen(t->key)) == 0) {
				m_linecount=1;
				found=1;
			}
			continue; // we do not process anything else on this line
			break;
		case EXCLMARK:
			// end of data
			if(strncmp(t->key, (const char*)&l_buffer, strlen(t->key)) == 0) {
				l_exclmarkfound=1;
				found=1;
			}
			break;
		case STD:
			if(strncmp(t->key, (const char*)&l_buffer, strlen(t->key)) == 0)
				found=1;
			break;
		case DEVTYPE:
			if(m_gasmbuschannel==0){
				vString=(const char*)t->key+3;
				if (strncmp(vString.c_str(), (const char*)&l_buffer+3, strlen(t->key)-3) == 0)
					found=1;
				else
					i+=100; // skip matches with any other gas lines - we need to find the M0-Bus channel first
			}
			break;
		case GAS:
			if(strncmp((m_gasprefix+(t->key+3)).c_str(), (const char*)&l_buffer, strlen(t->key)) == 0){
				found=1;
			}
			if (m_p1version>=4)
				i+=100; // skip matches with any DSMR v2 gas lines
			break;
		case LINE17:
			if(strncmp((m_gasprefix+(t->key+3)).c_str(), (const char*)&l_buffer, strlen(t->key)) == 0){
				m_linecount = 17;
				found=1;
			}
			break;
		case LINE18:
			if((m_linecount == 18)&&(strncmp(t->key, (const char*)&l_buffer, strlen(t->key)) == 0))
				found=1;
			break;
		} //switch

		if(!found)
			continue;

		if (l_exclmarkfound) {
			if (m_p1version==0)
			{
				_log.Log(LOG_STATUS,"P1 Smart Meter: Meter is pre DSMR 4.0 - using DSMR 2.2 compatibility");
				m_p1version=2;
			}
			time_t atime=mytime(NULL);
			if (difftime(atime,m_lastUpdateTime)>=m_ratelimit) {
				m_lastUpdateTime=atime;
				sDecodeRXMessage(this, (const unsigned char *)&m_power, "Power", 255);
				if (m_voltagel1) {
					SendVoltageSensor(0, 1, 255, m_voltagel1, "Voltage L1");
					if (m_voltagel2)
						SendVoltageSensor(0, 2, 255, m_voltagel2, "Voltage L2");
					if (m_voltagel3)
						SendVoltageSensor(0, 3, 255, m_voltagel3, "Voltage L3");
				}
				if ( (m_gas.gasusage>0)&&( (m_gas.gasusage!=m_lastgasusage)||(difftime(atime,m_lastSharedSendGas)>=300) ) ){
					//only update gas when there is a new value, or 5 minutes are passed
					if (m_gasclockskew>=300){ // just accept it - we cannot sync to our clock
						m_lastSharedSendGas=atime;
						m_lastgasusage=m_gas.gasusage;
						sDecodeRXMessage(this, (const unsigned char *)&m_gas, "Gas", 255);
					}
					else if (atime>=m_gasoktime){
						struct tm ltime;
						localtime_r(&atime, &ltime);
						char myts[16];
						sprintf(myts,"%02d%02d%02d%02d%02d%02dW",ltime.tm_year%100,ltime.tm_mon+1,ltime.tm_mday,ltime.tm_hour,ltime.tm_min,ltime.tm_sec);
						if (ltime.tm_isdst)
						myts[12]='S';
						if ( (m_gastimestamp.length()>13) || (strncmp((const char*)&myts,m_gastimestamp.c_str(),m_gastimestamp.length())>=0) )
						{
							m_lastSharedSendGas=atime;
							m_lastgasusage=m_gas.gasusage;
							m_gasoktime+=300;
							sDecodeRXMessage(this, (const unsigned char *)&m_gas, "Gas", 255);
						}
						else // gas clock is ahead
						{
							struct tm gastm;
							gastm.tm_year = atoi(m_gastimestamp.substr(0, 2).c_str()) + 100;
							gastm.tm_mon = atoi(m_gastimestamp.substr(2, 2).c_str()) - 1;
							gastm.tm_mday = atoi(m_gastimestamp.substr(4, 2).c_str());
							gastm.tm_hour = atoi(m_gastimestamp.substr(6, 2).c_str());
							gastm.tm_min = atoi(m_gastimestamp.substr(8, 2).c_str());
							gastm.tm_sec = atoi(m_gastimestamp.substr(10, 2).c_str());
							if (m_gastimestamp.length()==12)
								gastm.tm_isdst = -1;
							else if (m_gastimestamp[12]=='W')
								gastm.tm_isdst = 0;
							else
								gastm.tm_isdst = 1;

							time_t gtime=mktime(&gastm);
							m_gasclockskew=difftime(gtime,atime);
							if (m_gasclockskew>=300){
								_log.Log(LOG_ERROR, "P1 Smart Meter: Unable to synchronize to the gas meter clock because it is more than 5 minutes ahead of my time");
							}
							else {
								m_gasoktime=gtime;
								_log.Log(LOG_STATUS, "P1 Smart Meter: Gas meter clock is %i seconds ahead - wait for my clock to catch up", (int)m_gasclockskew);
							}
						}
					}
				}
			}
			m_linecount=0;
			l_exclmarkfound=0;
		}
		else
		{
			vString=(const char*)&l_buffer+t->start;
			int ePos=t->width;
			ePos=vString.find_first_of("*)");

			if (ePos==std::string::npos)
			{
				// invalid message: value not delimited
				_log.Log(LOG_NORM,"P1 Smart Meter: Dismiss incoming - value is not delimited in line \"%s\"", l_buffer);
				return false;
			}

			if (ePos>19)
			{
				// invalid message: line too long
				_log.Log(LOG_NORM,"P1 Smart Meter: Dismiss incoming - value in line \"%s\" is oversized", l_buffer);
				return false;
			}

			if (ePos>0)
			{
				strcpy(value,vString.substr(0,ePos).c_str());
#ifdef _DEBUG
				_log.Log(LOG_NORM,"P1 Smart Meter: Key: %s, Value: %s", t->topic,value);
#endif
			}

			unsigned long temp_usage = 0;
			float temp_volt = 0;
			char *validate=value+ePos;

			switch (t->type)
			{
			case P1TYPE_VERSION:
				if (m_p1version==0)
					_log.Log(LOG_STATUS,"P1 Smart Meter: Meter reports as DSMR %c.%c", value[0], value[1]);
				m_p1version=value[0]-0x30;
				break;
			case P1TYPE_MBUSDEVICETYPE:
				temp_usage = (unsigned long)(strtod(value,&validate));
				if (temp_usage == 3) {
					m_gasmbuschannel = (char)l_buffer[2];
					m_gasprefix[2]=m_gasmbuschannel;
					_log.Log(LOG_STATUS,"P1 Smart Meter: Found gas meter on M-Bus channel %c", m_gasmbuschannel);
				}
				break;
			case P1TYPE_POWERUSAGE1:
				temp_usage = (unsigned long)(strtod(value,&validate)*1000.0f);
				if (!m_power.powerusage1 || m_p1version >= 4)
					m_power.powerusage1 = temp_usage;
				else if (temp_usage - m_power.powerusage1 < 10000)
					m_power.powerusage1 = temp_usage;
				break;
			case P1TYPE_POWERUSAGE2:
				temp_usage = (unsigned long)(strtod(value,&validate)*1000.0f);
				if (!m_power.powerusage2 || m_p1version >= 4)
					m_power.powerusage2 = temp_usage;
				else if (temp_usage - m_power.powerusage2 < 10000)
					m_power.powerusage2 = temp_usage;
				break;
			case P1TYPE_POWERDELIV1:
				temp_usage = (unsigned long)(strtod(value,&validate)*1000.0f);
				if (!m_power.powerdeliv1 || m_p1version >= 4)
					m_power.powerdeliv1 = temp_usage;
				else if (temp_usage - m_power.powerdeliv1 < 10000)
					m_power.powerdeliv1 = temp_usage;
				break;
			case P1TYPE_POWERDELIV2:
				temp_usage = (unsigned long)(strtod(value,&validate)*1000.0f);
				if (!m_power.powerdeliv2 || m_p1version >= 4)
					m_power.powerdeliv2 = temp_usage;
				else if (temp_usage - m_power.powerdeliv2 < 10000)
					m_power.powerdeliv2 = temp_usage;
				break;
			case P1TYPE_USAGECURRENT:
				temp_usage = (unsigned long)(strtod(value,&validate)*1000.0f);	//Watt
				if (temp_usage < 17250)
					m_power.usagecurrent = temp_usage;
				break;
			case P1TYPE_DELIVCURRENT:
				temp_usage = (unsigned long)(strtod(value,&validate)*1000.0f);	//Watt;
				if (temp_usage < 17250)
					m_power.delivcurrent = temp_usage;
				break;
			case P1TYPE_VOLTAGEL1:
				temp_volt = strtof(value,&validate);
				if (temp_volt < 300)
					m_voltagel1 = temp_volt; //Voltage L1;
				break;
			case P1TYPE_VOLTAGEL2:
				temp_volt = strtof(value,&validate);
				if (temp_volt < 300)
					m_voltagel2 = temp_volt; //Voltage L2;
				break;
			case P1TYPE_VOLTAGEL3:
				temp_volt = strtof(value,&validate);
				if (temp_volt < 300)
					m_voltagel3 = temp_volt; //Voltage L3;
				break;
			case P1TYPE_GASTIMESTAMP:
				m_gastimestamp = std::string(value);
				break;
			case P1TYPE_GASUSAGE:
			case P1TYPE_GASUSAGEDSMR4:
				temp_usage = (unsigned long)(strtod(value,&validate)*1000.0f);
				if (!m_gas.gasusage || m_p1version >= 4)
					m_gas.gasusage = temp_usage;
				else if (temp_usage - m_gas.gasusage < 20000)
					m_gas.gasusage = temp_usage;
				break;
			}

			if (ePos>0 && ((validate - value) != ePos)) {
				// invalid message: value is not a number
				_log.Log(LOG_NORM,"P1 Smart Meter: Dismiss incoming - value in line \"%s\" is not a number", l_buffer);
				return false;
			}

			if (t->type == P1TYPE_GASUSAGEDSMR4){ // need to get timestamp from this line as well
				vString=(const char*)&l_buffer+11;
				m_gastimestamp=vString.substr(0,13);
#ifdef _DEBUG
				_log.Log(LOG_NORM,"P1 Smart Meter: Key: gastimestamp, Value: %s", m_gastimestamp);
#endif
			}
		}
	}
	return true;
}