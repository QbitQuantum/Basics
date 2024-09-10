void CPrinterDC::Abort(void)
{
	ASSERT(m_hDC);

	AbortDoc(m_hDC);
}