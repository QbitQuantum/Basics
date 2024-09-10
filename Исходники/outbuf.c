BOOL FWriteOutbuf(char *name, char *ext, OUTBUF *outbuf)
{
	FILE *f;
    U32 len = GET_BUF_OFFSET((U32)outbuf->buffer,(U32)outbuf->ptr);
    if(len) {
		sprintf(szTemp,"%s\\%05d.%s",name,scriptNumber,ext);
    	if((f = OpenFile(DIR_GAME,szTemp,"wb"))==NULL) {
    	 	fatal(FTL_SAVINGRESOURCE,szTemp);
    	}
    	FWrite(outbuf->buffer,len,f);
    	CloseFile(f);
    }
    return TRUE;
}