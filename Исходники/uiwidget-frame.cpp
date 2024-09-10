void UIWidgetFrame::InitializeFromDefinition( const SimpleString& DefinitionName )
{
	UIWidget::InitializeFromDefinition( DefinitionName );

	MAKEHASH( DefinitionName );
	MAKEHASH( m_Archetype );

	STATICHASH( DisplayWidth );
	const float DisplayWidth	= ConfigManager::GetFloat( sDisplayWidth );
	const float ParentWidth		= m_OriginParent ? m_OriginParent->GetWidth() : DisplayWidth;
	const float ParentX			= m_OriginParent ? Ceiling( m_OriginParent->GetX() ) : 0.0f;

	STATICHASH( DisplayHeight );
	const float DisplayHeight	= ConfigManager::GetFloat( sDisplayHeight );
	const float ParentHeight	= m_OriginParent ? m_OriginParent->GetHeight() : DisplayHeight;
	const float ParentY			= m_OriginParent ? Ceiling( m_OriginParent->GetY() ) : 0.0f;

	// "Screen" values are now relative to parent, which may or may not be screen dimensions.

	STATICHASH( PixelX );
	STATICHASH( ScreenX );
	float X = Pick(
		ConfigManager::GetArchetypeFloat( sPixelX, sm_Archetype, 0.0f, sDefinitionName ),
		ParentWidth * ConfigManager::GetArchetypeFloat( sScreenX, sm_Archetype, 0.0f, sDefinitionName ) );

	STATICHASH( PixelY );
	STATICHASH( ScreenY );
	float Y = Pick(
		ConfigManager::GetArchetypeFloat( sPixelY, sm_Archetype, 0.0f, sDefinitionName ),
		ParentHeight * ConfigManager::GetArchetypeFloat( sScreenY, sm_Archetype, 0.0f, sDefinitionName ) );
	
	STATICHASH( PixelWidth );
	STATICHASH( ScreenWidth );
	float Width = Pick(
		ConfigManager::GetArchetypeFloat( sPixelWidth, sm_Archetype, 0.0f, sDefinitionName ),
		ParentWidth * ConfigManager::GetArchetypeFloat( sScreenWidth, sm_Archetype, 0.0f, sDefinitionName ) );
	
	STATICHASH( PixelHeight );
	STATICHASH( ScreenHeight );
	float Height = Pick(
		ConfigManager::GetArchetypeFloat( sPixelHeight, sm_Archetype, 0.0f, sDefinitionName ),
		ParentHeight * ConfigManager::GetArchetypeFloat( sScreenHeight, sm_Archetype, 0.0f, sDefinitionName ) );

	STATICHASH( PixelBorder );
	m_Border = ConfigManager::GetArchetypeFloat( sPixelBorder, sm_Archetype, 0.0f, sDefinitionName );

	// Adjust for desired aspect ratio if one dimension is not given
	// (This is used to size images using ScreenWidth or ScreenHeight
	// properly regardless of screen aspect ratio.
	STATICHASH( AspectRatio );
	const float AspectRatio = ConfigManager::GetArchetypeFloat( sAspectRatio, sm_Archetype, 1.0f, sDefinitionName );
	if( Width == 0.0f )
	{
		Width = Height * AspectRatio;
	}
	else if( Height == 0.0f )
	{
		Height = Width / AspectRatio;
	}

	AdjustDimensionsToParent( X, Y, Width, Height, ParentX, ParentY, ParentWidth, ParentHeight );
	GetPositionFromOrigin( X, Y, Width, Height );

	ASSERT( Width > m_Border * 2.0f );
	ASSERT( Height > m_Border * 2.0f );

	STATICHASH( ClampToPixelGrid );
	if( ConfigManager::GetArchetypeBool( sClampToPixelGrid, sm_Archetype, true, sDefinitionName ) )
	{
		m_TopLeft.x = Round( m_TopLeft.x );
		m_TopLeft.y = Round( m_TopLeft.y );
	}

	// Offset to properly align on pixel grid.
	const float PixelGridOffset = GetPixelGridOffset();
	m_TopLeft.x -= PixelGridOffset;
	m_TopLeft.y -= PixelGridOffset;

	STATICHASH( Image );
	const char* const Filename = ConfigManager::GetArchetypeString( sImage, sm_Archetype, DEFAULT_TEXTURE, sDefinitionName );
	m_Texture = m_UIManager->GetRenderer()->GetTextureManager()->GetTexture( Filename, TextureManager::ETL_Permanent );

	m_Dimensions = Vector2( Width, Height );

	STATICHASH( MaterialOverride );
	const SimpleString DefaultMaterial( "Material_HUD" );
	m_Material = ConfigManager::GetArchetypeString( sMaterialOverride, sm_Archetype, DefaultMaterial.CStr(), sDefinitionName );

	UpdateRender();
}