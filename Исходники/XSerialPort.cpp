// 关闭串口
_XBool _XSerialPort::close()
{
	if(!m_bOpened || m_hIDComDev == NULL) return XTrue;
	if(m_overlappedRead.hEvent != NULL) CloseHandle(m_overlappedRead.hEvent);
	if(m_overlappedWrite.hEvent != NULL) CloseHandle(m_overlappedWrite.hEvent);
	if(m_mode == SP_MODE_AUTO) //自动模式的时候开启线程
	{
		m_threadState = STATE_SET_TO_END;
		SetCommMask(m_hIDComDev,0);
		while(1)
		{//等待线程结束
			if(m_threadState == STATE_END) break;
			Sleep(1);
		}
	}
	CloseHandle(m_hIDComDev);
	m_bOpened = XFalse;
	m_hIDComDev = NULL;

	return XTrue;
}