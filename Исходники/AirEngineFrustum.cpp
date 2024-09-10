		Air::Ray Frustum::BuildRay( Real x,Real y )
		{
#if 0
			POINT point;

			point.x	=	x;
			point.y	=	y;


			Common::Matrix mInverseView	=	m_matView;
			mInverseView.Inverse();

			// Compute the vector of the pick ray in screen space
			Float3 v;
			v.x = ( ( ( 2.0f * point.x ) / m_iScreenWidth ) - 1 ) /m_matProj.m00;
			v.y = -( ( ( 2.0f * point.y ) / m_iScreenHeight ) - 1 ) /m_matProj.m11;
			//如果是右手坐标系 Z必须为-1 左手坐标系为1 切需注意
			v.z = 1;//-m_ShaderParam.m_matProj[3][2];

			Ray ray;

			// Transform the screen space pick ray into 3D space
			ray.m_vDirection.x = v.x * mInverseView.m00 + v.y * mInverseView.m10 + v.z * mInverseView.m20;
			ray.m_vDirection.y = v.x * mInverseView.m01 + v.y * mInverseView.m11 + v.z * mInverseView.m21;
			ray.m_vDirection.z = v.x * mInverseView.m02 + v.y * mInverseView.m12 + v.z * mInverseView.m22;
			// 	 		//origin	=	m_vCurrentPosition;
			ray.m_vStart	=	Float3(mInverseView.m30,mInverseView.m31,mInverseView.m32);
			//Ray ray;
			ray.m_vDirection.Normalize();

			return	ray;
#else
			Matrix inverseVP = m_matViewProj;
			inverseVP.Inverse();

			Real nx = (2.0f * x) - 1.0f;
			Real ny = 1.0f - (2.0f * y);
			// Use midPoint rather than far point to avoid issues with infinite projection
			Float3 midPoint (nx, ny,  0.0f);

			// Get ray origin and ray target on near plane in world space
			Float3 rayTarget;


			rayTarget = inverseVP * midPoint;

			Float3 rayDirection = rayTarget - GetPosition();
			rayDirection.Normalize();

			return	Ray(GetPosition(),rayDirection);
#endif
			
		}