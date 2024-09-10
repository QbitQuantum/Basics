BOOL CAudioCtrl::SetPlayVolume(DWORD dwVolume)
{
    if (m_eStatus == ENUM_STATUS_PLAYING)
    {
        if(waveOutSetVolume( m_hPlay, dwVolume ) == MMSYSERR_NOERROR)
            return TRUE;
	}
    return FALSE;
}