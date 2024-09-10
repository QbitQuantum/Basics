char* SosUtil::floatToString(float val, int precision, char* displayString)
{
	int pos1=0,pos2=0;
	char* buf = _fcvt(val,precision,&pos1,&pos2);
	char buf2[50] = {0};

	int count = 0;
	if(pos1 < 0)
	{
		buf2[0] = '.';
		count++;
		while(pos1 < 0)
		{
			pos1++;
			buf2[count] = '0';
			count++;
		}
		strcpy(buf2+count,buf);
	}
	else if(pos1 > 0)
	{
		strncpy(buf2,buf,pos1);
		count = strlen(buf2);

		buf2[pos1]='.';
		
		strcpy(buf2 + pos1 +1,buf + pos1);

	}
	else
	{
		buf2[0]='.';
		strcpy(buf2+1,buf);
	}
	
	if(val < 0)
	{
		displayString[0] = '-';
		strcpy(displayString + 1,buf2);
	}
	else
	{
		
		strcpy(displayString,buf2);
	}
	return displayString;
   
}