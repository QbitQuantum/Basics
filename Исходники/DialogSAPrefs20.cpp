// CDlgSAPrefs20 message handlers
BOOL CDlgSAPrefs20::OnInitDialog()
{	
	CheckDlgButton(IDC_DEBUG_AUTOCONNECTOR , prefs.debug_autoconnector() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_AUTOPLAYER, prefs.debug_autoplayer() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_HEARTBEAT, prefs.debug_heartbeat() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_PRWIN, prefs.debug_prwin() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_ICM, prefs.debug_icm() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_OCCLUSSION, prefs.debug_occlusionchecker() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_POKERTRACKER, prefs.debug_pokertracker() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_REBUY, prefs.debug_rebuy() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_REPLAYFRAMES, prefs.debug_replayframes() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_SCRAPER, prefs.debug_scraper() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_SESSIONCOUNTER, prefs.debug_sessioncounter() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_STABLEFRAMESCOUNTER, prefs.debug_stableframescounter() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_SYMBOLENGINE, prefs.debug_symbolengine() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_BLINDLOCKING, prefs.debug_blindlocking() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_MEMORY_SYMBOLS, prefs.debug_memorysymbols() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_TABLEMAP_LOADER, prefs.debug_tablemap_loader() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_FILESYSTEM_MONITOR, prefs.debug_filesystem_monitor() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_TABLE_POSITIONER, prefs.debug_table_positioner() ? MF_CHECKED : MF_UNCHECKED);
	CheckDlgButton(IDC_DEBUG_ALLTHEREST, prefs.debug_alltherest() ? MF_CHECKED : MF_UNCHECKED);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}