void CUser::ExchangeReq(char *pBuf)
{
	int index = 0, destid = -1, send_index = 0, type = 0;
	CUser* pUser = NULL;
	char buff[256];

	if (isDead())
	{
		TRACE("### ExchangeProcess Fail : name=%s(%d), m_bResHpType=%d, hp=%d, x=%d, z=%d ###\n", m_pUserData->m_id, m_Sid, m_bResHpType, m_pUserData->m_sHp, (int)m_pUserData->m_curx, (int)m_pUserData->m_curz);
		goto fail_return;
	}
	else if (isTrading())
	{
		ExchangeCancel();
		return;
	}

	destid = GetShort( pBuf, index );
	pUser = m_pMain->GetUserPtr(destid);
	if (pUser == NULL
		|| pUser->isTrading()
		|| pUser->getNation() != getNation())
		goto fail_return;

	m_sExchangeUser = destid;
	pUser->m_sExchangeUser = m_Sid;

	SetByte( buff, WIZ_EXCHANGE, send_index );
	SetByte( buff, EXCHANGE_REQ, send_index );
	SetShort( buff, m_Sid, send_index );
	pUser->Send( buff, send_index );
	
	return;

fail_return:
	SetByte( buff, WIZ_EXCHANGE, send_index );
	SetByte( buff, EXCHANGE_CANCEL, send_index );
	Send( buff, send_index );
}