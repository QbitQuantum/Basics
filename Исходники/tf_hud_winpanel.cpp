//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CTFWinPanel::CTFWinPanel( const char *pElementName ) : EditablePanel( NULL, "WinPanel" ), CHudElement( pElementName )
{
	vgui::Panel *pParent = g_pClientMode->GetViewport();
	SetParent( pParent );
	m_bShouldBeVisible = false;
	SetAlpha( 0 );
	SetScheme( "ClientScheme" );

	m_pTeamScorePanel = new EditablePanel( this, "TeamScoresPanel" );
	m_flTimeUpdateTeamScore = 0;
	m_iBlueTeamScore = 0;
	m_iRedTeamScore = 0;

	RegisterForRenderGroup( "mid" );
}