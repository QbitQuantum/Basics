bool RS485::send(frame &frm){
	DWORD dwBytesWrite=frm.getLength();
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	bWriteStat=WriteFile(hCom,frm.getFrame(),dwBytesWrite,& dwBytesWrite,NULL);
	if(!bWriteStat)
	{
		std::cout<<"写串口失败"<<std::endl;
		return false;
	}
	return true;
}