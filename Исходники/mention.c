void compare_term_list(FILE* listfile, long totalchar,char*textlist)
{	
	int listcontainer = text_ini;
	int term_len = line_ini;
	int shouldcount=0;
	int list_i=0,term_i=0;
	char listterm_ch;
	char** listterm;
	listterm = malloc(listcontainer*sizeof(char*));
	assert(listterm);
	memset(listterm,0,listcontainer+1);
	listterm[list_i] = malloc((term_len+1)*sizeof(char));
	assert(listterm[list_i]);
	memset(listterm[list_i],0,term_len+1);
	long charOffset=0,termOffset=0;
	int afterlen_list;
	int readindex = 0;
	int readindex_list = 0;
	while((listterm_ch=fgetc(listfile))!=EOF)
	{	
		if (listterm_ch != '\n')
		{
			listterm[list_i][term_i] = listterm_ch;
			term_i++;
		}
		else if (listterm_ch == '\n')
		{
			list_i++;
			term_len = term_i;
			if ((list_i) == listcontainer -1)
			{
				listcontainer = listcontainer*2;
				listterm = realloc(listterm, listcontainer*sizeof(char*));
				assert(listterm);
				afterlen_list = listcontainer/2+1;
				memset(listterm+afterlen_list-2,0,(afterlen_list)*sizeof(char*));
			}
			listterm[list_i] = malloc((term_len+1)*sizeof(char));
			assert(listterm[list_i]);
			memset(listterm[list_i],0,term_len+1);
			term_i = 0;
		}
	}
	int totalterm = list_i;
	while (readindex < sizeof(textlist)/sizeof(char*))
	{	
		if (isalnum(textlist[readindex]) && shouldcount == 0)
		{
			termOffset++;
			shouldcount = 1;
		}
		if (!isalnum(textlist[readindex]))
		{
			shouldcount = 0;
		}
		while (readindex_list < totalterm)
		{	
			if (strncasecmp(textlist,listterm[readindex_list],readindex-len(listterm[readindex_list])) ==0)
			{	
				charOffset = charOffset+len(listterm[readindex_list]);
				termOffset = readindex;
				fprintf(stdout,"%ld,%ld,%s\n",charOffset,termOffset,listterm[readindex_list]);
			}
			else
			{
				readindex_list++;
			}
		}
		readindex_list = 0;
		readindex++;
	}
	free(textlist);
	free(listterm);
}