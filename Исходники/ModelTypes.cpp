void AnimatedTexture::Load( const CString &sTexOrIniPath )
{
	ASSERT( vFrames.empty() );	// don't load more than once

	m_bSphereMapped = sTexOrIniPath.Find("sphere") != -1;
	if( sTexOrIniPath.Find("add") != -1 )
		m_BlendMode = BLEND_ADD;
	else
		m_BlendMode = BLEND_NORMAL;

	if( GetExtension(sTexOrIniPath).CompareNoCase("ini")==0 )
	{
		IniFile ini;
		if( !ini.ReadFile( sTexOrIniPath ) )
			RageException::Throw( "Error reading %s: %s", sTexOrIniPath.c_str(), ini.GetError().c_str() );

		if( !ini.GetKey("AnimatedTexture") )
			RageException::Throw( "The animated texture file '%s' doesn't contain a section called 'AnimatedTexture'.", sTexOrIniPath.c_str() );
		
		ini.GetValue( "AnimatedTexture", "TexVelocityX", m_fTexVelocityX );
		ini.GetValue( "AnimatedTexture", "TexVelocityY", m_fTexVelocityY );
		
		const CString sTexOrIniName = Dirname(sTexOrIniPath);
		RageTextureID ID;
		ID.bStretch = true;
		ID.bHotPinkColorKey = true;
		ID.bMipMaps = true;	// use mipmaps in Models
		for( int i=0; i<1000; i++ )
		{
			CString sFileName;
			float fDelay = 0;
			if( ini.GetValue( "AnimatedTexture", ssprintf("Frame%04d", i), sFileName ) &&
				ini.GetValue( "AnimatedTexture", ssprintf("Delay%04d", i), fDelay ) ) 
			{
				ID.filename = sTexOrIniName + sFileName;
				AnimatedTextureState state = { 
					TEXTUREMAN->LoadTexture( ID ),
					fDelay
				};
				vFrames.push_back( state );
			}
			else
				break;
		}
	}
	else
	{
		RageTextureID ID;
		ID.filename = sTexOrIniPath;
		ID.bHotPinkColorKey = true;
		ID.bStretch = true;
		ID.bMipMaps = true;	// use mipmaps in Models
		AnimatedTextureState state = { 
			TEXTUREMAN->LoadTexture( ID ),
			1
		};
		vFrames.push_back( state );
	}
}