void ForcePerlin::apply( std::list<Particle> &particles, int counter )
{
	for( list<Particle>::iterator particleIt = particles.begin(); particleIt != particles.end(); ++particleIt )
	{
		Vec3f noise = mPerlin.dfBm( Vec3f( particleIt->mLoc[0].x, particleIt->mLoc[0].y, particleIt->mLoc[0].z ) * 0.01f + Vec3f( 0, 0, counter / 100.0f ) );
		noise.normalize();
		noise *= mMagnitude;
		particleIt->mAcc += Vec3f( noise.x, noise.y, noise.z );
	}
}