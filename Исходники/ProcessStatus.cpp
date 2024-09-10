void CProcessStatus::startingProcessor(CProcess * pProc)
{
	m_iProcNumber++;
	ASSERTX(m_iTotalProcessCount);
	int iPercentage = (int) (100.0* (float(m_iProcNumber-1) / float(m_iTotalProcessCount)));
	USES_CONVERSION;
	progress(A2CT(pProc->getDisplayName()), iPercentage);
}