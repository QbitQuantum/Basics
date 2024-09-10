void ExampleGame::SpriteComponentDefinition::PopulateMetaType( Helium::Reflect::MetaStruct& comp )
{
	comp.AddField( &SpriteComponentDefinition::m_Rotation, "m_Rotation" );
	comp.AddField( &SpriteComponentDefinition::m_Scale, "m_Scale" );
	comp.AddField( &SpriteComponentDefinition::m_Texture, "m_Texture" );
	comp.AddField( &SpriteComponentDefinition::m_TopLeftPixel, "m_TopLeftPixel" );
	comp.AddField( &SpriteComponentDefinition::m_FrameSize, "m_FrameSize" );
	comp.AddField( &SpriteComponentDefinition::m_FramesPerColumn, "m_FramesPerColumn" );
	comp.AddField( &SpriteComponentDefinition::m_FrameCount, "m_FrameCount" );
	comp.AddField( &SpriteComponentDefinition::m_Texture, "m_Texture" );
}