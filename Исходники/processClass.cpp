bool processClass::update(double time, double rot)
{
	cube1World = XMMatrixIdentity();

	camPosition = XMVectorSet(-10.0f * XMScalarSin(rot),  7.0f, -10.0f * XMScalarCos(rot) , 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
	cube2World = XMMatrixIdentity();

	return true;
}