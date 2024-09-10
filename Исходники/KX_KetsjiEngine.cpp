void KX_KetsjiEngine::PostProcessScene(KX_Scene* scene)
{
	bool override_camera = (m_overrideCam && (scene->GetName() == m_overrideSceneName));

	SG_SetActiveStage(SG_STAGE_SCENE);

	// if there is no activecamera, or the camera is being
	// overridden we need to construct a temporarily camera
	if (!scene->GetActiveCamera() || override_camera)
	{
		KX_Camera* activecam = NULL;

		RAS_CameraData camdata = RAS_CameraData();
		if (override_camera)
		{
			camdata.m_lens = m_overrideCamLens;
			camdata.m_clipstart = m_overrideCamNear;
			camdata.m_clipend = m_overrideCamFar;
			
			camdata.m_perspective= !m_overrideCamUseOrtho;
		}
		activecam = new KX_Camera(scene,KX_Scene::m_callbacks,camdata);
		activecam->SetName("__default__cam__");
	
			// set transformation
		if (override_camera) {
			const MT_CmMatrix4x4& cammatdata = m_overrideCamViewMat;
			MT_Transform trans = MT_Transform(cammatdata.getPointer());
			MT_Transform camtrans;
			camtrans.invert(trans);
			
			activecam->NodeSetLocalPosition(camtrans.getOrigin());
			activecam->NodeSetLocalOrientation(camtrans.getBasis());
			activecam->NodeUpdateGS(0);
		} else {
			activecam->NodeSetLocalPosition(MT_Point3(0.0, 0.0, 0.0));
			activecam->NodeSetLocalOrientation(MT_Vector3(0.0, 0.0, 0.0));
			activecam->NodeUpdateGS(0);
		}

		scene->AddCamera(activecam);
		scene->SetActiveCamera(activecam);
		scene->GetObjectList()->Add(activecam->AddRef());
		scene->GetRootParentList()->Add(activecam->AddRef());
		//done with activecam
		activecam->Release();
	}
	
	scene->UpdateParents(0.0);
}