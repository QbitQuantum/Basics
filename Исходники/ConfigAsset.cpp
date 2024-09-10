void ConfigAsset::PopulateMetaType( Reflect::MetaStruct& comp )
{
	comp.AddField( &ConfigAsset::m_ConfigObject, "m_ConfigObject" );
}