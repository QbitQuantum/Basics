void CRealTimer::DoTimer()
{
	CBenchmark	bm;
	float	Error = 0;
	float	Period = 1.0f / m_Freq;
	int		PrevReset = 0;
	UINT	Clock = 0;
	HANDLE	ha[2] = {m_Event, m_Timer};
	while (m_State != DIE) {
		__int64	Due = round((Period - Error) * -1e7);	// relative UTC
		SetWaitableTimer(m_Timer, (LARGE_INTEGER *)&Due, 0, NULL, NULL, 0);
		WaitForMultipleObjects(m_State + 1, ha, FALSE, INFINITE);
		m_State = m_NewState;
		if (m_State == RUN) {
			m_Callback(m_Cookie);
			Clock++;
			Error = float(bm.Elapsed() - Clock * Period);
			if (m_Reset != PrevReset) {
				Period = 1.0f / m_Freq;
				PrevReset = m_Reset;
				Clock = 0;
				Error = 0;
				bm.Reset();
			}
		}
	}
}