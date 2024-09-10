int ReadFromMailslot(HANDLE hmailslot, char *buffer, int *size)
{
	DWORD dwMessageSize, dwMessageNum, dwMessageReadSize;
	BOOL bRes;
	int i;
	bRes = GetMailslotInfo(hmailslot,NULL,&dwMessageSize,&dwMessageNum,(LPDWORD)NULL);
	if(bRes==FALSE || dwMessageSize==MAILSLOT_NO_MESSAGE)
		return FALSE;
	for(i=0;i<10;i++){
		bRes = ReadFile(hMailslot,buffer,dwMessageSize,&dwMessageReadSize,(LPOVERLAPPED)NULL);
#ifdef W32GUI_DEBUG
PrintfDebugWnd("[%s]\n",buffer);
#endif
		if(bRes==TRUE){
			break;
		}
		Sleep(300);
	}
	if(bRes==TRUE){
		*size = (int)dwMessageSize;
		return TRUE;
	} else
		return FALSE;
}