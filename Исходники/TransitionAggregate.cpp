void CTransitionAggregate::Load( ILTMessage_Read *pMsg, uint32 dwLoadFlags )
{
	if( !pMsg ) return;
	
	LOAD_HOBJECT( m_hObject );

	// The rest is dependent on the load type...

	if( dwLoadFlags != LOAD_TRANSITION ) return;
	
	HOBJECT hTransArea = g_pTransMgr->GetTransitionArea();
	if( !hTransArea ) return;
	
	TransitionArea *pTransArea = (TransitionArea*)g_pLTServer->HandleToObject( hTransArea );
	if( !pTransArea ) return;

	LTransform tfLocal;
	LTransform tfObjectWorld;
	LTVector vVelRel;
	LTransform const& tfTransAreaWorld = pTransArea->GetWorldTransform( );
	LTMatrix mRotation;
	tfTransAreaWorld.m_Rot.ConvertToMatrix( mRotation );

	LOAD_VECTOR( tfLocal.m_Pos );
	LOAD_ROTATION( tfLocal.m_Rot );
	LOAD_VECTOR( vVelRel );
	
	// Calc pos and rot based on offsets and current TransArea...

	tfObjectWorld.m_Pos = tfTransAreaWorld.m_Pos + ( mRotation * tfLocal.m_Pos );
	tfObjectWorld.m_Rot = tfTransAreaWorld.m_Rot * tfLocal.m_Rot;
	LTVector vVel = mRotation * vVelRel;

	if( IsPlayer( m_hObject ))
	{
		// Since the PlayerObj is controlled by the client we need to notify the
		// client of the rotation.  We are only worried about the Yaw since Roll doesn't 
		// matter and Pitch can be preserved on the client.


		CPlayerObj *pPlayer = (CPlayerObj*)g_pLTServer->HandleToObject( m_hObject );
		if( !pPlayer ) return;

		
		LTFLOAT		fYaw;
		LTVector	vF = tfObjectWorld.m_Rot.Forward();

		// We don't care about Roll...

		vF.y = 0.0f; 
		vF.Normalize();

		// Yaw = arctan( vF.x / vF.z );
		// atan2 is well defined even for vF.z == 0

		fYaw = (LTFLOAT)atan2( vF.x, vF.z );
		
		// Inform the client of the correct camera/player orientation...

		LTVector vVec( 0.0f, fYaw, 0.0f );
		
		CAutoMessage cMsg;
		cMsg.Writeuint8( MID_PLAYER_ORIENTATION );
		cMsg.Writeuint8( MID_ORIENTATION_YAW );
		cMsg.WriteLTVector( vVec );
		g_pLTServer->SendToClient(cMsg.Read(), pPlayer->GetClient(), MESSAGE_GUARANTEED);
		
	}

	g_pLTServer->SetObjectPos( m_hObject, &tfObjectWorld.m_Pos );
	g_pLTServer->SetObjectRotation( m_hObject, &tfObjectWorld.m_Rot );
	g_pPhysicsLT->SetVelocity( m_hObject, &vVel );
}