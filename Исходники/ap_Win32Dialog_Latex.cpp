void AP_Win32Dialog_Latex::event_Close(void)
{
	m_answer = AP_Dialog_Latex::a_CANCEL;
	modeless_cleanup();
	destroyWindow();
}