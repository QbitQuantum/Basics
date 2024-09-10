CDiscArena_RoundStart::CDiscArena_RoundStart( void ) : CDiscArenaPanel( ARENAWINDOW_X, ARENAWINDOW_Y, ARENAWINDOW_SIZE_X, ARENAWINDOW_SIZE_Y )
{
	m_pRound = new Label( "Round 1", 0, ROUND_Y, getWide(), YRES(32) );
	m_pRound->setParent( this );
	m_pRound->setBgColor( 0, 0, 0, 128 );
	m_pRound->setFgColor( 255,255,255, 0 );
	m_pRound->setContentAlignment( vgui::Label::a_center );

	m_pTeamOne = new Label( "Team One", 0, TEAMONE_Y, getWide(), YRES(32) );
	m_pTeamOne->setParent( this );
	m_pTeamOne->setBgColor( 128, 0, 0, 128 );
	m_pTeamOne->setFgColor( 255,255,255, 0 );
	m_pTeamOne->setContentAlignment( vgui::Label::a_center );

	// Trim the trailing \n from the VS string
	char sz[32];
	strcpy( sz, CHudTextMessage::BufferedLocaliseTextString( "#Versus" ) );
	sz[ strlen(sz) - 1 ] = '\0';
	Label *pLabel = new Label( sz, 0, VERSUS_Y, getWide(), YRES(32) );
	pLabel->setParent( this );
	pLabel->setBgColor( 0, 0, 0, 255 );
	pLabel->setFgColor( 255,255,255, 0 );
	pLabel->setContentAlignment( vgui::Label::a_center );

	m_pTeamTwo = new Label( "Team Two", 0, TEAMTWO_Y, getWide(), YRES(32) );
	m_pTeamTwo->setParent( this );
	m_pTeamTwo->setBgColor( 0, 0, 128, 128 );
	m_pTeamTwo->setFgColor( 255,255,255, 0 );
	m_pTeamTwo->setContentAlignment( vgui::Label::a_center );

	setVisible(false);
}