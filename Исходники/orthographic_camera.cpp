void OrthographicCamera::rotateCamera(float rx, float ry)
{
	// Don't let the model flip upside-down (There is a singularity
	// at the poles when 'up' and 'direction' are aligned)
	float tiltAngle = acos(m_up.Dot3(m_direction));
	if (tiltAngle - ry > 3.13)
		ry = tiltAngle - 3.13;
	else if (tiltAngle - ry < 0.01)
		ry = tiltAngle - 0.01;

	Matrix rotMat = Matrix::MakeAxisRotation(m_up, rx);
	rotMat *= Matrix::MakeAxisRotation(m_horizontal, ry);

	rotMat.Transform(m_center);
	rotMat.TransformDirection(m_direction);

	// ===========================================
	// ASSIGNMENT 5: Fix any other affected values
	// ===========================================
}