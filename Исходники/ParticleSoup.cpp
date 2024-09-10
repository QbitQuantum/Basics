void ParticleSoup::update()
{
	static float prevTime = (float)app::getElapsedSeconds();
	float curTime = (float)app::getElapsedSeconds();
	float dt = curTime - prevTime;
	prevTime = curTime;

	Rectf bounds = ci::app::getWindowBounds();
	float minX = -kBorder;
	float minY = -kBorder;
	float maxX = bounds.getWidth();
	float maxY = bounds.getHeight();

	// Avoid the borders in the remap because the velocity might be zero.
	// Nothing interesting happens where velocity is zero.
	float dx = (float)(mFluid->resX() - 4)/(float)bounds.getWidth();
	float dy = (float)(mFluid->resY() - 4)/(float)bounds.getHeight();
	for( int i = 0; i < numParticles(); ++i ) {
		Particle& part = mParticles.at( i );
		if( part.pos().x < minX || part.pos().y < minY || part.pos().x >= maxX || part.pos().y >= maxY ) {
			vec2 P;
			P.x = Rand::randFloat( bounds.x1 + 5.0f, bounds.x2 - 5.0f );
			P.y = Rand::randFloat( bounds.y1 + 5.0f, bounds.y2 - 5.0f );
			float life = Rand::randFloat( 2.0f, 3.0f );
			part.reset( P, life, mColor );
		}

		float x = part.pos().x*dx + 2.0f;
		float y = part.pos().y*dy + 2.0f;
		vec2 vel = mFluid->velocity().bilinearSampleChecked( x, y, vec2( 0.0f, 0.0f ) );
		part.addForce( vel );
		part.update( mFluid->dt(), dt );
	}
}