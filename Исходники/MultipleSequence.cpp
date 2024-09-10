bool MultipleSequence::loadInformation(FILE* fp, int* no, char*** seqFileName, int** seqIndex)
{
	ASSERT(fp);

	char buf[MAX_BUF], *p, *q;
	int i;

	int hNumberLen   = strlen(H_NUMBER);
	int hFileNameLen = strlen(H_FILE_NAME);

	while (fgets(buf, MAX_BUF, fp))
	{
		// Number : 2
		if (!STRNICMP(buf, H_NUMBER, hNumberLen))
		{
			*no = atoi(buf+hNumberLen);
			*seqFileName = new char*[*no];
			*seqIndex    = new int[*no];
		}
		else if (!STRNICMP(buf, H_FILE_NAME, hFileNameLen))
		{
			p = buf+hFileNameLen;
			i = atoi(p);
			ASSERT(i < *no);
			p = strchr(p, H_FILE_DELIMETER);		// start of filename
			ASSERT(p);
			q = strchr(++p, H_FILE_DELIMETER);	// end of filename
			ASSERT(q);
			*q = '\0';  q++;							// start of index
			p = StringEx::trim(p);					// trim
			(*seqIndex)[i] = atoi(q);
			(*seqFileName)[i] = new char[strlen(p)+1];
			strcpy((*seqFileName)[i], p);
			if (i == *no-1) return true;
		}
	}

	return false;
}