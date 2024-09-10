void CActorPlane::Update()
{
	static float fRotationX;
	static float fRotationY;

	if (Input->IsKeyDown(VK_RIGHT))
		fRotationX += .1f;

	if (Input->IsKeyDown(VK_LEFT))
		fRotationX -= .1f;

	if (Input->IsKeyDown(VK_UP))
		fRotationY += .1f;

	if (Input->IsKeyDown(VK_DOWN))
		fRotationY -= .1f;

	this->mxWorld = XMMatrixRotationY( fRotationY ) * XMMatrixRotationX( fRotationX );
}