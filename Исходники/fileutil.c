ubyte * readFile2(char *name,int *lenptr)
{
ubyte *buf;
ulong len;
FILE *fp;

	if ( (fp = fopen(name,"rb")) == NULL )
		return NULL;

	*lenptr = -1;

	if ( (len = FileLengthofFH(fp)) == FileLengthofFH_Error ) {
		fclose(fp);
		return NULL;
	}

	if ( (buf = malloc(len)) == NULL ) {
		fclose(fp);
		return NULL;
	}

	if (FRead(fp,buf,len) != len) {
		printf("Failed to read the whole file: %s\n", name);
		exit(EXIT_FAILURE);
	}

	fclose(fp);

	*lenptr = len;

return buf;
}