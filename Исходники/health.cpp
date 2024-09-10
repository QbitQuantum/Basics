void HealthComponentDefinition::PopulateMetaType( Reflect::MetaStruct& comp )
{
	comp.AddField( &HealthComponentDefinition::m_InitialHealth, "m_InitialHealth" );
	comp.AddField( &HealthComponentDefinition::m_MaxHealth, "m_MaxHealth" );
}