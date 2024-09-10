void DelaunayMeshMaker::draw()
{
	gl::clear();

	gl::pushMatrices();

	gl::pushModelView();
		gl::color( ColorA::white() );

		if( mMesh.getNumTriangles() > 0 ){
			if( mApplyPhongShading )
				mPhongShader.bind();

			gl::enableDepthRead();
			gl::enableDepthWrite();

			gl::disableAlphaBlending();

			if( mDrawWireframe )
				gl::enableWireframe();

			gl::draw( mVboMesh );

			if( mDrawWireframe )
				gl::disableWireframe();

			if( mApplyPhongShading )
				mPhongShader.unbind();
		}

		if( mAlpha > 0.0f ){
			gl::disableDepthRead();
			gl::disableDepthWrite();

			gl::enableAlphaBlending();

			gl::color( ColorA( 1,1,1, mAlpha ) );
			gl::draw( mSurface );
		}
	gl::popModelView();

	gl::popMatrices();

	if( mTesselator->isRunning() ){
		gl::disableDepthRead();
		gl::disableDepthWrite();

		gl::enableAlphaBlending();

		gl::color( ColorA(0.0f, 0.0f, 0.0f, 0.5f ) );
		gl::drawSolidRect( Rectf( 0, 0, app::getWindowWidth(), app::getWindowHeight() ) );

		gl::pushModelView();
			gl::translate( app::getWindowSize()/2 );
			double time = getElapsedSeconds();
			double fraction = time - (int) time;
			int numFractions = 12;

			for(int i=0;i<numFractions;++i) {
				float a = (float) (fraction + i * (1.0f / (float)numFractions));
				a -= (int) a;

				gl::pushModelView();
				gl::rotate( i * ( -360.0f/(float)numFractions ) );
				gl::color( ColorA(1,1,1,1-a) );
				gl::drawSolidRect( Rectf(-6.0f, -44.0f, +6.0f, -31.0f) );
				gl::popModelView();
			}
		gl::popModelView();
	}

	mParams.draw();
}