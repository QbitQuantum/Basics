void Helium::RotateComponentDefinition::PopulateMetaType( Reflect::MetaStruct& comp )
{
	comp.AddField(&RotateComponentDefinition::m_Roll, "m_Roll");
	comp.AddField(&RotateComponentDefinition::m_Pitch, "m_Pitch");
	comp.AddField(&RotateComponentDefinition::m_Yaw, "m_Yaw");
}