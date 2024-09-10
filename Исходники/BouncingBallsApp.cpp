void Ball::draw( const gl::VboMesh &mesh, bool useMotionBlur )
{
	float trailsize = math<float>::clamp( math<float>::floor(mPrevPosition.distance(mPosition)), 3.0f, 30.0f );
	float segments = trailsize - 1.0f;

	gl::pushModelView();

	if(useMotionBlur) {
		// draw ball with motion blur (using additive blending)
		gl::color( mColor / trailsize );

		Vec2f offset(0.0f, 0.0f);
		for(size_t i=0;i<trailsize;++i) {
			Vec2f difference = mPrevPosition.lerp( i / segments, mPosition ) - offset;	
			offset += difference;

			gl::translate( difference );
			gl::draw( mesh );
		}		
	}
	else {
		// draw ball without motion blur
		gl::color( mColor );
		gl::translate( mPosition );
		gl::draw( mesh );
	}

	gl::popModelView();

	//
	mHasBeenDrawn = true;
}