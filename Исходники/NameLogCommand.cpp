void CNameLogCommand::Initialize( CListCtrl& listCtrl ) const
{
    CRect	rect;
    int		step = -1;

    listCtrl.GetClientRect( rect );

    CString textDate;
    textDate.LoadString( IDS_STRING3 );
    listCtrl.InsertColumn( ++step, textDate, LVCFMT_LEFT, int( rect.Width() * 0.4f ) );
    CString textPlayer;
    textPlayer.LoadString( IDS_STRING54 );
    listCtrl.InsertColumn( ++step, textPlayer, LVCFMT_LEFT, int( rect.Width() * 0.2f ) );
    CString textName;
    textName.LoadString( IDS_STRING20 );
    listCtrl.InsertColumn( ++step, textName, LVCFMT_LEFT, int( rect.Width() * 0.6f ) );
}