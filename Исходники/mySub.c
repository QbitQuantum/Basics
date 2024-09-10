void  uart0Printf(UINT8 *str)
{
	UINT8  i;
	
	for(i=0;i<strlen(str);i++)
	    fputchar(str[i]);
}