ERTFToken RTFdatafield::Read (RTFParser& p)
{
	ERTFToken tok;
	
	for(;;)
	{
		tok = p.GetToken(true);
		switch(tok)
		{
			case rtfec_OK:
				return rtfec_OK;

			default:						
				m_RTFdatafield += tok;		
				break;
		}
	}
	THROW_FATAL_RTF_READERROR(false, _T("Reading RTFdatafield"));
}