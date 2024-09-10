//播放一块数据
BOOL CAudioPlay::Play(char *buf, UINT uSize)
{

    BOOL bRet=FALSE;
    char* p;
    LPWAVEHDR pwh=new WAVEHDR;
    if(!pwh)
        goto RET;
    p=new char[uSize];//重新分配一块内存(在播放结束后删除)
    if(!p)
        goto RET;
    CopyMemory(p,buf,uSize);
    ZeroMemory(pwh,sizeof(WAVEHDR));
    pwh->dwBufferLength=uSize;
    pwh->lpData=p;
    //
    m_mmr=waveOutPrepareHeader(m_hOut,pwh,sizeof(WAVEHDR));
    if(m_mmr)
        goto RET;
    m_mmr=waveOutWrite(m_hOut,pwh,sizeof(WAVEHDR));
    if(m_mmr)
        goto RET;
    bRet=TRUE;


RET:
    return bRet;
}