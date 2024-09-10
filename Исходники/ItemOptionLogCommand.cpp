void CItemOptionLogCommand::Initialize( CListCtrl& listCtrl ) const
{
	CRect	rect;
	int		step = -1;

	listCtrl.GetClientRect( rect );

	listCtrl.InsertColumn( ++step,  _T( "log index" ), LVCFMT_LEFT, 0 );

	CString textDate;
	textDate.LoadString( IDS_STRING3 );
	listCtrl.InsertColumn( ++step, textDate, LVCFMT_LEFT, int( rect.Width() * 0.15f ) );

	CString textType;
	textType.LoadString( IDS_STRING4 );
	listCtrl.InsertColumn( ++step, textType, LVCFMT_LEFT, int( rect.Width() * 0.15f ) );

	CString textItemDbIndex;
	textItemDbIndex.LoadString( IDS_STRING13 );
	listCtrl.InsertColumn( ++step, textItemDbIndex, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );

	CString textStrength;
	textStrength.LoadString( IDS_STRING70 );

	CString textDexterity;
	textDexterity.LoadString( IDS_STRING71 );

	CString textVitality;
	textVitality.LoadString( IDS_STRING72 );

	CString textIntelligence;
	textIntelligence.LoadString( IDS_STRING73 );

	CString textWisdom;
	textWisdom.LoadString( IDS_STRING74 );

	CString textLife;
	textLife.LoadString( IDS_STRING75 );

	CString textMana;
	textMana.LoadString( IDS_STRING76 );

	CString textLifeRecovery;
	textLifeRecovery.LoadString( IDS_STRING77 );

	CString textManaRecovery;
	textManaRecovery.LoadString( IDS_STRING78 );

	CString textPhysicalAttack;
	textPhysicalAttack.LoadString( IDS_STRING79 );

	CString textPhysicalDefence;
	textPhysicalDefence.LoadString( IDS_STRING80 );

	CString textMagicalAttack;
	textMagicalAttack.LoadString( IDS_STRING81 );

	CString textMagicalDefence;
	textMagicalDefence.LoadString( IDS_STRING82 );

	CString textMoveSpeed;
	textMoveSpeed.LoadString( IDS_STRING83 );

	CString textEvade;
	textEvade.LoadString( IDS_STRING84 );

	CString textAccuracy;
	textAccuracy.LoadString( IDS_STRING85 );

	CString textCriticalDamage;
	textCriticalDamage.LoadString( IDS_STRING86 );

	CString textCriticalRate;
	textCriticalRate.LoadString( IDS_STRING87 );

	CString textReinforce;
	textReinforce.LoadString( IDS_STRING89 );

	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textStrength, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textDexterity, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textVitality, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textIntelligence, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textWisdom, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textLife, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textMana, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textLifeRecovery, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textManaRecovery, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textPhysicalAttack, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textPhysicalDefence, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textMagicalAttack, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textMagicalDefence, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textCriticalRate, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textCriticalDamage, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textMoveSpeed, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textEvade, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textReinforce + _T( ": " ) + textAccuracy, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );

	CString textMix;
	textMix.LoadString( IDS_STRING90 );

	listCtrl.InsertColumn( ++step, textMix + _T( ": " ) + textStrength, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textMix + _T( ": " ) + textIntelligence, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textMix + _T( ": " ) + textDexterity, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textMix + _T( ": " ) + textWisdom, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textMix + _T( ": " ) + textVitality, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );

	CString textEnchant;
	textEnchant.LoadString( IDS_STRING91 );

	CString textLevel;
	textLevel.LoadString( IDS_STRING5 );
	CString textIndex;
	textIndex.LoadString( IDS_STRING22 );

	listCtrl.InsertColumn( ++step, textEnchant + _T( ": " ) + textIndex, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );
	listCtrl.InsertColumn( ++step, textEnchant + _T( ": " ) + textLevel, LVCFMT_RIGHT, int( rect.Width() * 0.15f ) );

	CString textMemo;
	textMemo.LoadString( IDS_STRING17 );
	listCtrl.InsertColumn( ++step, textMemo, LVCFMT_LEFT, int( rect.Width() * 0.15f ) );
}