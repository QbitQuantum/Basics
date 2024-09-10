/* asqlBlobMemPut()
 *
 *************************************************************************/
_declspec(dllexport) long asqlBlobMemPut(TS_CLIENT_CURSOR *tscc, \
					LPCSTR lpszUser, \
					LPCSTR lpszUserDir,\
					void *df, \
					long recNo, \
					LPSTR fieldName, \
					EXCHNG_BUF_INFO *exbuf )
{
    TS_COM_PROPS tscp;
    unsigned short iw;
    char           *sp;
    long           memSize;
    BOOL 	   pbIfEnd;

    memset(&tscp, 0, sizeof(TS_COM_PROPS));

    while( tscc != NULL ) {
	if( tscc->p == (void *)df )
	    goto  agdr_dfTrueR;
	tscc = tscc->pNext;
    }
	df = NULL;
agdr_dfTrueR:

    if( SrvReadExchngBufEx(exbuf, &sp, &memSize, &pbIfEnd) != 0 ) {
	tscp.lp = -5;
	SrvWriteExchngBuf(exbuf, &tscp, sizeof(TS_COM_PROPS));
	return  -5;
    }

    tscp.packetType = 'R';
    tscp.msgType = 'E';
    tscp.len = 0;

    if( df == NULL || recNo <= 0 ) {
	HANDLE hDataBuf;

	hDataBuf = LocalHandle(sp);
	LocalUnlock( hDataBuf );
	LocalFree( hDataBuf );

	tscp.lp = -1;
	SrvWriteExchngBuf(exbuf, &tscp, sizeof(TS_COM_PROPS));

	return  -1;
    }

    iw = GetFldid((dFILE *)df, fieldName);
    if( iw == 0xFFFF ) {
	HANDLE hDataBuf;

	hDataBuf = LocalHandle(sp);
	LocalUnlock( hDataBuf );
	LocalFree( hDataBuf );

	tscp.lp = -4;
	SrvWriteExchngBuf(exbuf, &tscp, sizeof(TS_COM_PROPS));
	return  -4;
    }

    //((dFILE *)df)->rec_p = recNo;
    dseek((dFILE *)df, recNo-1, dSEEK_SET);

    if( get1rec((dFILE *)df) == NULL ) {
	HANDLE hDataBuf;

	hDataBuf = LocalHandle(sp);
	LocalUnlock( hDataBuf );
	LocalFree( hDataBuf );

	tscp.lp = -4;
	SrvWriteExchngBuf(exbuf, &tscp, sizeof(TS_COM_PROPS));
	return  -4;
    }

    //2000.7.21
    /*
    if( memSize < 0 ) {
	
    } else {
	blobFromMem((dFILE *)df, iw, sp, memSize);
    }*/
  
    if( memSize >= 0 ) {
	blobFromMem((dFILE *)df, iw, sp, memSize);
    }


    { ///////////////////////
	HANDLE hDataBuf;

	hDataBuf = LocalHandle(sp);
	LocalUnlock( hDataBuf );
	LocalFree( hDataBuf );
    }

    tscp.msgType = 'D';
    tscp.lp = 0;
    SrvWriteExchngBuf(exbuf, &tscp, sizeof(TS_COM_PROPS));

    return  0;

} //end of asqlBlobMemPut()