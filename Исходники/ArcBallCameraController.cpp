/// <summary>
/// Sets up a quaternion & position from vector camera components
/// and oriented the camera up
/// </summary>
/// <param name="eye">The camera position</param>
/// <param name="lookAt">The camera's look-at point</param>
/// <param name="up"></param>
void ArcBallCameraController::SetCamera(Vector3F position, Vector3F target, Vector3F up)
{
	m_bRecomputeViewMatrix = true;

	//Create a look at matrix, to simplify matters a bit
	Matrix4 temp;
	temp.LookAt(position, target, up);

	//invert the matrix, since we're determining the
	//orientation from the rotation matrix in RH coords
	temp.Invert();

	//set the position
	m_Target = target;

	//set distance
	m_fDistance = (target - position).Length();

	//create the new aspect from the look-at matrix
	m_ArcBallOrientation.FromMatrix(temp);

	//When setting a new eye-view direction 
	//in one of the gamble-locked modes, the yaw and
	//pitch gimble must be calculated.

	//first, get the direction projected on the x/z plne
	Vector3F dir = Direction();
	dir.y = 0.0f;
	if (dir.Length() == 0.0f)
	{
		dir = Vector3F::Forward();
	}
	dir.Normalize();

	//find the yaw of the direction on the x/z plane
	//and use the sign of the x-component since we have 360 degrees
	//of freedom
	m_fArcBallYaw = (acosf(-dir.z) * Sign(dir.x));

	//Get the pitch from the angle formed by the Up vector and the 
	//the forward direction, then subtracting Pi / 2, since 
	//we pitch is zero at Forward, not Up.
	m_fArcBallPitch = -(acosf(Vector3F::Dot(Vector3F::Up(), Direction())) - MATH_PI_DIV_2);
}