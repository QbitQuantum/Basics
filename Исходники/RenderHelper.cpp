void RenderHelper::DrawCircle3D(const Vector3 & center, const Vector3 &emissionVector, float32 radius, bool useFilling)
{
	Polygon3 pts;
    float32 angle = SEGMENT_LENGTH / radius;
	int ptsCount = (int)(PI_2 / (DegToRad(angle))) + 1;

	for (int k = 0; k < ptsCount; ++k)
	{
		float32 angleA = ((float)k / (ptsCount - 1)) * PI_2;
		float sinAngle = 0.0f;
		float cosAngle = 0.0f;
		SinCosFast(angleA, sinAngle, cosAngle);

		Vector3 directionVector(radius * cosAngle,
								radius * sinAngle,
								0.0f);
		
		// Rotate the direction vector according to the current emission vector value.
		Vector3 zNormalVector(0.0f, 0.0f, 1.0f);
		Vector3 curEmissionVector = emissionVector;
		curEmissionVector.Normalize();
		
		// This code rotates the (XY) plane with the particles to the direction vector.
		// Taking into account that a normal vector to the (XY) plane is (0,0,1) this
		// code is very simplified version of the generic "plane rotation" code.
		float32 length = curEmissionVector.Length();
		if (FLOAT_EQUAL(length, 0.0f) == false)
		{
			float32 cosAngleRot = curEmissionVector.z / length;
			float32 angleRot = acos(cosAngleRot);
			Vector3 axisRot(curEmissionVector.y, -curEmissionVector.x, 0);

			Matrix3 planeRotMatrix;
			planeRotMatrix.CreateRotation(axisRot, angleRot);
			Vector3 rotatedVector = directionVector * planeRotMatrix;
			directionVector = rotatedVector;
		}
		
		Vector3 pos = center - directionVector;
		pts.AddPoint(pos);
	}
	
	if (useFilling)
	{
		FillPolygon(pts);
	}
	else
	{
    	DrawPolygon(pts, false);
	}
}