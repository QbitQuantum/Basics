// Ad-hoc
void CFlyer::ProcessMovement(float frameTime)
{
	frameTime = min(1.f, frameTime);

	float desiredSpeed = m_vDesiredVelocity.GetLength();
	const float maxDeltaSpeed = 100.f;

	float deltaSpeed = min(maxDeltaSpeed, fabsf(desiredSpeed - m_stats.speed));

	// Advance "m_velocity" towards "m_vDesiredVelocity" at the speed proportional to (1 / square(deltaSpeed))
	Interpolate(
		m_velocity,
		m_vDesiredVelocity,
		2.5f * ((deltaSpeed > 0.f) ? min(frameTime, 2.f / square(deltaSpeed)) : frameTime),
		1.f);

	Quat desiredVelocityQuat = m_qDesiredRotation;

	// pitch/roll
	if (desiredSpeed > 0.f && m_stats.speed > 0.f)
	{
		const Vec3& vUp = Vec3Constants<float>::fVec3_OneZ;
		Vec3 vForward = m_velocity.GetNormalized();

		// If the direction is not too vertical
		if (fabs(vForward.dot(vUp)) < cosf(DEG2RAD(3.f)))
		{
			vForward.z = 0;
			vForward.NormalizeSafe();
			Vec3 vRight = vForward.Cross(vUp);
			vRight.NormalizeSafe();

			Vec3 vDesiredVelocityNormalized = m_vDesiredVelocity.GetNormalized();

			// Roll in an aircraft-like manner
			float cofRoll = 6.f * vRight.dot(vDesiredVelocityNormalized) * (m_stats.speed / maxDeltaSpeed);
			clamp(cofRoll, -1.f, 1.f);
			desiredVelocityQuat *= Quat::CreateRotationY(DEG2RAD(60.f) * cofRoll); 

			float cofPitch = vDesiredVelocityNormalized.dot(vForward) * (deltaSpeed / maxDeltaSpeed);
			clamp(cofPitch, -1.f, 1.f);
			desiredVelocityQuat *= Quat::CreateRotationX(DEG2RAD(-60.f) * cofPitch); 
		}
	}

	float cofRot = 2.5f * ((deltaSpeed > 0.f) ? min(frameTime, 1.f / square(deltaSpeed)) : frameTime);
	clamp(cofRot, 0.f, 1.f);
	const Quat& qRotation = GetEntity()->GetRotation();
	Quat newRot = Quat::CreateSlerp(qRotation, desiredVelocityQuat, cofRot);
	m_moveRequest.rotation = qRotation.GetInverted() * newRot;
	m_moveRequest.rotation.Normalize();

	m_moveRequest.velocity = m_velocity;

	m_moveRequest.type = eCMT_Fly;
}