	//-----------------------------------------------------------------------
	Real LiSPSMShadowCameraSetup::calculateNOpt(const Matrix4& lightSpace, 
		const AxisAlignedBox& bodyBABB_ls, const PointListBody& bodyLVS, 
		const Camera& cam) const
	{
		// get inverse light space matrix
		Matrix4 invLightSpace = lightSpace.inverse();

		// get view matrix
		const Matrix4& viewMatrix = cam.getViewMatrix();

		// calculate z0_ls
		const Vector3 e_ws  = getNearCameraPoint_ws(viewMatrix, bodyLVS);
		const Vector3 z0_ls = calculateZ0_ls(lightSpace, e_ws, bodyBABB_ls.getMaximum().z, cam);

		// z1_ls has the same x and y values as z0_ls and the minimum z values of bodyABB_ls
		const Vector3 z1_ls = Vector3(z0_ls.x, z0_ls.y, bodyBABB_ls.getMinimum().z);

		// world
		const Vector3 z0_ws = invLightSpace * z0_ls;
		const Vector3 z1_ws = invLightSpace * z1_ls;

		// eye
		const Vector3 z0_es = viewMatrix * z0_ws;
		const Vector3 z1_es = viewMatrix * z1_ws;

		const Real z0 = z0_es.z;
		const Real z1 = z1_es.z;

		// check if we have to do uniform shadow mapping
		if ((z0 < 0 && z1 > 0) ||
			(z1 < 0 && z0 > 0))
		{
			// apply uniform shadow mapping
			return 0.0;
		}
		return cam.getNearClipDistance() + Math::Sqrt(z0 * z1) * mOptAdjustFactor;
	}