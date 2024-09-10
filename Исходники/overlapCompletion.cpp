void CALLBACK WorkerRoutine(DWORD error, DWORD bytesTrans, LPWSAOVERLAPPED overlap, DWORD flags){
	DWORD sendBytes,recvBytes;
	if(error != 0 || bytesTrans == 0){
		//发生错误 关闭套接字
		closesocket(sNew);
		return;
	}
	//此时 一个重叠的wsarecv成功完成
	//现在可以接收数据
	memcpy(buff,buff + 1,bytesTrans - 1);  //收到的第一位为数据的编码标识 在此去除
	buff[bytesTrans - 1] = '\0';
	printf("recv data: %s \n", dataBuff.buf);
	//处理完成后 需要投递另外一个重叠的WSARecv 或 WSASend
	flags = 0;
	ZeroMemory(overlap,sizeof(WSAOVERLAPPED));
	dataBuff.len = BUFF_SIZE;
	dataBuff.buf = buff;
	if(WSARecv(sNew,&dataBuff,1,&recvBytes,&flags,overlap,WorkerRoutine) == SOCKET_ERROR){
		if(WSAGetLastError() != WSA_IO_PENDING){
			printf("WSARecv() failed with error %d \n", WSAGetLastError());
			return;
		}
	}
}