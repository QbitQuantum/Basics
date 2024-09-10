void PA6C::filterData(char *fieldData, goCoord *current, uint8_t *sID, uint8_t *fID)
{
	if(!(*fID))
	{
		if(strstr(fieldData,GPGGA)!=NULL)
		{		
			*sID = 4;
			(*fID)++;
			return;
		}
		if(strstr(fieldData,GPGSA)!=NULL)
		{		
			*sID |= 2;
			(*fID)++;
			return;
		}
		if(strstr(fieldData,GPGSV)!=NULL)
			return;
		if(strstr(fieldData,GPRMC)!=NULL)
		{		
			*sID |= 1;
			(*fID)++;
			return;
		}
		if(strstr(fieldData,GPVTG)!=NULL)
		{		
			*sID |= 0x08;
			(*fID)++;
			return;
		}
		*fID = 0;
	}
	if(!(*sID))
		*fID = 0;
	if(*sID == 4)
	{
		switch(*fID)
		{
			case 6:
				current->positionFixInd = atoi(fieldData);
				break;
			case 7:	
				current->satellitesUsed = atoi(fieldData);
				break;
			case 9:
				current->altitude = atol(fieldData);
				break;
			case 14:
				*fID = 0;
				return;
				break;
		}
		(*fID)++;
	}
	if(*sID == 6)
	{
		switch(*fID)
		{
			case 1:
				break;
			case 2:	
				current->mode2 = atoi(fieldData);
				break;
			case 15:
				current->pdop = (uint16_t)(atof(fieldData)*100);
				break;
			case 16:	
				current->hdop = (uint16_t)(atof(fieldData)*100);
				break;
			case 17:
				current->vdop = (uint16_t)(atof(fieldData)*100);
				*fID = 0;
				return;
				break;
		}
		(*fID)++;
	}	
	if(*sID == 7)
	{
		switch(*fID)
		{
			case 1:
				fieldData[6] = '\0';
				strcpy(current->time,fieldData);
				break;
			case 2:
				if(fieldData[0] == 'A')
					current->signalLock = true;
				else
					current->signalLock = false;
				break;
			case 3:	
				strcpy(current->latitude,fieldData);
				break;
			case 4:
				current->ns = fieldData[0];
				break;
			case 5:
				strcpy(current->longitude,fieldData);
				break;
			case 6:	
				current->ew = fieldData[0];
				break;
			case 8:
				current->course = atoi(fieldData);
				break;
			case 9:
				strcpy(current->date,fieldData);
				break;
			case 12:
				*fID = 0;
				return;
				break;
		}
		(*fID)++;
	}
	if(*sID == 0x0F)
	{
		switch(*fID)
		{
			case 7:
				current->speed = atol(fieldData);
				break;
			case 9:
				*fID = 0;
				return;
				break;
		}
		(*fID)++;
	}
}