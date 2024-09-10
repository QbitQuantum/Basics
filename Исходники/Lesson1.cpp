char *toip(int myhost)
{
	char x[10];
	char *cng;
	_gcvt((myhost & 0xff000000)/0x01000000, 5, x);
	cng = strstr(x, ".");
	if(cng != NULL)
	{
		*cng = '\0';
	}
	strcpy(qchar, x);
	strcat(qchar, ".");
	_gcvt((myhost & 0x00ff0000)/0x00010000, 5, x);
	cng = strstr(x, ".");
	if(cng != NULL)
	{
		*cng = '\0';
	}
	strcat(qchar, x);
	strcat(qchar, ".");
	_gcvt((myhost & 0x0000ff00)/256, 5, x);
	cng = strstr(x, ".");
	if(cng != NULL)
	{
		*cng = '\0';
	}
	strcat(qchar, x);
	strcat(qchar, ".");
	_gcvt((myhost & 0x000000ff), 5, x);
	cng = strstr(x, ".");
	if(cng != NULL)
	{
		*cng = '\0';
	}
	strcat(qchar, x);
	return qchar;

}