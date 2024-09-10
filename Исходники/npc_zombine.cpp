void CNPC_Zombine::DropGrenade( Vector vDir )
{
	if ( m_hGrenade == NULL )
		 return;

	m_hGrenade->SetParent( NULL );
	m_hGrenade->SetOwnerEntity( NULL );

	Vector vGunPos;
	QAngle angles;
	GetAttachment( "grenade_attachment", vGunPos, angles );

	IPhysicsObject *pPhysObj = m_hGrenade->VPhysicsGetObject();

	if ( pPhysObj == NULL )
	{
		m_hGrenade->SetMoveType( MOVETYPE_VPHYSICS );
		m_hGrenade->SetSolid( SOLID_VPHYSICS );
		m_hGrenade->SetCollisionGroup( COLLISION_GROUP_WEAPON );

		m_hGrenade->CreateVPhysics();
	}

	if ( pPhysObj )
	{
		pPhysObj->Wake();
		pPhysObj->SetPosition( vGunPos, angles, true );
		pPhysObj->ApplyForceCenter( vDir * 0.2f );

		pPhysObj->RecheckCollisionFilter();
	}

	m_hGrenade = NULL;
}