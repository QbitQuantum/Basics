//------------------------------------------------------------------------
Quat CVehicleViewFirstPerson::GetWorldRotGoal()
{
	// now get fitting vehicle world pos/rot
	Quat vehicleWorldRot = m_pVehicle->GetEntity()->GetWorldRotation();

	if (m_relToHorizon > 0.f)
	{
		Quat vehicleRot = m_pVehicle->GetEntity()->GetRotation();
		Vec3 vx = vehicleRot * Vec3(1, 0, 0);
		Vec3 vy = vehicleRot * Vec3(0, 1, 0);
		Vec3 vz = vehicleRot * Vec3(0, 0, 1);

		// vx is "correct"
		vy = (1.0f - m_relToHorizon) * Vec3(0, 0, 1).Cross(vx) + m_relToHorizon * vy;
		vy.NormalizeSafe(Vec3Constants<float>::fVec3_OneY);
		vz = vx.Cross(vy);
		vz.NormalizeSafe(Vec3Constants<float>::fVec3_OneZ);

		vehicleWorldRot = Quat(Matrix33::CreateFromVectors(vx, vy, vz));      
	}

	return vehicleWorldRot;
}