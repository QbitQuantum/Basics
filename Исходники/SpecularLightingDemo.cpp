	SpecularLightingDemo::SpecularLightingDemo(Library::Game & game) :
		DrawableGameComponent(game), mVertexShader(), mIndexCount(), mPixelShader(), mWorldMatrix(MatrixHelper::Identity), mAnimationEnabled(true)
	{
		XMStoreFloat4x4(&mWorldMatrix, XMMatrixIdentity());
	}