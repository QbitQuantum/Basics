void Helium::BulletBodyDefinition::PopulateMetaType( Reflect::MetaStruct& comp )
{
	comp.AddField(&BulletBodyDefinition::m_Shapes, TXT( "m_Shapes" ));
	comp.AddField(&BulletBodyDefinition::m_Restitution, TXT( "m_Restitution" ));
	comp.AddField(&BulletBodyDefinition::m_LinearDamping, TXT( "m_LinearDamping" ));
	comp.AddField(&BulletBodyDefinition::m_AngularDamping, TXT( "m_AngularDamping" ));
	comp.AddField(&BulletBodyDefinition::m_LockPositionX, "m_LockPositionX");
	comp.AddField(&BulletBodyDefinition::m_LockPositionY, "m_LockPositionY");
	comp.AddField(&BulletBodyDefinition::m_LockPositionZ, "m_LockPositionZ");
	comp.AddField(&BulletBodyDefinition::m_LockRotationX, "m_LockRotationX");
	comp.AddField(&BulletBodyDefinition::m_LockRotationY, "m_LockRotationY");
	comp.AddField(&BulletBodyDefinition::m_LockRotationZ, "m_LockRotationZ");
	comp.AddField(&BulletBodyDefinition::m_IsKinematic, "m_IsKinematic");
	comp.AddField(&BulletBodyDefinition::m_DisableCollisionResponse, "m_DisableCollisionResponse");
}