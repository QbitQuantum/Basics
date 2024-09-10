/*virtual*/ void WBCompEldIcicles::Tick( float DeltaTime )
{
	XTRACE_FUNCTION;
	PROFILE_FUNCTION;

	Unused( DeltaTime );

	WBEntity* const				pEntity		= GetEntity();
	ASSERT( pEntity );

	WBCompEldAnchor* const		pAnchor		= GET_WBCOMP( pEntity, EldAnchor );
	ASSERT( pAnchor );

	if( !pAnchor->IsAnchored() )
	{
		return;
	}

	WBEntity* const				pPlayer		= EldritchGame::GetPlayer();

	if( !pPlayer )
	{
		return;
	}

	WBCompStatMod* const		pPlayerStatMod		= GET_WBCOMP( pPlayer, StatMod );
	ASSERT( pPlayerStatMod );

	WB_MODIFY_FLOAT( IgnoreIcicles, 0.0f, pPlayerStatMod );
	const bool IgnoreIcicles = ( WB_MODDED( IgnoreIcicles ) != 0.0f );

	if( IgnoreIcicles )
	{
		return;
	}

	EldritchWorld* const		pWorld				= GetWorld();
	ASSERT( pWorld );

	WBCompEldTransform* const	pTransform			= pEntity->GetTransformComponent<WBCompEldTransform>();
	ASSERT( pTransform );

	WBCompEldCollision* const	pCollision			= GET_WBCOMP( pEntity, EldCollision );
	ASSERT( pCollision );

	WBCompEldTransform* const	pPlayerTransform	= pPlayer->GetTransformComponent<WBCompEldTransform>();
	ASSERT( pPlayerTransform );

	WBCompEldCollision* const	pPlayerCollision	= GET_WBCOMP( pPlayer, EldCollision );
	ASSERT( pPlayerCollision );

	const Vector	CheckOffset	= Vector( 0.0f, 0.0f, -m_CheckDistance );
	const Vector	TraceStart	= pTransform->GetLocation();
	Vector			TraceEnd	= TraceStart + CheckOffset;

	// Early out if player doesn't intersect the trace bounds.
	Vector			EntityExtents	= pCollision->GetExtents();
	EntityExtents.z					= 0.0f;
	const AABB		TraceBox		= AABB( TraceEnd - EntityExtents, TraceStart + EntityExtents );
	const AABB		PlayerBox		= pPlayerCollision->GetBounds();
	if( !TraceBox.Intersects( PlayerBox ) )
	{
		return;
	}

	// Move trace up to the top of player so we don't check occlusion beyond player.
	const float	PlayerTopZ	= PlayerBox.m_Max.z;
	TraceEnd.z				= PlayerTopZ;

	// Do an occlusion test to make sure there's nothing blocking the trace.
	CollisionInfo Info;
	Info.m_CollideWorld			= true;
	Info.m_CollideEntities		= true;
	Info.m_CollidingEntity		= pEntity;
	Info.m_UserFlags			= EECF_Occlusion;
	Info.m_StopAtAnyCollision	= true;

	const bool Occluded			= pWorld->LineCheck( TraceStart, TraceEnd, Info );
	if( Occluded )
	{
		return;
	}

	// All checks passed. Unanchor to initiate falling sequence
	WB_MAKE_EVENT( Unanchor, pEntity );
	WB_DISPATCH_EVENT( GetEventManager(), Unanchor, pEntity );
}