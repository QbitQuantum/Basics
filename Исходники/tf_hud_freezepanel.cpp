//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CTFFreezePanel::CTFFreezePanel( const char *pElementName )
	: EditablePanel( NULL, "FreezePanel" ), CHudElement( pElementName )
{
	vgui::Panel *pParent = g_pClientMode->GetViewport();
	SetParent( pParent );
	SetVisible( false );
	SetScheme( "ClientScheme" );

	m_iKillerIndex = 0;
	m_iShowNemesisPanel = SHOW_NO_NEMESIS;
	m_iYBase = -1;
	m_flShowCalloutsAt = 0;

	m_iBasePanelOriginalX = -1;
	m_iBasePanelOriginalY = -1;
}