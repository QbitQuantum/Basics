CString CDurationComboBox::DurationToString(double Duration)
{
	CString	s;
	if (Duration) {
		for (int iDenom = 0; iDenom < DENOMINATORS; iDenom++) {
			int denom = 1 << iDenom;
			for (int iUnit = 0; iUnit < UNITS; iUnit++) {
				double	divisor = m_Unit[iUnit] / denom;
				double	r = fabs(fmod(Duration, divisor));
//				printf("%g %g\n", divisor, r);
				if (r < m_Epsilon || fabs(r - divisor) < m_Epsilon) {
					int	numer = round(Duration / divisor);
					DWORD	dots = 0;
					if (SHOW_DOTS) {
						if (numer > 2 && IsPowerOfTwo(numer + 1)) {
							int	DotDenom = denom / ((numer + 1) / 2);
							if (DotDenom) {	// avoid divide by zero
								_BitScanReverse(&dots, denom / DotDenom);
								denom = DotDenom;
								numer = 1;
							}
						}
					}
					s.Format(_T("%d/%d"), numer, denom);
					if (iUnit)
						s.Insert(numer < 0, _T("T"));
					for (DWORD iDot = 0; iDot < dots; iDot++)
						s += '.';
					return(s);	// early out
				}
			}
		}
	}
	s.Format(_T("%g"), Duration);
	return(s);
}