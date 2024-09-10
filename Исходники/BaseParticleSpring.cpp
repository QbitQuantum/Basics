Vec2f BaseParticleSpring::normalize()
{
	if( p1->fixed && p2->fixed )
		return Vec2f( 0, 0 );

	BaseParticle *particleBase = p1;
	BaseParticle *particleNorm = p2;

	if( p2->fixed )
	{
		particleBase = p2;
		particleNorm = p1;
	}

	Vec2f direction = particleNorm->position - particleBase->position;
	float d = direction.length();

	if( d != distance )
	{
		direction.normalize();
		Vec2f posNorm = particleNorm->position;
		particleNorm->position = particleBase->position + direction * distance;

		direction = particleNorm->position - particleBase->position;
		d = direction.length();

		return Vec2f( posNorm - particleNorm->position );
	}

	return Vec2f( 0, 0 );
}