void CItemShopLogCommand::Initialize( CListCtrl& listCtrl ) const
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

    CString textUser;
    textUser.LoadString( IDS_STRING301 );
    CString textIndex;
    textIndex.LoadString( IDS_STRING22 );
    // 080403 LUJ, 사용자 인덱스 표시
    listCtrl.InsertColumn( ++step, textUser + _T( " " ) + textIndex, LVCFMT_RIGHT, 0 );
    // 080403 LUJ, 사용자 아이디 표시
    listCtrl.InsertColumn( ++step, textUser, LVCFMT_LEFT, int( rect.Width() * 0.1f ) );

    CString textItem;
    textItem.LoadString( IDS_STRING189 );
    listCtrl.InsertColumn( ++step, textItem, LVCFMT_LEFT, int( rect.Width() * 0.25f ) );

    CString textDbIndex;
    textDbIndex.LoadString( IDS_STRING13 );
    listCtrl.InsertColumn( ++step, textItem + _T( " " ) + textDbIndex, LVCFMT_RIGHT, int( rect.Width() * 0.2f ) );

    CString textQuantity;
    textQuantity.LoadString( IDS_STRING42 );
    listCtrl.InsertColumn( ++step, textQuantity, LVCFMT_RIGHT, int( rect.Width() * 0.1f ) );
}