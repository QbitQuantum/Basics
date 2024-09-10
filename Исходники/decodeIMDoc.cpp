CDecodeIMDoc::CDecodeIMDoc()
{
	// TODO: add one-time construction code here
	m_sTempFileName = _tempnam("c:\\","IDec");
	m_bHasDecodeContent = false;
	m_sLastMessage = "";
}