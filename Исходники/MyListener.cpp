bool MyListener::frameStarted(float timeSinceLastFrame)
{
	
	mKeyboard->capture();
	mMouse->capture();
	cameraMan->update(timeSinceLastFrame);
	debugWindow->updateFPS(timeSinceLastFrame);

	elapsedTime+=timeSinceLastFrame*0.3f;
	Light* l = mSceneMgr->mShadingMgr->directionalLight;

	
	//XMStoreFloat3(&baseDir,XMVector2Normalize(XMLoadFloat3(&baseDir)));

	//l->direction = baseDir;//XMFLOAT3(baseDir.x*cos(elapsedTime)-baseDir.z*sin(elapsedTime),baseDir.y,baseDir.x*cos(elapsedTime)+baseDir.z*sin(elapsedTime));
	//XMStoreFloat3(&l->direction,XMVector2Normalize(XMLoadFloat3(&l->direction)));
	XMStoreFloat3(&l->direction,XMVector3Rotate(XMLoadFloat3(&baseDir),XMLoadFloat4(&lightQuat)));

	mSceneMgr->getGuiManager()->update(timeSinceLastFrame/1000.0f);

	mPhysicsMgr->fetchResults(true);
	mPhysicsMgr->synchronizeEntities();
	mPhysicsMgr->startSimulating(timeSinceLastFrame);

	mShadowMapping->renderShadowMaps();

	//if(count%2==0)
	voxelScene->voxelizeScene(XMFLOAT3(30,30,30),XMFLOAT3(0,0,0));

	mShadowMapping->renderCaustics();

	voxelScene->endFrame(XMFLOAT3(30,30,30),XMFLOAT3(0,0,0));

	count++;

	//voxelScene->unifyVoxels();
	mSceneMgr->setCurrentCamera(mSceneMgr->getCamera("main"));
	mSceneMgr->mShadingMgr->updatePerFrameConstants(timeSinceLastFrame,mSceneMgr->getCamera(),mSceneMgr->getCamera("sun"));
	
	mRS->setBackbufferAsRenderTarget();
	mRS->clearViews();
	//mSceneMgr->renderSceneWithMaterial(mSceneMgr->getMaterial("depthWrite"));
	//mSceneMgr->renderScene();

	pp->render();


	mSceneMgr->getGuiManager()->render();

	mRS->swapChain_->Present(0,0);

	if(xp) xr+=timeSinceLastFrame; else if(xm) xr-=timeSinceLastFrame;
	if(zp) zr+=timeSinceLastFrame; else if(zm) zr-=timeSinceLastFrame;

	XMStoreFloat4(&lightQuat,XMQuaternionRotationRollPitchYaw(xr,0,zr));

	return continue_rendering;
}