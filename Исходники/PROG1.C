/* main encoder */
void Encode (void)
{
	unsigned int dictpos, deleteflag, sectorlen;
	unsigned long bytescompressed;

	InitEncode();

	dictpos = deleteflag = 0;

	bytescompressed = 0;

	while (1)
	{
		/* delete old data from dictionary */
		if (deleteflag) DeleteData(dictpos);

		/* grab more data to compress */
		if ((sectorlen = LoadDict(dictpos)) == 0) break;

		/* hash the data */
		HashData(dictpos, sectorlen);

		/* find dictionary matches */
		DictSearch(dictpos, sectorlen);

		bytescompressed += sectorlen;

		printf("\r%ld", bytescompressed);

		dictpos += SECTORLEN;

		/* wrap back to beginning of dictionary when its full */
		if (dictpos == DICTSIZE)
		{
			dictpos = 0;
			deleteflag = 1;   /* ok to delete now */
		}
	}

	/* Send EOF flag */
	SendMatch(MAXMATCH + 1, 0);

	/* Flush bit buffer */
	if (bitsin) SendBits(0, 8 - bitsin);

	return;
}