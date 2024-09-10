// ADC数据采集停止
//************************************
// Method:    OnADCSampleStop
// FullName:  CADCSet::OnADCSampleStop
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CADCSet::OnADCSampleStop(void)
{
	int iPos = 0;
	iPos = ADCSetFrameHead(BroadCastPort, SendSetCmd, ADSetReturnPort);

	OnStopSample(iPos);
	SendTo(m_ucFrameData, SndFrameSize, m_uiSendPort, IPBroadcastAddr);
 
	Sleep(ADCOperationSleepTime);
 
	OnStopSample(iPos);
	SendTo(m_ucFrameData, SndFrameSize, m_uiSendPort, IPBroadcastAddr);

	Sleep(ADCOperationSleepTime);

	OnStopSample(iPos);
	SendTo(m_ucFrameData, SndFrameSize, m_uiSendPort, IPBroadcastAddr);
}