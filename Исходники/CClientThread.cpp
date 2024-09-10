void CClientThread::ReadFilePart(HANDLE hFile, const _i64 &offset,const bool &last)
{
	LPOVERLAPPED overlap=new OVERLAPPED;
	//memset(overlap, 0, sizeof(OVERLAPPED) );
	
	overlap->Offset=(DWORD)offset;
	overlap->OffsetHigh=(DWORD)(offset>>32);

	SLPData *ldata=new SLPData;
	ldata->buffer=bufmgr->getBuffer();

	if( ldata->buffer==NULL ) 
	{
		Log("Error: No Free Buffer", LL_DEBUG);
		Log("Info: Free Buffers="+nconvert(bufmgr->nfreeBufffer()), LL_DEBUG );
		return;
	}

	ldata->t_send=&t_send;
	ldata->t_unsend=&t_unsend;
	ldata->last=last;
	ldata->filepart=currfilepart;
	ldata->sendfilepart=&sendfilepart;
	overlap->hEvent=ldata;

	BOOL b=ReadFileEx(hFile, ldata->buffer, READSIZE, overlap, FileIOCompletionRoutine);

	++currfilepart;

	if( /*GetLastError() != ERROR_SUCCESS ||*/ b==false)
	{
		Log("Error: Can't start reading from File", LL_DEBUG);
		return;
	}
}