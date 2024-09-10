//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CDODDeathStatsPanel::CDODDeathStatsPanel( const char *pElementName )
: EditablePanel( NULL, "DeathStats" ), CHudElement( pElementName )
{
	vgui::Panel *pParent = g_pClientMode->GetViewport();
	SetParent( pParent );
	SetVisible( false );
	SetAlpha( 0 );
	SetScheme( "ClientScheme" );

	m_pAttackerHistoryLabel = new vgui::Label( this, "AttackerDmgLabel", "..." );
	m_pSummaryLabel = new vgui::Label( this, "LifeSummaryLabel", "..." );

	memset( &m_DeathRecord, 0, sizeof(m_DeathRecord) );

	LoadControlSettings("Resource/UI/DeathStats.res");	
}