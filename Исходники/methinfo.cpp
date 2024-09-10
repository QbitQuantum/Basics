void CMethodInfo::GetParamString(TSTR& str)
{
	str = _T("");
	int numParams = GetNumParams();
	CParamInfo  *pParamInfo = 0;

	if (m_invkind == INVOKE_FUNC)
	{
		for( int iParam = 0; iParam < numParams; iParam++ )
		{
			pParamInfo = m_apParamInfo[iParam];
			str += ((pParamInfo->m_flags & PARAMFLAG_FOUT) ? TSTR(_T(" &")) : TSTR(_T(" "))) +  
						pParamInfo->GetName() + _T(":") + pParamInfo->m_strType;
		}
	}
	else
	{
		TSTR buf(_T(" "));
		if (numParams > ((m_invkind == INVOKE_PROPERTYGET) ? 0 : 1))
		{
			pParamInfo = m_apParamInfo[0];
			buf.printf(_T("[%s:%s] "), pParamInfo->GetName(), pParamInfo->m_strType);
		}		
		str.printf(_T("%s: %s"), buf, 
			m_strReturn.isNull() ? m_apParamInfo[0]->m_strType : m_strReturn);
		
		if (m_dispid == DISPID_VALUE)	str += _T(", default");
		if (m_isHidden)
			str += _T(", hidden");		
	}
}