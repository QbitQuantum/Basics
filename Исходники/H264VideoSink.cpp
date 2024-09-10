/**
Singleton constructor
*/
H264VideoSink::H264VideoSink(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId):
	MyVideoSink(env), m_fSubsession(subsession)
{
	TRACE_INFO("Video sink constructor");
	m_fStreamId = strDup(streamId);
	//m_bufferSize=253440;//2*DUMMY_SINK_RECEIVE_BUFFER_SIZE;
    //m_fPos = 0;
    uint8_t startCode[] = {0x00, 0x00,0x01};

	//m_buffer = new unsigned char[m_bufferSize];
	//m_frameQueue=new CMediaQueue(200);
	m_decoder=new CVideoDecoder("H264");
	AddData(startCode, sizeof(startCode));
	//InitializeCriticalSection(&m_criticalSection);
	//m_ready=1;
}