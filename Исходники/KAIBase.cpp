void KAIBase::OnEscape(void)
{
	// 决定是否还要逃跑
	BOOL bRetCode = FALSE;

	KG_PROCESS_ERROR(g_pSO3World->m_nGameLoop < m_EscapeData.nEscapeFrame);

	Escape();
	return;
Exit0:
	// 不跑了，开打
	DoPursuit();
	return;
}