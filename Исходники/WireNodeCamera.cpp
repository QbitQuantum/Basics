//----------------------------------------------------------------------------
void NodeCamera::Draw(TArray<NodeCamera*>& rNodeCameras, Spatial* pRoot,
	Culler& rCuller, Renderer* pRenderer)
{
	WIRE_ASSERT(pRenderer && pRoot);
	if (!pRenderer || !pRoot)
	{
		return;
	}

	const UInt maxCameraCount = 64;
	if (rNodeCameras.GetQuantity() >= 64)
	{
		WIRE_ASSERT(false);
		return;
	}

	// cull all skyboxes attached to cameras in the scene
	Spatial::CullingMode tempCullingModes[maxCameraCount];
	for (UInt i = 0; i < rNodeCameras.GetQuantity(); i++)
	{
		NodeCamera* pNodeCamera = rNodeCameras[i];
		WIRE_ASSERT(pNodeCamera);
		Node* pSkybox = pNodeCamera->mspSkybox;
		if (pSkybox && pNodeCamera->IsEnabled())
		{
			tempCullingModes[i] = pSkybox->Culling;
			pSkybox->Culling = Spatial::CULL_ALWAYS;
		}
	}

	for (UInt i = 0; i < rNodeCameras.GetQuantity(); i++)
	{
		NodeCamera* pNodeCamera = rNodeCameras[i];
		WIRE_ASSERT(pNodeCamera && pNodeCamera->Get());
		if (!pNodeCamera->IsEnabled())
		{
			continue;
		}

		Camera* pCamera = pNodeCamera->Get();

		rCuller.SetCamera(pCamera);
		rCuller.ComputeVisibleSet(pRoot);

		Float left;
		Float right;
		Float top;
		Float bottom;
		pCamera->GetViewport(left, right, top, bottom);
		UInt width = pRenderer->GetWidth();
		UInt height = pRenderer->GetHeight();
		Vector4F rect;
		rect.X() = MathF::Round(left*width);
		rect.Y() = MathF::Round((1.0F-top)*height);
		rect.Z() = MathF::Round((right-left)*width);
		rect.W() = MathF::Round((top-bottom)*height);

		ColorRGBA clearColor = pRenderer->GetClearColor();
		switch (rNodeCameras[i]->mClearFlag)
		{
		case CF_ALL:
			pRenderer->SetClearColor(pNodeCamera->GetClearColor());
			pRenderer->ClearBuffers(true, true, rect);
			pRenderer->SetClearColor(clearColor);
			break;

		case CF_Z_ONLY:
			pRenderer->ClearBuffers(false, true, rect);
			break;

		case CF_NONE:		
			break;

		default:
			WIRE_ASSERT(false);
		}

		pRenderer->SetCamera(pCamera);
		pRenderer->Draw(rCuller.GetVisibleSets());

		Node* pSkybox = pNodeCamera->mspSkybox;
		if (pSkybox)
		{
			pSkybox->Culling = Spatial::CULL_NEVER;
			rCuller.ComputeVisibleSet(pSkybox);
			pRenderer->Draw(rCuller.GetVisibleSets());
			pSkybox->Culling = Spatial::CULL_ALWAYS;
		}
	}

	// restore culling mode of all skyboxes attached to cameras in the scene
	for (UInt i = 0; i < rNodeCameras.GetQuantity(); i++)
	{
		NodeCamera* pNodeCamera = rNodeCameras[i];
		WIRE_ASSERT(pNodeCamera);
		Node* pSkybox = pNodeCamera->mspSkybox;
		if (pSkybox && pNodeCamera->IsEnabled())
		{
			pSkybox->Culling = tempCullingModes[i];
		}
	}
}