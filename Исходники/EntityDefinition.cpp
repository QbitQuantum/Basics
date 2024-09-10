void Helium::EntityDefinition::PopulateMetaType( Reflect::MetaStruct& comp )
{
	comp.AddField( &EntityDefinition::m_ComponentSet, "m_ComponentSet" );
	comp.AddField( &EntityDefinition::m_Components, "m_Components" );
}