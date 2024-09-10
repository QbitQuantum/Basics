BOOL CWin32Exception::ResetTranslator (void)
{
	if (m_fInstalled) {
	_se_translator_function pNextProc = m_pNextProc;

		m_pNextProc = NULL;

	_se_translator_function pPrevProc = _set_se_translator (m_pNextProc);

		TX_ASSERT(Translator == pPrevProc);
		m_fInstalled = false;
		return true;
	}

return false;
}