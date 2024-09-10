	//--------------------------------------------------------------------------------------------------------------
	//获取屏幕坐标在世界空间的投影射线
	bool Viewport::GetWorldRayFromScreenPoint( LONG nX, LONG nY, Ray3* pRay3 )
	{
		if( nX < (LONG)mLeft || nY < (LONG)mTop )
			return false;
		
		nX -= mLeft;
		nY -= mTop;

		if( nX > (LONG)mWidth || nY > (LONG)mHeight )
			return false;

		//将屏幕坐标转换为以中心为原点的单位化坐标（投影转换）
		float fTanFOV2 = Tan( FK_PI * 0.125 );		// Tan( FK_DegreeToRadian( 45.0f / 2.0f )
		float fX = fTanFOV2 * ( (float)nX / ( (float)mWidth * 0.5f ) - 1.0f ) * mAspect;
		float fY = fTanFOV2 * ( 1.0f - (float)nY / ( (float)mHeight * 0.5f ) );

		//将经过投影转换的坐标值转换到世界空间坐标
		static Matrix4 MatInvView;
		static Vector3 VectorEnd;

		MatInvView = mpCamera->mViewMatrix.GetInverse();

		pRay3->mOrigin.x = fX * mpCamera->mViewNear;
		pRay3->mOrigin.y = fY * mpCamera->mViewNear;
		pRay3->mOrigin.z = mpCamera->mViewNear;

		VectorEnd.x = fX * mpCamera->mViewFar;
		VectorEnd.y = fY * mpCamera->mViewFar;
		VectorEnd.z = mpCamera->mViewFar;

		pRay3->mOrigin *= MatInvView;
		VectorEnd *= MatInvView;

		pRay3->mDirection = VectorEnd - pRay3->mOrigin;
		pRay3->mDirection.Normalize();

		return true;
	}