extern	Bool
RequestExportBLOB(
	NETFILE	*fp,
	MonObjectType	obj,
	char			*fname)
{
	Bool	rc;
	char	buff[SIZE_BUFF];
	FILE	*fpf;
	size_t	size
		,	left;

ENTER_FUNC;
	rc = FALSE;
	RequestBLOB(fp,BLOB_EXPORT);		ON_IO_ERROR(fp,badio);
	SendObject(fp,obj);					ON_IO_ERROR(fp,badio);
	if		(  RecvPacketClass(fp)  ==  BLOB_OK  ) {
		if		(  ( fpf = Fopen(fname,"w") )  !=  NULL  ) {
			fchmod(fileno(fpf),0600);
			left = RecvLength(fp);
			while	(  left  >  0  ) {
				size = (  left  >  SIZE_BUFF  ) ? SIZE_BUFF : left;
				Recv(fp,buff,size);			ON_IO_ERROR(fp,badio);
				fwrite(buff,size,1,fpf);
				left -= size;
			}
			fclose(fpf);
			rc = TRUE;
		} else {
			Warning("could not open for write: %s", fname);
		}
	}
  badio:
LEAVE_FUNC;
	return	(rc);
}