//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *parent - 
//-----------------------------------------------------------------------------
CDownloadSliderPanel::CDownloadSliderPanel( vgui::VPANEL parent ) :
	BaseClass( NULL , "CDownloadSliderPanel" )
{
	SetParent( parent );
	SetSize( ScreenWidth(), ScreenHeight() );
	SetPos( 0, 0 );
	SetVisible( false );
	SetCursor( null );

	SetFgColor( Color( 0, 0, 0, 255 ) );
	SetPaintBackgroundEnabled( false );

	scr_downloading = (ConVar *)cvar->FindVar( "scr_downloading" );
	assert( scr_downloading );

	vgui::ivgui()->AddTickSignal( GetVPanel(), 250 );
}