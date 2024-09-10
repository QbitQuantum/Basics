	//---------------------------------------------------------------
	// Rotate point by quaternion
	Vector3 Quaternion_rotatePoint (const Quaternion& q, const Vector3& v) {

		// Inverse quaternion
		Quaternion inv = q;
		inv.invert();

		// Normalize inv
		inv.normalize();


		// q * v
		Quaternion temp = q * v;

		// temp * inv
		temp = temp * inv;

		return Vector3(temp[0], temp[1], temp[2]);
	}