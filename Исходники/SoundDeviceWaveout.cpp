void CWaveDevice::StopFromSoundThread()
//-------------------------------------
{
	MPT_TRACE();
	if(m_hWaveOut)
	{
		CheckResult(waveOutPause(m_hWaveOut));
		m_JustStarted = false;
		{
			MPT_LOCK_GUARD<mpt::mutex> guard(m_PositionWraparoundMutex);
			MemsetZero(m_PositionLast);
			m_PositionWrappedCount = 0;
		}
	}
}