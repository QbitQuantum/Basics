char * CxMemFile::GetS(char *string, int32_t n)
{
	n--;
	int32_t c,i=0;
	while (i<n){
		c = GetC();
		if (c == EOF) return 0;
		string[i++] = (char)c;
		if (c == '\n') break;
	}
	string[i] = 0;
	return string;
}