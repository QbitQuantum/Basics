static int format_Options(struct ALN_Options * op)
{ 
	int len;
	char * ptr;

	if(op->spt == NULL || op->read == NULL) return -1;

	ptr = op->spt + strlen(op->spt) - 3;
	if(strcmp(ptr, "spt") != 0)
	{
		fprintf(stderr, "File type not supported: %s\r\n", op->spt);
		return -2;
	}

	ptr = getFileType(op->read);
	if(strcmp(ptr, "fa") != 0 && strcmp(ptr, "fasta") != 0)
	{
		fprintf(stderr, "File type not supported: %s\r\n", op->read);
		return -2;
	}

	if(op->prefix == NULL) return -1;

	len = 0;
	if(op->dir != NULL) len = strlen(op->dir);
	len += strlen(op->prefix);

	op->pac = (char *)malloc(len + 6);
	op->si = (char *)malloc(len + 6);

	if(op->dir != NULL)
	{
		strcpy(op->pac, op->dir);
		strcpy(op->si, op->dir);

		strcat(op->pac, op->prefix);
		strcat(op->si, op->prefix);
	}
	else
	{
		strcpy(op->pac, op->prefix);
		strcpy(op->si, op->prefix);
	}

	strcat(op->pac, ".pac");
	strcat(op->si, ".si");

	op->hash = (char *)malloc(strlen(op->spt) + 5);
	strcpy(op->hash, op->spt);
	strcat(op->hash, ".hsh");

	if(op->verbose & 0x80) op->verbose = 0x80;
	return 0;
}