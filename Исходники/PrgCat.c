int SaveAll(int usernumber, struct ProgramCategory *start)
{
	BPTR fh;
	char buffer[257], filnamn[257];
	struct ProgramData *pek;

	sprintf(filnamn, "NiKom:Users/%d/%d/ProgramData", usernumber/100, usernumber);

	if(start != NULL)
	{
		if(fh = Open(filnamn, MODE_NEWFILE))
		{
			while(start != NULL)
			{
				sprintf(buffer,"[%s]\n",start->namn);
				FPuts(fh, buffer);
				if(start->datastart != NULL)
				{
					pek = start->datastart;
					while(pek != NULL)
					{
						sprintf(buffer,"%s=%s\n",pek->typ,pek->data);
						FPuts(fh, buffer);
						pek = pek->next;
					}
				}
				start = start->next;
			}
		
			Close(fh);
			return(1);
		}
	}
	
	return(0);
}