HX_RESULT 
CWinRegKey::Flush()
{
    if(!m_bOpen)
    {
	return HXR_UNEXPECTED;
    }

    if
    (
	RegFlushKey(m_hkThis)
	==
	ERROR_SUCCESS
    )
    {
	return HXR_OK;
    }

    return HXR_FAIL;
}