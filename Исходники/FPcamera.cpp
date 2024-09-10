void FPcamera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	view = (target - position).Normalized();
	Vector3 right = view.Cross(up).Normalized();
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	this->sensitivity = defaultSensitivity = 1.0f;

	sCameraType = LAND_CAM;

	for (int i = 0; i < 255; ++i)
	{
		myKeys[i] = false;
	}

	m_bCrouching = false;
	m_bCollideGround = true;
	m_bJumping = false;
	m_bRecoil = false;
	JumpVel = 0.0f;
	JUMPMAXSPEED = 200.f;
	JUMPACCEL = 100.f;
	GRAVITY = -200.f;

	rotationX = 0.f;
	rotationY = 0.f;
	recoil = 0.f;
}