char* fnMy_MkTemp(char* templatestr)
{
	char* pXs=NULL;
	char numbuf[50]={'\0'};
	int count=0;
	char* pPid=NULL;

	char termchar = '\0';
	char letter = 'a';
	char letter1 = 'a';


	if (templatestr && (pXs = strstr(templatestr, (char *)"XXXXXX")))
	{
		// generate temp name
		termchar = pXs[6];
		ltoa(GetThreadID(), numbuf, 16);
//		numbuf[sizeof(numbuf)-1] = '\0';
		numbuf[strlen(numbuf)-1] = '\0';
		// beware! thread IDs are 8 hex digits on NW 4.11 and only the
		// lower digits seem to change, whereas on NW 5 they are in the
		// range of < 1000 hex or 3 hex digits in length. So the following
		// logic ensures we use the least significant portion of the number.
		if (strlen(numbuf) > 5)
			pPid = &numbuf[strlen(numbuf)-5];
		else
			pPid = numbuf;

/**
		Backtick operation uses temp files that are stored under NWDEFPERLTEMP
		directory. They are temporarily used and then cleaned up after usage.
		In cases where multiple backtick operations are used that call some
		complex scripts, new temp files will be created before the old ones are
		deleted. So, we need to have a provision to create many temp files.
		Hence the below logic. It is found that provision for 26 files may
		not be enough in some cases.

		This below logic allows 26 files (like, pla00015.tmp through plz00015.tmp)
		plus 6x26=676 (like, plaa0015.tmp through plzz0015.tmp)
**/

		letter = 'a';
		do
		{
			sprintf(pXs, (char *)"%c%05.5s", letter, pPid);
			pXs[6] = termchar;
			if (access(templatestr, 0) != 0)	// File does not exist
			{
				return templatestr;
			}
			letter++;
		} while (letter <= 'z');

		letter1 = 'a';
		do
		{
			letter = 'a';
			do
			{
				sprintf(pXs, (char *)"%c%c%04.5s", letter1, letter, pPid);
				pXs[6] = termchar;
				if (access(templatestr, 0) != 0)	// File does not exist
				{
					return templatestr;
				}
				letter++;
			} while (letter <= 'z');
			letter1++;
		} while (letter1 <= 'z');

		errno = ENOENT;
		return NULL;
	}
	else
	{
		errno = EINVAL;
		return NULL;
	}
}