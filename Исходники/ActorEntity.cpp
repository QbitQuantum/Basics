void CActorEntity::update( float timeAlpha )
{
	bool alive = mGameEntity->isAlive();
	if( alive ) {
		// fade out the outline
		float dt = CSystemTimer::getInstance().getDeltaTimeS();
		mOutlineTTL -= dt;
		if( mOutlineTTL < 0.0f )
			mOutlineTTL = 0.0f;

		SMatrix4x4& m = mWorldMat;
		SVector3 pos = samplePos( timeAlpha );
		SVector3 dir = samplePos( timeAlpha + 0.1f ) - pos;
		if( dir.lengthSq() < 1.0e-3f )
			dir = m.getAxisZ();
		else
			dir.normalize();

		if( mGameEntity->getType() == ENTITY_BLOCKER ) {
			double tt = CSystemTimer::getInstance().getTimeS();
			D3DXMatrixRotationY( &m, tt * 0.2f );
			m.getOrigin() = pos;
			m.getOrigin().y += sinf( tt * 0.6f ) * 0.2f;
		} else {
			m.getOrigin() = pos;
			m.getAxisZ() = dir;
			m.getAxisZ().y *= 0.2f;
			m.getAxisZ().normalize();
			m.getAxisY().set( 0, 1, 0 );
			m.getAxisX() = m.getAxisY().cross( m.getAxisZ() );
			m.getAxisX().normalize();
			m.getAxisY() = m.getAxisZ().cross( m.getAxisX() );
		}
	} else {
		mOutlineTTL = 0.0f;
	}
}