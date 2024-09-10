void ParticleEmitter3D::CalculateParticlePositionForCircle(Particle* particle, const Vector3& tempPosition,
														   const Matrix3& rotationMatrix)
{
	float32 curRadius = 1.0f;
	if (radius)
	{
		curRadius = radius->GetValue(time);
	}

	float32 curAngle = PI_2 * (float32)Random::Instance()->RandFloat();
	if (emitterType == EMITTER_ONCIRCLE_VOLUME)
	{
		// "Volume" means we have to emit particles from the whole circle.
		curRadius *= (float32)Random::Instance()->RandFloat();
	}

	float sinAngle = 0.0f;
	float cosAngle = 0.0f;
	SinCosFast(curAngle, sinAngle, cosAngle);

	Vector3 directionVector(curRadius * cosAngle,
							curRadius * sinAngle,
							0.0f);
		
	// Rotate the direction vector according to the current emission vector value.
	Vector3 zNormalVector(0.0f, 0.0f, 1.0f);
	Vector3 curEmissionVector;
	if (emissionVector)
	{
		curEmissionVector = emissionVector->GetValue(time);
		curEmissionVector.Normalize();
	}
		
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
		
	particle->position = tempPosition + TransformPerserveLength(directionVector, rotationMatrix);	
}