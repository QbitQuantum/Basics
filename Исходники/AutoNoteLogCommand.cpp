void CAutoNoteLogCommand::Initialize( CListCtrl& listCtrl ) const
{
	CRect rect;
	int	step = -1;
	listCtrl.GetClientRect( rect );

	listCtrl.InsertColumn( ++step, L"log index", LVCFMT_LEFT, 0 );
	CString textDate;
	textDate.LoadString( IDS_STRING3 );
	listCtrl.InsertColumn( ++step, textDate, LVCFMT_LEFT, int( rect.Width() * 0.25f ) );
	CString textType;
	textType.LoadString( IDS_STRING4 );
	listCtrl.InsertColumn( ++step, textType, LVCFMT_LEFT, int( rect.Width() * 0.15f ) );
	CString textReportPlayer;
	textReportPlayer.LoadString( IDS_STRING441 );
	listCtrl.InsertColumn( ++step, textReportPlayer, LVCFMT_LEFT, int( rect.Width() * 0.2f ) );
	CString textReportPlayerIndex;
	textReportPlayerIndex.LoadString( IDS_STRING442 );
	listCtrl.InsertColumn( ++step, textReportPlayerIndex, LVCFMT_RIGHT, int( rect.Width() * 0.1f ) );
	CString textAutoPlayer;
	textAutoPlayer.LoadString( IDS_STRING443 );
	listCtrl.InsertColumn( ++step, textAutoPlayer, LVCFMT_LEFT, int( rect.Width() * 0.2f ) );
	CString textAutoPlayerIndex;
	textAutoPlayerIndex.LoadString( IDS_STRING444 );
	listCtrl.InsertColumn( ++step, textAutoPlayerIndex, LVCFMT_RIGHT, int( rect.Width() * 0.1f ) );
}