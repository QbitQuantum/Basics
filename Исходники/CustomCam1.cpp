void CustomCam1::Init(const Vector3& pos, const Vector3& target, const Vector3& up, const float mouseSensitivity)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	this->mouseSensitivity = mouseSensitivity;
	mouseX = 0.0;
	mouseY = 0.0;

	f_currentPitch = CalAnglefromPosition(target, position, false);
	f_pitchLimit = 80.f;
}