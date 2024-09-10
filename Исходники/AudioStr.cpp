// Destructor
void Timer::destructor(void)
{
	if (m_nIDTimer) {
		timeKillEvent (m_nIDTimer);
		m_nIDTimer = NULL;
	}
}