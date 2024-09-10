WMSG_RESULT CUISpinControl::OnCharMessage( MSG* pMsg )
{
	extern UBYTE	_abKeysPressed[256];

	// If editbox is not focused
	if( !IsFocused() || m_InValidEditBox )
		return WMSG_FAIL;

	if(m_bOnlyInteger && (pMsg->wParam < 48 || pMsg->wParam > 57))
	{
		return WMSG_SUCCESS;
	}

	InsertChar(m_nCursorIndex, pMsg->wParam);

	if (_atoi64(GetString()) > m_llMax)
	{
		CTString strTmp;
		strTmp.PrintF("%I64d", m_llMax);

		SetString(strTmp.str_String);
	}

	return WMSG_SUCCESS;
}