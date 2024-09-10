	void KungFuPOC::UpdateKinectSkeletonData()
	{
		float3 offset(0.0, 0.0, 0.0);
		
		SkeletonData data;
		kinectController.GetSkeletonData(&data);
		int skeletonIndex = GetActiveSkeleton(data.skeletonData);
		if (skeletonIndex < 0) return;

		NUI_SKELETON_DATA skeleton = data.skeletonData[skeletonIndex];
		Vector4* positions = skeleton.SkeletonPositions;
		
		float dz = 0.0;
		for (int i = 0; i != NUI_SKELETON_POSITION_COUNT; ++i) {			
			Vector4& pos = positions[i];
			pos.z = -pos.z;
			// don't let player come too close to the painting!
			if (i == 0) {
				if (pos.z > PAINTING_Z - MINIMUM_PLAYER_DISTANCE) {
					dz = pos.z - (PAINTING_Z - MINIMUM_PLAYER_DISTANCE);
				}
			}
			pos.z -= dz;
		}

		stickFigureMesh->Update(deviceContext, positions);

		matrix4x4 projectionMtx = XMLoadFloat4x4(&projection);
		for (auto it = paintLogics.begin(); it != paintLogics.end(); ++it) {
			deviceContext->OMSetRenderTargets(1, &backBufferView, depthStencilView);
			SetViewport(0, 0, (float)windowWidth, (float)windowHeight);
			(*it)->Update(projectionMtx, deviceContext, positions);
		}
	}