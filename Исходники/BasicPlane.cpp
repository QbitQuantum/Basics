void BasicPlane::Update(float deltaTime)
{
	XMVECTOR forward = XMVector3Rotate(XMVectorSet(0, 0, 1, 0), XMLoadFloat4(&gameObject->transform.rotation));
	XMVECTOR right = XMVector3Rotate(XMVectorSet(1, 0, 0, 0), XMLoadFloat4(&gameObject->transform.rotation));
	XMVECTOR up = XMVector3Rotate(XMVectorSet(0, 1, 0, 0), XMLoadFloat4(&gameObject->transform.rotation));
	Vector3 velocityDirection = particleModel->velocity;
	velocityDirection.Normalize();
	Vector3 velocityForwards = forward * particleModel->velocity.Dot(forward);
	//thrust
	const float maxPlaneThrust = 30 * particleModel->mass;
	const float thrustChangeSpeed = 5 * particleModel->mass;
	static float planeThrust = maxPlaneThrust * 0.0;
	if (GetAsyncKeyState(VK_HOME))
	{
		planeThrust += thrustChangeSpeed * deltaTime;
	}
	if (GetAsyncKeyState(VK_DELETE))
	{
		planeThrust -= thrustChangeSpeed * deltaTime;
	}
	planeThrust = fmax(0.0f, fmin(maxPlaneThrust, planeThrust));
	particleModel->AddForce(forward * planeThrust);
	//lift and drag
	float lift;
	float percentVelocityForwards = particleModel->velocity.Length() < 1e-4 ? 0 : (velocityForwards.Length() / particleModel->velocity.Length());
	lift = 100 * particleModel->velocity.LengthSquared() * (percentVelocityForwards);
	if (planeThrust > 0.25 * maxPlaneThrust)
	{
		planeThrust -= thrustChangeSpeed * 0.5 * deltaTime;
	}
	//float density = 0.5;
	//float area = 10;
	//float liftCoefficient = 0.8f;
	//lift = 0.5 * density * particleModel->velocity.LengthSquared() * area * liftCoefficient;
	particleModel->AddForce(up * lift);
	float drag;
	drag = 300 * particleModel->velocity.LengthSquared() * (percentVelocityForwards * 0.2 + (1.0 - percentVelocityForwards) * 1.0);
	//float dragCoefficient = 0.1f;
	//drag = dragCoefficient * area * density * (particleModel->velocity.LengthSquared() / 2);
	particleModel->AddForce(-velocityDirection * drag);
	//rotate
	const float planeRotateSpeed = XMConvertToRadians(20 * deltaTime);
	XMVECTOR rotate = XMQuaternionIdentity();
	if (GetAsyncKeyState(VK_RIGHT))
	{
		rotate = XMQuaternionMultiply(rotate, XMQuaternionRotationNormal(forward, -planeRotateSpeed));
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		rotate = XMQuaternionMultiply(rotate, XMQuaternionRotationNormal(forward, planeRotateSpeed));
	}
	if (GetAsyncKeyState(VK_UP))
	{
		rotate = XMQuaternionMultiply(rotate, XMQuaternionRotationNormal(right, -planeRotateSpeed));
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		rotate = XMQuaternionMultiply(rotate, XMQuaternionRotationNormal(right, planeRotateSpeed));
	}
	gameObject->transform.rotation *= rotate;
}