void ShaderAsset::EnumerateClass( Reflect::Compositor<ShaderAsset>& comp )
{
    comp.GetComposite().m_UIName = TXT( "Shader" );
    comp.GetComposite().SetProperty( AssetProperties::FileFilter, "*.shader.*" );

    comp.AddField( &ShaderAsset::m_ColorMapPath, "m_ColorMapPath", Reflect::FieldFlags::FilePath );
    comp.AddField( &ShaderAsset::m_NormalMapPath, "m_NormalMapPath", Reflect::FieldFlags::FilePath );
    comp.AddField( &ShaderAsset::m_GPIMapPath, "m_GPIMapPath", Reflect::FieldFlags::FilePath );

    comp.AddField( &ShaderAsset::m_EnableColorMapTint, "m_EnableColorMapTint" );
    comp.AddField( &ShaderAsset::m_ColorMapTint, "m_ColorMapTint" );

    comp.AddField( &ShaderAsset::m_NormalMapScaling, "m_NormalMapScaling" );

    comp.AddField( &ShaderAsset::m_GlossMapEnabled, "m_GlossMapEnabled" );
    comp.AddField( &ShaderAsset::m_GlossMapScaling, "m_GlossMapScaling" );
    comp.AddField( &ShaderAsset::m_GlossMapTint, "m_GlossMapTint" );
    comp.AddField( &ShaderAsset::m_GlossMapDirtiness, "m_GlossMapDirtiness" );
    comp.AddField( &ShaderAsset::m_SpecularPower, "m_SpecularPower" );

    comp.AddField( &ShaderAsset::m_ParallaxMapEnabled, "m_ParallaxMapEnabled" );
    comp.AddField( &ShaderAsset::m_ParallaxMapScaling, "m_ParallaxMapScaling" );

    comp.AddField( &ShaderAsset::m_IncandescentMapEnabled, "m_IncandescentMapEnabled" );
    comp.AddField( &ShaderAsset::m_IncandescentMapScaling, "m_IncandescentMapScaling" );

    Reflect::Field* fieldDoubleSided = comp.AddField( &ShaderAsset::m_DoubleSided, "m_DoubleSided" );

    Reflect::EnumerationField* enumWrapModeU = comp.AddEnumerationField( &ShaderAsset::m_WrapModeU, "m_WrapModeU" );
    Reflect::EnumerationField* enumWrapModeV = comp.AddEnumerationField( &ShaderAsset::m_WrapModeV, "m_WrapModeV" );

    Reflect::EnumerationField* enumAlphaMode = comp.AddEnumerationField( &ShaderAsset::m_AlphaMode, "m_AlphaMode" );

    Reflect::EnumerationField* enumWetSurfaceMode = comp.AddEnumerationField( &ShaderAsset::m_WetSurfaceMode, "m_WetSurfaceMode" );
}