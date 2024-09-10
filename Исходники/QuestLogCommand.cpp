void CQuestLogCommand::Initialize( CListCtrl& listCtrl ) const
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

    CString textQuest;
    textQuest.LoadString( IDS_STRING190 );

    CString textMain;
    textMain.LoadString( IDS_STRING191 );
    CString textIndex;
    textIndex.LoadString( IDS_STRING22 );
    listCtrl.InsertColumn( ++step, textQuest + _T( " " ) + textMain + _T( " " ) + textIndex, LVCFMT_RIGHT, int( rect.Width() * 0.25f ) );

    CString textSub;
    textSub.LoadString( IDS_STRING192 );
    listCtrl.InsertColumn( ++step, textQuest + _T( " " ) + textSub + _T( " " ) + textIndex, LVCFMT_LEFT, int( rect.Width() * 0.25f ) );

    CString textName;
    textName.LoadString( IDS_STRING20 );
    listCtrl.InsertColumn( ++step, textName, LVCFMT_LEFT, int( rect.Width() * 0.25f ) );

    CString textValue;
    textValue.LoadString( IDS_STRING152 );
    listCtrl.InsertColumn( ++step, textValue + _T( "1" ), LVCFMT_RIGHT, int( rect.Width() * 0.25f ) );
    listCtrl.InsertColumn( ++step, textValue + _T( "2" ), LVCFMT_RIGHT, int( rect.Width() * 0.25f ) );

    CString textMemo;
    textMemo.LoadString( IDS_STRING17 );
    listCtrl.InsertColumn( ++step, textMemo, LVCFMT_LEFT, int( rect.Width() * 0.25f ) );
}