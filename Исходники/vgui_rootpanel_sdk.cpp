//-----------------------------------------------------------------------------
// C_SDKRootPanel implementation.
//-----------------------------------------------------------------------------
C_SDKRootPanel::C_SDKRootPanel( vgui::VPANEL parent )
	: BaseClass( NULL, "SDK Root Panel" )
{
	SetParent( parent );
	SetPaintEnabled( false );
	SetPaintBorderEnabled( false );
	SetPaintBackgroundEnabled( false );

	// This panel does post child painting
	SetPostChildPaintEnabled( true );

	// Make it screen sized
	SetBounds( 0, 0, ScreenWidth(), ScreenHeight() );

	// Ask for OnTick messages
	vgui::ivgui()->AddTickSignal( GetVPanel() );
}