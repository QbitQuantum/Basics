void CSiegeLogCommand::Initialize( CListCtrl& listCtrl ) const
{
	CRect	rect;
	int		step = -1;

	listCtrl.GetClientRect( rect );

	listCtrl.InsertColumn( ++step,  _T( "log index" ), LVCFMT_LEFT, 0 );

	CString textDate;
	textDate.LoadString( IDS_STRING3 );
	listCtrl.InsertColumn( ++step, textDate, LVCFMT_LEFT, int( rect.Width() * 0.25f ) );

	CString textType;
	textType.LoadString( IDS_STRING4 );
	listCtrl.InsertColumn( ++step, textType, LVCFMT_LEFT, int( rect.Width() * 0.25f ) );

	CString textGuild;
	textGuild.LoadString( IDS_STRING164 );
	listCtrl.InsertColumn( ++step, textGuild, LVCFMT_LEFT, int( rect.Width() * 0.25f ) );

	CString textPlayer;
	textPlayer.LoadString( IDS_STRING54 );
	listCtrl.InsertColumn( ++step, textPlayer, LVCFMT_LEFT, int( rect.Width() * 0.25f ) );

	CString textMemo;
	textMemo.LoadString( IDS_STRING17 );
	listCtrl.InsertColumn( ++step, textMemo, LVCFMT_LEFT, int( rect.Width() * 0.25f ) );
}