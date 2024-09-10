void CStatLogCommand::Initialize( CListCtrl& listCtrl ) const
{
	CRect	rect;
	int		step = -1;

	listCtrl.GetClientRect( rect );

	listCtrl.InsertColumn( ++step,  _T( "log index" ), LVCFMT_LEFT, 0 );

	CString textDate;
	textDate.LoadString( IDS_STRING3 );
	listCtrl.InsertColumn( ++step, textDate, LVCFMT_LEFT, int( rect.Width() * 0.15f ) );

	CString textLevel;
	textLevel.LoadString( IDS_STRING5 );
	listCtrl.InsertColumn( ++step, textLevel, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );

	CString textStrength;
	textStrength.LoadString( IDS_STRING70 );
	listCtrl.InsertColumn( ++step, textStrength, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );

	CString textDexterity;
	textDexterity.LoadString( IDS_STRING71 );
	listCtrl.InsertColumn( ++step, textDexterity, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );

	CString textVitality;
	textVitality.LoadString( IDS_STRING72 );
	listCtrl.InsertColumn( ++step, textVitality, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );

	CString textIntelligence;
	textIntelligence.LoadString( IDS_STRING73 );
	listCtrl.InsertColumn( ++step, textIntelligence, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );

	CString textWisdom;
	textWisdom.LoadString( IDS_STRING74 );
	listCtrl.InsertColumn( ++step, textWisdom, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );

	CString textExperience;
	textExperience.LoadString( IDS_STRING9 );
	listCtrl.InsertColumn( ++step, textExperience, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
}