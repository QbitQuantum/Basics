//
//	Name: CGUICommunity
//	Author: Hekar Khani
//	Description: Community portal to news, etc
//	Notes: 
//
CGUICommunity::CGUICommunity( vgui::VPANEL parent ) :
	BaseClass( NULL, "GUICommunity" )
{	
	SetParent( parent );
	vgui::HScheme scheme = vgui::scheme()->LoadSchemeFromFile( "resource/sourcescheme.res", "sourcescheme" );
	SetScheme( scheme );
	LoadControlSettings( "resource/ui/Community.res" );

	SetVisible( false );
	SetTitle( "#lf_community_title", true );
	SetSizeable( false );

	SetMaximizeButtonVisible( false );
	SetMinimizeButtonVisible( false );
}