void CStringEx::PutDouble(double f, int len)
{
	switch	(_fpclass(f))
	{
		case _FPCLASS_SNAN:
		case _FPCLASS_QNAN:
			Format("%s", m_csNAN); // "NaN"
			return;
		case _FPCLASS_NINF:
			Format("%s", m_csNINF);// "-Inf"
			return;
		case _FPCLASS_PINF:
			Format("%s", m_csPINF);// "+Inf"
			return;
	}
	dtoan(GetBuffer(len),f,len);
	ReleaseBuffer(len);
	// have we exceeded our acuracy?
	int acc = 16;
	if(len< acc+1) return;
	Accuracy(acc);
}