/**************************************************************************
* fn: 
* socket: 发送的socket
* fd: 录像文件的句柄
***************************************************************************/
int DcpStartRecDownload( int socket, int fd )
{
	int ret = -1;
	pthread_t threadId;
	REC_DOWNLOAD_T *pRecDownload = (REC_DOWNLOAD_T *)Malloc( sizeof(REC_DOWNLOAD_T) );

	if( NULL != pRecDownload )
    {
    	pRecDownload->socket     = socket;        
    	pRecDownload->fd         = fd;
    	Memset( &pRecDownload->sendPack.packHead, 0x00, 
            	sizeof(pRecDownload->sendPack.packHead) );
    	ret = ThreadCreate( &threadId, DcpRecDownloadThread, pRecDownload );
    }

	return ret;
}