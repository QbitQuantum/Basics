lasErr FUNCTION c_lswrit(FILE	**fd, const char *key, int	*clen, int	*dlen, 
	const char *cbuf, const unsigned char *dbuf, const char *dtype)
{
FILE *fp;
char header[HDRL];
char len[LENL];

fp = *fd;
if (strlen(key) >= KEYL)
    {
    c_errmsg("Error: Key length too long.  Key should be truncated.",
             "lswrit-key", NON_FATAL);
    }

/*Seek to end-of-file.*/
FSEEK64(*fd, 0, 2);

if (*clen > 0)
   sprintf(len,"%-d/%-d",*clen,*dlen);
else
   sprintf(len,"%-d",*dlen);

sprintf (header,"%-*s%-*s%-*s",LENL,len,TYPL,dtype,KEYL-1,key);
FWRITE(header,sizeof(char),HDRL,fp);

if (*clen > 0)
    FWRITE(cbuf,sizeof(char), *clen,fp);

if (*dlen > 0)
    FWRITE(dbuf,sizeof(char), *dlen,fp);

return(E_SUCC);
}