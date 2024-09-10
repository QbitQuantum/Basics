	DReal DRenderable::getSquaredViewDepthToCamera( const DCamera* cam )
	{
		if (mCacheCamera == cam )
		{
			return mCacheDepth;
		}
		mCacheCamera = cam;
		DMatrix4 t = DMatrix4::IDENTITY;
		getWorldTransform(t);
		DVector3 p;
		t.getTranslate(p);
		mCacheDepth = (p-cam->getEyePosition()).dotProduct(cam->getDirection());
		return mCacheDepth;
	}