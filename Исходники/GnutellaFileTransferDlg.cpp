string CGnutellaFileTransferDlg::FormatWithCommas(unsigned int num)
{
	string ret;

	char buf[32];
	char buf2[sizeof(buf)*2];
	memset(buf,0,sizeof(buf));
	memset(buf2,0,sizeof(buf2));

	_itoa(num,buf,10);

	char *ptr=&buf[strlen(buf)-1];	// last char
	char *ptr2=&buf2[sizeof(buf2)-2];	// last char
	int i=0;
	while(1)
	{
		if(i>0)
		{
			if(i%3==0)
			{
				*ptr2=',';
				ptr2--;
			}
		}

		*ptr2=*ptr;

		if(ptr==buf)
		{
			break;
		}

		ptr--;
		ptr2--;
		i++;
	}
	*ptr2=*ptr;
	
	ret=ptr2;

	return ret;
}