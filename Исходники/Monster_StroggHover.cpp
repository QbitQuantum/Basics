void rvMonsterStroggHover::TryStartPursuit ( void )
{
	if ( GetEnemy() )
	{
		inPursuit = false;
		if ( !marker.GetEntity() ) {
			//wtf?!
			assert(0);
			return;
		}
		attackPosOffset.Set( gameLocal.random.CRandomFloat()*500.0f, gameLocal.random.CRandomFloat()*500.0f, 0.0f );
		if ( attackPosOffset.Length() < 150.0f )
		{
			attackPosOffset.Normalize();
			attackPosOffset *= 150.0f;
		}
		attackPosOffset.z = (gameLocal.random.CRandomFloat()*30.0f)+50.0f + move.fly_offset;
		marker.GetEntity()->GetPhysics()->SetOrigin( GetEnemy()->GetPhysics()->GetOrigin()+attackPosOffset );
		if ( MarkerPosValid() )
		{
			if ( MoveToEntity( marker ) )
			{
				inPursuit = true;
				holdPosTime = 0;
				SetState( "State_Pursue" );
			}
		}
	}
}