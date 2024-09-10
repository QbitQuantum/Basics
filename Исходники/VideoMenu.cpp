OvrVideoMenu::OvrVideoMenu( App * app, Oculus360Videos * videos, OvrVRMenuMgr & menuMgr, BitmapFont const & font,
	OvrMetaData & metaData, float fadeOutTime, float radius )
	: VRMenu( MENU_NAME )
	, AppPtr( app )
	, MenuMgr( menuMgr )
	, Font( font )
	, Videos( videos )
	, MetaData( metaData )
	, LoadingIconHandle( 0 )
	, AttributionHandle( 0 )
	, BrowserButtonHandle( 0 )
	, VideoControlButtonHandle( 0 )
	, Radius( radius )
	, ButtonCoolDown( 0.0f )
	, OpenTime( 0.0 )
{
	// Init with empty root
	Init( menuMgr, font, 0.0f, VRMenuFlags_t() );

	// Create Attribution info view
	Array< VRMenuObjectParms const * > parms;
	Array< VRMenuComponent* > comps;
	VRMenuId_t attributionPanelId( ID_CENTER_ROOT.Get() + 10 );

	comps.PushBack( new OvrVideoMenuRootComponent( *this ) );

	Quatf rot( DOWN, 0.0f );
	Vector3f dir( -FWD );
	Posef panelPose( rot, dir * Radius );
	Vector3f panelScale( 1.0f );

	const VRMenuFontParms fontParms( true, true, false, false, true, 0.525f, 0.45f, 1.0f );

	VRMenuObjectParms attrParms( VRMENU_STATIC, comps,
		VRMenuSurfaceParms(), "Attribution Panel", panelPose, panelScale, Posef(), Vector3f( 1.0f ), fontParms, attributionPanelId,
		VRMenuObjectFlags_t(), VRMenuObjectInitFlags_t( VRMENUOBJECT_INIT_FORCE_POSITION ) );

	parms.PushBack( &attrParms );

	AddItems( MenuMgr, Font, parms, GetRootHandle(), false );
	parms.Clear();
	comps.Clear();

	AttributionHandle = HandleForId( MenuMgr, attributionPanelId );
	VRMenuObject * attributionObject = MenuMgr.ToObject( AttributionHandle );
	OVR_ASSERT( attributionObject != NULL );

	//Browser button
	float const ICON_HEIGHT = 80.0f * VRMenuObject::DEFAULT_TEXEL_SCALE;
	Array< VRMenuSurfaceParms > surfParms;

	Posef browserButtonPose( Quatf(), UP * ICON_HEIGHT * 2.0f );

	comps.PushBack( new OvrDefaultComponent( Vector3f( 0.0f, 0.0f, 0.05f ), 1.05f, 0.25f, 0.0f, Vector4f( 1.0f ), Vector4f( 1.0f ) ) );
	comps.PushBack( new OvrButton_OnUp( this, ID_BROWSER_BUTTON ) );
	comps.PushBack( new OvrSurfaceToggleComponent( ) );
	surfParms.PushBack( VRMenuSurfaceParms( "browser",
		"assets/nav_home_off.png", SURFACE_TEXTURE_DIFFUSE,
		NULL, SURFACE_TEXTURE_MAX, NULL, SURFACE_TEXTURE_MAX ) );
	surfParms.PushBack( VRMenuSurfaceParms( "browser",
		"assets/nav_home_on.png", SURFACE_TEXTURE_DIFFUSE,
		NULL, SURFACE_TEXTURE_MAX, NULL, SURFACE_TEXTURE_MAX ) );
	VRMenuObjectParms browserButtonParms( VRMENU_BUTTON, comps, surfParms, "",
		browserButtonPose, Vector3f( 1.0f ), Posef(), Vector3f( 1.0f ), fontParms,
		ID_BROWSER_BUTTON, VRMenuObjectFlags_t( VRMENUOBJECT_DONT_HIT_TEXT ),
		VRMenuObjectInitFlags_t( VRMENUOBJECT_INIT_FORCE_POSITION ) );
	parms.PushBack( &browserButtonParms );

	AddItems( MenuMgr, Font, parms, AttributionHandle, false );
	parms.Clear();
	comps.Clear();
	surfParms.Clear();

	BrowserButtonHandle = attributionObject->ChildHandleForId( MenuMgr, ID_BROWSER_BUTTON );
	VRMenuObject * browserButtonObject = MenuMgr.ToObject( BrowserButtonHandle );
	OVR_ASSERT( browserButtonObject != NULL );
	OVR_UNUSED( browserButtonObject );

	//Video control button 
	Posef videoButtonPose( Quatf(), DOWN * ICON_HEIGHT * 2.0f );

	comps.PushBack( new OvrDefaultComponent( Vector3f( 0.0f, 0.0f, 0.05f ), 1.05f, 0.25f, 0.0f, Vector4f( 1.0f ), Vector4f( 1.0f ) ) );
	comps.PushBack( new OvrButton_OnUp( this, ID_VIDEO_BUTTON ) );
	comps.PushBack( new OvrSurfaceToggleComponent( ) );
	surfParms.PushBack( VRMenuSurfaceParms( "browser",
		"assets/nav_restart_off.png", SURFACE_TEXTURE_DIFFUSE,
		NULL, SURFACE_TEXTURE_MAX, NULL, SURFACE_TEXTURE_MAX ) );
	surfParms.PushBack( VRMenuSurfaceParms( "browser",
		"assets/nav_restart_on.png", SURFACE_TEXTURE_DIFFUSE,
		NULL, SURFACE_TEXTURE_MAX, NULL, SURFACE_TEXTURE_MAX ) );
	VRMenuObjectParms controlButtonParms( VRMENU_BUTTON, comps, surfParms, "",
		videoButtonPose, Vector3f( 1.0f ), Posef(), Vector3f( 1.0f ), fontParms,
		ID_VIDEO_BUTTON, VRMenuObjectFlags_t( VRMENUOBJECT_DONT_HIT_TEXT ),
		VRMenuObjectInitFlags_t( VRMENUOBJECT_INIT_FORCE_POSITION ) );
	parms.PushBack( &controlButtonParms );

	AddItems( MenuMgr, Font, parms, AttributionHandle, false );
	parms.Clear();
	comps.Clear();

	VideoControlButtonHandle = attributionObject->ChildHandleForId( MenuMgr, ID_VIDEO_BUTTON );
	VRMenuObject * controlButtonObject = MenuMgr.ToObject( VideoControlButtonHandle );
	OVR_ASSERT( controlButtonObject != NULL );
	OVR_UNUSED( controlButtonObject );

}