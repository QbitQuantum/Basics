	void RenderEngine::renderScene(Mat4 const& matView)
	{
		Mat4 matViewInv;
		float det;
		matView.inverse( matViewInv , det );
		mEffect.bind();
		mEffect.setParam( "gParam.matViewInv" , matViewInv );

		glLoadMatrixf( matView );
		renderGroup( mParam.world->mRootGroup );

		mEffect.unbind();
	}