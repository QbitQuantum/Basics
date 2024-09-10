void 
AP_UnixDialog_Goto::runModeless (XAP_Frame * pFrame)
{
	UT_DEBUGMSG (("ROB: runModeless ()\n"));
	constuctWindow (pFrame);
	UT_ASSERT (m_wDialog);
	updateWindow ();
	abiSetupModelessDialog (GTK_DIALOG (m_wDialog), pFrame, this, GTK_RESPONSE_CLOSE);
	gtk_widget_show_all (m_wDialog);
	gtk_window_present (GTK_WINDOW (m_wDialog));
}