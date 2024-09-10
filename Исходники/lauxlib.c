LUALIB_API int isLic()
{
	int flag=0;
	int key[6]={1,0,1,0,0,0};
	FILE *in = fopen("control/li.lic","r");	
	char buf[1024];
	if(in==NULL)
	{
		printf("can not open 1.lic");
		flag=0;
	}
	else
	{
		fgets(buf,1024,in);
		fclose(in);
		printf("buf:%s\n",buf);	

		unsigned int resultSize=0;
		char *buf2=base64Decode(buf,resultSize,true);
		printf("base64Decode buf2:%s\n",buf2);
		for(int i=0;i<strlen(buf2);i++)
		{
			buf2[i]=buf2[i]^key[i%6];
		}
		printf("buf2^:%s\n",buf2);



		char type=buf2[0];
		printf("type:%c\n",type);
		char* yearc = new char[11];
		char* macc = new char[strlen(buf2)-11];
		for(int i=0;i<10;i++)
		{
			yearc[i]=buf2[i+1];
		}
		yearc[10]='\0';
		for(int i=0;i<strlen(buf2)-11;i++)
		{
			macc[i]=buf2[i+11];
		}
		if(type=='0'||type=='3')
		{
			flag=2;
			printf("yearc:%s\n",yearc);
			int        nYear, nMonth, nDay; 
			sscanf_s(yearc, "%d-%d-%d", &nYear, &nMonth, &nDay);
			nMonth=nMonth-1;
			nYear=nYear-1900;
			printf("year:%d,month:%d,day:%d\n",nYear,nMonth,nDay);
			time_t t = time(0);     
			tm *t1=localtime(&t);
			printf("tyear:%d,tmonth:%d,tday:%d\n",t1->tm_year,t1->tm_mon,t1->tm_mday);
			int year =t1->tm_year;
			
			if(year<nYear)
			{
				flag=1;
			}
			else if(year==nYear)
			{
				if(t1->tm_mon<nMonth)
				{
					flag=1;
				}
				else if(t1->tm_mon==nMonth)
				{
					if(t1->tm_mday<=nDay)
					{
						flag=1;
					}
				}
			}
		}
		 if(type=='1'||type=='3')
		{
			flag=3;
			printf("macc:%s\n",macc);
			char* mac=getMac();
			printf("mac:%s\n",mac);
			if(strstr(macc,mac)!=NULL)
			{
				flag=1;
			}			 
		}
	}
	printf("flag:%d\n",flag);
	return flag;
}  