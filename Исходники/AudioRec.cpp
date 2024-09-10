//开始录音
BOOL CAudioRec::Start()
{
	BOOL bRet=FALSE;
	if(!m_hIn)
		goto RET;
	if(!AllocBuffer())
		goto RET;
	m_mmr=waveInStart(m_hIn);
	if(m_mmr)
		goto RET;	
	
	bRet=TRUE;
	
RET:

	return bRet;
}