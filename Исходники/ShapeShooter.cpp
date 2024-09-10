void ShapeShooterComponentDefinition::PopulateMetaType( Reflect::MetaStruct& comp )
{
	comp.AddField( &ShapeShooterComponentDefinition::m_StateMachine, "m_StateMachine" );
}