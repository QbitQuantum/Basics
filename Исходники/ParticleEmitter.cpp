void ParticleEmitter::repulseParticles()
{
	for( list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1 ){
		
		list<Particle>::iterator p2 = p1;
		for( ++p2; p2 != mParticles.end(); ++p2 ) {
			Vec2f dir = p1->mLoc - p2->mLoc;
			
			float thresh = ( p1->mRadius + p2->mRadius ) * 5.0f;
			if( dir.x > -thresh && dir.x < thresh && dir.y > -thresh && dir.y < thresh ){
				float distSqrd = dir.lengthSquared() * dir.length();
				
				if( distSqrd > 0.0f ){
					float F = 1.0f/distSqrd;
					dir.normalize();
					
					// acceleration = force / mass
					p1->mAcc += ( F * dir ) / p1->mMass;
					p2->mAcc -= ( F * dir ) / p2->mMass;

					// TMP
					p1->mAcc *= 0.005;
					p2->mAcc *= 0.005;
					
				}
			}
		}
	}
}