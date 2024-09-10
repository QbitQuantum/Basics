void Base::SourceAudioPreRead(std::size_t numFrames)
//--------------------------------------------------
{
	if(!InternalHasTimeInfo())
	{
		if(InternalHasGetStreamPosition())
		{
			SoundDevice::TimeInfo timeInfo;
			timeInfo.StreamFrames = InternalHasGetStreamPosition();
			timeInfo.SystemTimestamp = Clock().NowNanoseconds();
			timeInfo.Speed = 1.0;
			UpdateTimeInfo(timeInfo);
		} else
		{
			SoundDevice::TimeInfo timeInfo;
			{
				Util::lock_guard<Util::mutex> lock(m_StreamPositionMutex);
				timeInfo.StreamFrames = m_StreamPositionRenderFrames + numFrames;
			}
			timeInfo.SystemTimestamp = Clock().NowNanoseconds() + Util::Round<int64>(m_BufferAttributes.Latency * 1000000000.0);
			timeInfo.Speed = 1.0;
			UpdateTimeInfo(timeInfo);
		}
	}
}