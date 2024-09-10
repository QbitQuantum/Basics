void RayTracingDemo::draw(const GameTimer & timer)
{
	mTextureSize = { static_cast<float>(mGame->screenWidth()), static_cast<float>(mGame->screenHeight()) };

	ID3D11DeviceContext * deviceContext = mGame->deviceContext();
	mMaterial->TextureSize() << XMLoadFloat2(&mTextureSize);
	mMaterial->BlueColor() << mBlueColor;
	mMaterial->CameraPosition() << mCamera->positionVector();
	mMaterial->InverseViewMatrix() << XMMatrixInverse(nullptr,mCamera->viewMatrix());
	mMaterial->InverseProjectionMatrix() << XMMatrixInverse(nullptr, mCamera->projectionMatrix());
	mMaterial->ViewMatrix() << mCamera->viewMatrix();
	mMaterial->Position() << XMLoadFloat3(&mPosition);
	mMaterial->LightPosition() << XMLoadFloat3(&mLightPosition);
	mMaterial->ProjectionMatrix() << mCamera->projectionMatrix();
	//mMaterial->SpherePosition() << mPosition;

	mMaterial->OutputTexture() << mOutputTexture;
	mComputePass->apply(0, deviceContext);

	deviceContext->Dispatch(mThreadGroupCount.x, mThreadGroupCount.y, 1);
	static ID3D11UnorderedAccessView * emptyUAV = nullptr;
	deviceContext->CSSetUnorderedAccessViews(0, 1, &emptyUAV, nullptr);

	mFullScreenQuad->draw(timer);
}