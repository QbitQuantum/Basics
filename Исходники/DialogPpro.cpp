BOOL CDlgPpro::DestroyWindow() 
{
	KillTimer(STATE_TIMER);
	KillTimer(AUTOSEAT_TIMER);
	return CDialog::DestroyWindow();
}