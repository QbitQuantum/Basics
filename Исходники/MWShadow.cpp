	void Shadow::_updateCamera()
	{
		Camera * worldCam = World::Instance()->MainCamera();

		mInverseWorldCameraVP = World::Instance()->MainCamera()->GetViewProjMatrix().Inverse();

		float nearClip = worldCam->GetNearClip();
		float farClip = mDist[K_NumShadowLayers - 1];

		Vec3 xAixs = worldCam->GetDirection();
		Vec3 yAixs = worldCam->GetUp();
		Vec3 zAixs = Environment::Instance()->GetEvParam()->LightDir;

		if (Math::Abs(zAixs.Dot(yAixs)) > 0.99f)
		{
			yAixs = zAixs.CrossN(xAixs);
			xAixs = yAixs.CrossN(zAixs);
		}
		else
		{
			xAixs = yAixs.CrossN(zAixs);
			yAixs = zAixs.CrossN(xAixs);
		}

		if (xAixs.Dot(worldCam->GetDirection()) < 0)
			xAixs = -xAixs;

		yAixs = zAixs.CrossN(xAixs);

		Mat4 matView;
		Quat qOrient = Quat::S_FromAxis(xAixs, yAixs, zAixs);

		matView.MakeViewLH(worldCam->GetPosition(), qOrient);

		Vec3 corner[8], t_corner[8];

		worldCam->GetWorldCorner(t_corner, nearClip, farClip);

		float dist = t_corner[4].Distance(t_corner[5]);

		for (int i = 0; i < 8; ++i)
		{
			corner[i] = t_corner[i] * matView;
		}

		Aabb aabb = Aabb::Invalid;

		for (int i = 0; i < 8; ++i)
		{
			aabb.minimum = aabb.minimum.Minimum(corner[i]);
			aabb.maximum = aabb.maximum.Maximum(corner[i]);
		}

		Vec3 center = aabb.GetCenter();
		float width = aabb.GetWidth();
		float height = aabb.GetHeight();
		float depth = aabb.GetDepth();

		center *= matView.Inverse();

		Vec3 lightPos = center - zAixs * mOffset;

		mLightCamera->SetPosition(lightPos);
		mLightCamera->SetOrientation(qOrient);
		mLightCamera->SetOrthoWidth(width);
		mLightCamera->SetOrthoHeight(height);
		mLightCamera->SetNearClip(nearClip);
		mLightCamera->SetFarClip(mOffset + depth);
		mLightCamera->SetProjectionType(PROJTYPE_ORTHO);
	}