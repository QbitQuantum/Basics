void CDestructable::HandleTrigger(HOBJECT hSender, HMESSAGEREAD hRead)
{
	CServerDE* pServerDE = BaseClass::GetServerDE();
	if (!pServerDE) return;

	HSTRING hMsg = pServerDE->ReadFromMessageHString(hRead);

	char* pMsg = pServerDE->GetStringData(hMsg);
	if (!pMsg || !pMsg[0]) return;

	if (_mbsicmp((const unsigned char*)pMsg, (const unsigned char*)TRIGGER_MSG_KILL) == 0)
	{
		DVector vTmp;
		VEC_INIT(vTmp);
		BaseClass *ffObj = pServerDE->HandleToObject(hSender);
		DamageObject(hSender, ffObj, m_hObject, 1, vTmp, vTmp, DAMAGE_TYPE_DEATH);
	}
	pServerDE->FreeString(hMsg);
}