void CGame::SleepUntilInput( int time )
{
	MsgWaitForMultipleObjects(1, &m_hEvent, FALSE, time, QS_KEY );
}