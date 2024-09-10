//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CDoDHudPlayerStatusPanel::CDoDHudPlayerStatusPanel( const char *pElementName ) : CHudElement( pElementName ), BaseClass( NULL, "HudPlayerStatusPanel" )
{
    SetParent( g_pClientMode->GetViewport() );

    m_pMainBar = new CDoDCutEditablePanel( this, "PlayerStatusMainBackground" );
    m_pAlliesIcon = new ImagePanel( this, "PlayerStatusAlliesIcon" );
    m_pAxisIcon = new ImagePanel( this, "PlayerStatusAxisIcon" );
    m_pAmmoStatus = new CDoDHudAmmo( this, "PlayerStatusAmmo" );
    m_pCurrentWeapon = new CDoDHudCurrentWeapon( this, "PlayerStatusCurrentWeapon" );
    m_pHealthStatus = new CDoDHudHealth( this, "PlayerStatusHealth" );
    m_pStamina = new CDoDHudStamina( this, "PlayerStatusStamina" );
    m_pMGHeat = new CDoDHudMGHeat( this, "PlayerStatusMGHeat" );
    m_pFireSelect = new CDoDHudFireSelect( this, "PlayerStatusFireSelect" );
    m_pTNT = new CDoDHudTNT( this, "PlayerStatusTNT" );
}