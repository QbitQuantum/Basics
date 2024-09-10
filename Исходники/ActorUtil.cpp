// NOTE: This function can return NULL if the actor should not be displayed.
// Callers should be aware of this and handle it appropriately.
Actor* ActorUtil::MakeActor( const RString &sPath_, Actor *pParentActor )
{
	RString sPath( sPath_ );

	FileType ft = GetFileType( sPath );
	switch( ft )
	{
	case FT_Lua:
		{
			auto_ptr<XNode> pNode( LoadXNodeFromLuaShowErrors(sPath) );
			if( pNode.get() == NULL )
			{
				// XNode will warn about the error
				return new Actor;
			}

			Actor *pRet = ActorUtil::LoadFromNode( pNode.get(), pParentActor );
			return pRet;
		}
	case FT_Xml:
		{
			// Legacy actors; only supported in quirks mode
			if ( !PREFSMAN->m_bQuirksMode )
				return new Actor;

			XNode xml;
			if ( !XmlFileUtil::LoadFromFileShowErrors(xml, sPath) )
				return new Actor;
			XmlFileUtil::CompileXNodeTree( &xml, sPath );
			XmlFileUtil::AnnotateXNodeTree( &xml, sPath );
			return LoadFromNode( &xml, pParentActor );
		}
	case FT_Directory:
		{
			if( sPath.Right(1) != "/" )
				sPath += '/';

			RString sXml = sPath + "default.xml";
			if (DoesFileExist(sXml))
				return MakeActor(sXml, pParentActor);

			XNode xml;
			xml.AppendAttr( "Class", "BGAnimation" );
			xml.AppendAttr( "AniDir", sPath );

			return ActorUtil::LoadFromNode( &xml, pParentActor );
		}
	case FT_Bitmap:
	case FT_Movie:
		{
			XNode xml;
			xml.AppendAttr( "Class", "Sprite" );
			xml.AppendAttr( "Texture", sPath );

			return ActorUtil::LoadFromNode( &xml, pParentActor );
		}
	case FT_Sprite:
		{
			// Legacy actor; only supported in quirks mode
			if( !PREFSMAN->m_bQuirksMode )
				return new Actor;

			IniFile ini;
			ini.ReadFile( sPath );
			XmlFileUtil::AnnotateXNodeTree( &ini, sPath );

			return ActorUtil::LoadFromNode( ini.GetChild("Sprite"), pParentActor );
		}
	case FT_Model:
		{
			XNode xml;
			xml.AppendAttr( "Class", "Model" );
			xml.AppendAttr( "Meshes", sPath );
			xml.AppendAttr( "Materials", sPath );
			xml.AppendAttr( "Bones", sPath );

			return ActorUtil::LoadFromNode( &xml, pParentActor );
		}
	default:
		{
			LOG->Warn( "File \"%s\" has unknown type, \"%s\".", sPath.c_str(), FileTypeToString(ft).c_str() );

			XNode xml;
			xml.AppendAttr( "Class", "Actor" );
			return ActorUtil::LoadFromNode( &xml, pParentActor );
		}
	}
}