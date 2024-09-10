void PlayerManagerComponentDefinition::PopulateMetaType( Reflect::MetaStruct& comp )
{
	comp.AddField( &PlayerManagerComponentDefinition::m_PlayerEntity, "m_PlayerEntity" );
}