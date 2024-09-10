void SpotlightSample::InitializeCamera()
{
	mCamera.mTransform = new Transform();
	mCamera.mTransform->mPosition = { 0, 50, -50 };
	mCamera.mTransform->RotatePitch(XMConvertToRadians(45.f));
	mCamera.Update();
	mCamera.UpdateProjection(0.25f * 3.1415926535f, AspectRatio(), 0.1f, 100.0f);
}