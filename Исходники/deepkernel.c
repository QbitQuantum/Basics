//this unit will contain the functions and other crap used by the hider function
BOOLEAN CheckImageName(IN PUNICODE_STRING FullImageName, IN char* List,int listsize)
{
#ifndef AMD64
	/*
	pre:List has been initialized and all entries are UPPERCASE. Each entry is seperated
	    by a 0-marker so just setting the pointer ro the start and doing a compare will work

	*/
	ANSI_STRING tempstring;
	int i;

	DbgPrint("Checking this image name...\n");
	RtlZeroMemory(&tempstring,sizeof(ANSI_STRING));
	if (RtlUnicodeStringToAnsiString(&tempstring,FullImageName,TRUE)== STATUS_SUCCESS)
	{
		char *p;
		INT_PTR modulesize;
		__try
		{
			RtlUpperString(&tempstring,&tempstring);

			p=List;
	
			for (i=0;i<listsize;i++)
			{
				if (List[i]=='\0')
				{
					modulesize=i-(INT_PTR)(p-List);
					if (modulesize>=0)
					{	
						DbgPrint("Checking %s with %s\n",&tempstring.Buffer[tempstring.Length-modulesize],p);

						if ((tempstring.Length>=modulesize) && (strcmp(p,&tempstring.Buffer[tempstring.Length-modulesize])==0))
						{
							//we have a match!!!
							DbgPrint("It's a match with %s\n",p);
							return TRUE;	
						}						
	
					}
					p=&List[i+1];
				}
	
			}
		
			
		}
		__finally
		{
			RtlFreeAnsiString(&tempstring);	
		}
	}