void CUartChannel::SetupTimesout(void)
{
	COMMTIMEOUTS  CommTimeOuts ;

	if(this->IsOpened() == FALSE)
		return;
	if (!GetCommTimeouts(this->m_Hcomm,&CommTimeOuts))
		return;
	CommTimeOuts.ReadIntervalTimeout = 20;//MAXDWORD;//0xFFFFFFFF ;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 10;//MAXDWORD;//0 ;
	CommTimeOuts.ReadTotalTimeoutConstant = 100;//MAXDWORD-1;//1000 ;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 10;//2*CBR_9600/DBUG_BAUD ;
	CommTimeOuts.WriteTotalTimeoutConstant = 100 ;
	SetCommTimeouts(this->m_Hcomm, &CommTimeOuts);
}