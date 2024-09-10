void ResumeMovieView::CreateMenu( App * app, OvrVRMenuMgr & menuMgr, BitmapFont const & font )
{
	Menu = VRMenu::Create( "ResumeMoviePrompt" );

    Vector3f fwd( 0.0f, 0.0f, 1.0f );
	Vector3f up( 0.0f, 1.0f, 0.0f );
	Vector3f defaultScale( 1.0f );

    Array< VRMenuObjectParms const * > parms;

	VRMenuFontParms fontParms( true, true, false, false, false, 1.3f );

	Quatf orientation( Vector3f( 0.0f, 1.0f, 0.0f ), 0.0f );
	Vector3f centerPos( 0.0f, 0.0f, 0.0f );

	VRMenuObjectParms centerRootParms( VRMENU_CONTAINER, Array< VRMenuComponent* >(), VRMenuSurfaceParms(), "CenterRoot",
			Posef( orientation, centerPos ), Vector3f( 1.0f, 1.0f, 1.0f ), fontParms,
			ID_CENTER_ROOT, VRMenuObjectFlags_t(), VRMenuObjectInitFlags_t( VRMENUOBJECT_INIT_FORCE_POSITION ) );
    parms.PushBack( &centerRootParms );

	Menu->InitWithItems( menuMgr, font, 0.0f, VRMenuFlags_t(), parms );
    parms.Clear();

    // the centerroot item will get touch relative and touch absolute events and use them to rotate the centerRoot
    menuHandle_t centerRootHandle = Menu->HandleForId( menuMgr, ID_CENTER_ROOT );
    VRMenuObject * centerRoot = menuMgr.ToObject( centerRootHandle );
    OVR_ASSERT( centerRoot != NULL );

    // ==============================================================================
    //
    // title
    //
    {
        Posef panelPose( Quatf( up, 0.0f ), Vector3f( 0.0f, 2.2f, -3.0f ) );

		VRMenuObjectParms p( VRMENU_STATIC, Array< VRMenuComponent* >(),
				VRMenuSurfaceParms(), Strings::ResumeMenu_Title, panelPose, defaultScale, fontParms, VRMenuId_t( ID_TITLE.Get() ),
				VRMenuObjectFlags_t(), VRMenuObjectInitFlags_t( VRMENUOBJECT_INIT_FORCE_POSITION ) );

		parms.PushBack( &p );

		Menu->AddItems( menuMgr, font, parms, centerRootHandle, false );
		parms.Clear();
    }

    // ==============================================================================
    //
    // options
    //
    Array<const char *> options;
    options.PushBack( Strings::ResumeMenu_Resume );
    options.PushBack( Strings::ResumeMenu_Restart );

    Array<const char *> icons;
    icons.PushBack( "assets/resume.png" );
    icons.PushBack( "assets/restart.png" );

    Array<PanelPose> optionPositions;
    optionPositions.PushBack( PanelPose( Quatf( up, 0.0f / 180.0f * Mathf::Pi ), Vector3f( -0.5f, 1.7f, -3.0f ), Vector4f( 1.0f, 1.0f, 1.0f, 1.0f ) ) );
    optionPositions.PushBack( PanelPose( Quatf( up, 0.0f / 180.0f * Mathf::Pi ), Vector3f(  0.5f, 1.7f, -3.0f ), Vector4f( 1.0f, 1.0f, 1.0f, 1.0f ) ) );

    int borderWidth = 0, borderHeight = 0;
    GLuint borderTexture = LoadTextureFromApplicationPackage( "assets/resume_restart_border.png", TextureFlags_t( TEXTUREFLAG_NO_DEFAULT ), borderWidth, borderHeight );

	for ( int i = 0; i < optionPositions.GetSizeI(); ++i )
	{
		ResumeMovieComponent * resumeMovieComponent = new ResumeMovieComponent( this, i );
		Array< VRMenuComponent* > optionComps;
		optionComps.PushBack( resumeMovieComponent );

		VRMenuSurfaceParms panelSurfParms( "",
				borderTexture, borderWidth, borderHeight, SURFACE_TEXTURE_ADDITIVE,
				0, 0, 0, SURFACE_TEXTURE_MAX,
				0, 0, 0, SURFACE_TEXTURE_MAX );

		Posef panelPose( optionPositions[ i ].Orientation, optionPositions[ i ].Position );
		VRMenuObjectParms * p = new VRMenuObjectParms( VRMENU_BUTTON, optionComps,
				panelSurfParms, options[ i ], panelPose, defaultScale, fontParms, VRMenuId_t( ID_OPTIONS.Get() + i ),
				VRMenuObjectFlags_t(), VRMenuObjectInitFlags_t( VRMENUOBJECT_INIT_FORCE_POSITION ) );

		parms.PushBack( p );

		Menu->AddItems( menuMgr, font, parms, centerRootHandle, false );
		DeletePointerArray( parms );
		parms.Clear();

		// add icon
	    menuHandle_t optionHandle = centerRoot->ChildHandleForId( menuMgr, VRMenuId_t( ID_OPTIONS.Get() + i ) );
	    VRMenuObject * optionObject = menuMgr.ToObject( optionHandle );
	    OVR_ASSERT( optionObject != NULL );

	    int iconWidth = 0, iconHeight = 0;
	    GLuint iconTexture = LoadTextureFromApplicationPackage( icons[ i ], TextureFlags_t( TEXTUREFLAG_NO_DEFAULT ), iconWidth, iconHeight );

		VRMenuSurfaceParms iconSurfParms( "",
				iconTexture, iconWidth, iconHeight, SURFACE_TEXTURE_DIFFUSE,
				0, 0, 0, SURFACE_TEXTURE_MAX,
				0, 0, 0, SURFACE_TEXTURE_MAX );


		Bounds3f textBounds = optionObject->GetTextLocalBounds( font );
		optionObject->SetTextLocalPosition( Vector3f( iconWidth * VRMenuObject::DEFAULT_TEXEL_SCALE * 0.5f, 0.0f, 0.0f ) );

		Posef iconPose( optionPositions[ i ].Orientation, optionPositions[ i ].Position + Vector3f( textBounds.GetMins().x, 0.0f, 0.01f ) );
		p = new VRMenuObjectParms( VRMENU_STATIC, Array< VRMenuComponent* >(),
				iconSurfParms, NULL, iconPose, defaultScale, fontParms, VRMenuId_t( ID_OPTION_ICONS.Get() + i ),
				VRMenuObjectFlags_t( VRMENUOBJECT_DONT_HIT_ALL ), VRMenuObjectInitFlags_t( VRMENUOBJECT_INIT_FORCE_POSITION ) );

		parms.PushBack( p );

		Menu->AddItems( menuMgr, font, parms, centerRootHandle, false );
	    DeletePointerArray( parms );
	    parms.Clear();

	    menuHandle_t iconHandle = centerRoot->ChildHandleForId( menuMgr, VRMenuId_t( ID_OPTION_ICONS.Get() + i ) );
	    resumeMovieComponent->Icon = menuMgr.ToObject( iconHandle );
	}

    Cinema.app->GetGuiSys().AddMenu( Menu );
}