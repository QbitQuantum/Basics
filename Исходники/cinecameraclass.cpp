void CineCameraClass::Tilt(float degree)
{

	double horizontalMagnitude = sqrt(direction.x * direction.x + direction.z * direction.z);
	float angle = (float)atan(direction.y / horizontalMagnitude);
	if ((angle - degree*(XM_PIDIV2/100*CAMERA_TILT_SPEED) < XM_PIDIV2) &&
		(angle - degree*(XM_PIDIV2/100*CAMERA_TILT_SPEED) > -XM_PIDIV2))
	{
		rotation.y += degree*(XM_PIDIV2/100*CAMERA_TILT_SPEED);
		//NOTE: currently the argument delta is not used
		wchar_t* outstring = L"CineCameraClass::Tilt\n";
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

		//Tilt the camera upwards rotating about the sideways direction vector
	
		XMVECTOR sideWaysVector = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&upDirection), XMLoadFloat3(&direction) ));
		XMVECTOR tiltRotationQuaternion = XMQuaternionRotationAxis(sideWaysVector, degree*(XM_PIDIV2/100*CAMERA_TILT_SPEED));

		XMStoreFloat3(&direction, XMVector3Rotate( XMLoadFloat3(&direction), tiltRotationQuaternion));
		XMStoreFloat3(&upDirection, XMVector3Rotate( XMLoadFloat3(&upDirection), tiltRotationQuaternion));
	}
}