void Matrix4::makeInverseTransform(const Vector3& position, const Vector3& scale, const Quaternion& orientation)
{

	Vector3 invTranslate = -position;
	Vector3 invScale(1 / scale.x, 1 / scale.y, 1 / scale.z);
	Quaternion invRot = orientation.inverse();

	invTranslate *= invScale; 
	invTranslate = invRot.rotate(invTranslate); 


	Matrix3 rot3x3, scale3x3;
	rot3x3 = invRot.toRotationMatrix();
	scale3x3 = Matrix3::ZERO;
	scale3x3[0][0] = invScale.x;
	scale3x3[1][1] = invScale.y;
	scale3x3[2][2] = invScale.z;


	*this = scale3x3 * rot3x3;
	this->setTrans(invTranslate);


	d[3][0] = 0; d[3][1] = 0; d[3][2] = 0; d[3][3] = 1;
}