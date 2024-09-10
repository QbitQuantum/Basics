void COptionsAbout::OnDestroy() 
{
	CDialog::OnDestroy();

	timeKillEvent( mmTimer );
	//KillTimer( TIMER_ABOUT );
}