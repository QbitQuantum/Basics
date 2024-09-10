	void Camera::_updateTM()
	{
		if (mTmChangeFlags == 0)
			return ;

		Node::_updateTM();

		const Float3 & pos = GetWorldPosition();
		const Quat & ort = GetWorldRotation();

		mMatView.MakeViewLH(pos, ort);

		if (GetOrthoEnable())
		{
			mMatProj.MakeOrthoLH(mOrthoWidth, mOrthoHeight, mNear, mFar);
		}
		else
		{
			mMatProj.MakePerspectiveLH(mFovy, mAspect, mNear, mFar);
		}

		mMatViewProj = mMatView * mMatProj;

		mFrustum.FromMatrix(mMatViewProj);

		// update corner
		Float3 corner[8] = { 
			Float3(-1, 1, 0), Float3(1, 1, 0), Float3(-1, -1, 0), Float3(1, -1, 0), 
			Float3(-1, 1, 1), Float3(1, 1, 1), Float3(-1, -1, 1), Float3(1, -1, 1)
		};

		Mat4 matInvProj = mMatProj, matInvView = mMatView;

		matInvProj.Inverse();
		matInvView.Inverse();

		for (int i = 0; i < 8; ++i)
			mViewCorner[i] = corner[i] * matInvProj;

		for (int i = 0; i < 8; ++i)
			mWorldCorner[i] = mViewCorner[i] * matInvView;
	}