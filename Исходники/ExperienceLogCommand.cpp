void CExperienceLogCommand::Initialize( CListCtrl& listCtrl ) const
{
	CRect	rect;
	int		step = -1;

	listCtrl.GetWindowRect( rect );

	listCtrl.InsertColumn( ++step,  _T( "log index" ), LVCFMT_LEFT, 0 );

	CString textDate;
	textDate.LoadString( IDS_STRING3 );
	listCtrl.InsertColumn( ++step, textDate, LVCFMT_LEFT, int( rect.Width() * 0.29f ) );

	CString textCategory;
	textCategory.LoadString( IDS_STRING4 );
	listCtrl.InsertColumn( ++step, textCategory, LVCFMT_LEFT, int( rect.Width() * 0.1f ) );

	CString textLevel;
	textLevel.LoadString( IDS_STRING5 );			
	listCtrl.InsertColumn( ++step, textLevel, LVCFMT_RIGHT, int( rect.Width() * 0.1f ) );

	CString textVariety;
	textVariety.LoadString( IDS_STRING6 );
	listCtrl.InsertColumn( ++step, textVariety, LVCFMT_LEFT, int( rect.Width() * 0.1f ) );

	CString textKillerType;
	textKillerType.LoadString( IDS_STRING7 );
	// 080716 LUJ, 킬러 종류를 번호로 찍는 숨김 필드를 추가
	listCtrl.InsertColumn( ++step, _T( "Killer kind" ), LVCFMT_LEFT, 0 );
	listCtrl.InsertColumn( ++step, textKillerType, LVCFMT_LEFT, int( rect.Width() * 0.25f ) );

	CString textKillerIndex;
	textKillerIndex.LoadString( IDS_STRING8 );
	listCtrl.InsertColumn( ++step, textKillerIndex, LVCFMT_RIGHT, int( rect.Width() * 0.25f ) );

	CString textExperience;
	textExperience.LoadString( IDS_STRING9 );
	listCtrl.InsertColumn( ++step, textExperience, LVCFMT_RIGHT, int( rect.Width() * 0.2f ) );

	// 080716 LUJ, 보호 회수 표시하기 위해 필드 추가
	CString textMemo;
	textExperience.LoadString( IDS_STRING17 );
	listCtrl.InsertColumn( ++step, textExperience, LVCFMT_LEFT, int( rect.Width() * 0.3f ) );
}