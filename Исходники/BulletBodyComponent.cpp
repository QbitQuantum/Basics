void BulletBodyComponentDefinition::PopulateMetaType( Reflect::MetaStruct& comp )
{
	comp.AddField(&BulletBodyComponentDefinition::m_BodyDefinition, "m_BodyDefinition");
	comp.AddField(&BulletBodyComponentDefinition::m_InitialVelocity, "m_InitialVelocity");
	comp.AddField(&BulletBodyComponentDefinition::m_AssignedGroupFlags, "m_AssignedGroupFlags");
	comp.AddField(&BulletBodyComponentDefinition::m_TrackPhysicalContactGroupFlags, "m_TrackPhysicalContactGroupFlags");
	comp.AddField(&BulletBodyComponentDefinition::m_AssignedGroups, "m_AssignedGroups", Reflect::FieldFlags::Discard);
	comp.AddField(&BulletBodyComponentDefinition::m_TrackPhysicalContactGroupMask, "m_TrackPhysicalContactGroupMask", Reflect::FieldFlags::Discard);
}