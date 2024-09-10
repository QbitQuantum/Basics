	void Matrix4::makeInverseTransform(const Vector3& position, const Vector3& scale, const Quaternion& orientation)
	{
		// Invert the parameters
		Vector3 invTranslate = Vector3(-position.x,-position.y,-position.z);
		Vector3 invScale(1 / scale.x, 1 / scale.y, 1 / scale.z);
		Quaternion invRot = orientation.inverse();

		// Because we're inverting, order is translation, rotation, scale
		// So make translation relative to scale & rotation
		invTranslate = invRot * invTranslate; // rotate
		invTranslate *= invScale; // scale

		// Next, make a 3x3 rotation matrix
		Matrix3 rot3x3;
		invRot.ToRotationMatrix(rot3x3);

		// Set up final matrix with scale, rotation and translation
		m[0][0] = invScale.x * rot3x3[0][0]; m[0][1] = invScale.x * rot3x3[0][1]; m[0][2] = invScale.x * rot3x3[0][2]; m[0][3] = invTranslate.x;
		m[1][0] = invScale.y * rot3x3[1][0]; m[1][1] = invScale.y * rot3x3[1][1]; m[1][2] = invScale.y * rot3x3[1][2]; m[1][3] = invTranslate.y;
		m[2][0] = invScale.z * rot3x3[2][0]; m[2][1] = invScale.z * rot3x3[2][1]; m[2][2] = invScale.z * rot3x3[2][2]; m[2][3] = invTranslate.z;		

		// No projection term
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
	}