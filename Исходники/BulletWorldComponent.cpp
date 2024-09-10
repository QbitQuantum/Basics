void Helium::BulletWorldComponentDefinition::PopulateMetaType( Reflect::MetaStruct& comp )
{
	comp.AddField(&BulletWorldComponentDefinition::m_WorldDefinition, "m_WorldDefinition");
}