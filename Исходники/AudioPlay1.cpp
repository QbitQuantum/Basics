bool __stdcall AudioStop1()
{	
	waveOutReset(m_hWaveOut1);//停止输出
	waveOutClose(m_hWaveOut1);//关闭设备
    return true;

}