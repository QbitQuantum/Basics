GKbool GKTextEncoding::Convert( GKbyte* target, GKint32& nTargetLen, const GKbyte* source, GKint32 nSourceLen )
{
	GKASSERT(target != NULL && source != NULL);
	UErrorCode ErrorCode = U_ZERO_ERROR;
	m_dstConverter = ucnv_open(m_dstCharset.Cstr(), &ErrorCode);
	if(U_FAILURE(ErrorCode)){
		GKFPRINTF(stdout, "%s\n",u_errorName(ErrorCode));
		ucnv_close(m_dstConverter); 
		return false;
	}
	m_srcConverter = ucnv_open(m_srcCharset.Cstr(), &ErrorCode);
	if(U_FAILURE(ErrorCode)){
		GKFPRINTF(stdout, "%s\n",u_errorName(ErrorCode));
		ucnv_close(m_srcConverter);
		return false;
	}
	
	ucnv_convert(m_dstCharset.Cstr(), m_srcCharset.Cstr(), (char*)target, nTargetLen, (char*)source, nSourceLen,&ErrorCode);
	if(U_FAILURE(ErrorCode)){
		GKFPRINTF(stdout, "%s\n",u_errorName(ErrorCode));
		ucnv_close(m_dstConverter);
		ucnv_close(m_srcConverter);

		return false;
	}
	ucnv_close(m_dstConverter);
	ucnv_close(m_srcConverter);

	return true;
}