//---------------------------------------------------------------------
// OpenEventLog/CloseEventLogを対にするクラス
//---------------------------------------------------------------------
//---------------------------------------------------------------------
// イベントログを開く
//---------------------------------------------------------------------
BOOL kjm::eventlog::OpenEventLog( LPCTSTR lpUNCServerName, LPCTSTR lpSourceName ) {

	// すでに開いているかもしれないので、閉じる
	CloseEventLog();

	m_unc_server_name = ( lpUNCServerName ) ? lpUNCServerName : "";
	m_source_name = ( lpSourceName ) ? lpSourceName : "";

	m_hEventLog = ::OpenEventLog( lpUNCServerName, lpSourceName );
	return ( m_hEventLog ) ? TRUE : FALSE;
}